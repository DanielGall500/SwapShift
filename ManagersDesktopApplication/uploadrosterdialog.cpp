#include "uploadrosterdialog.h"
#include "ui_uploadrosterdialog.h"

UploadRosterDialog::UploadRosterDialog(EmployeeDatabase *db, QWidget *parent) :
    QDialog(parent), EMPL_DB(db),
    ui(new Ui::UploadRosterDialog)
{
    ui->setupUi(this);
}

UploadRosterDialog::~UploadRosterDialog()
{
    delete ui;
}

//Roster(string title, vectorStr2D csv_roster, col_pos names, row_pos dates, vectorStr non_shifts);

void UploadRosterDialog::on_chooseFileButton_clicked()
{
    QString file_filter = "CSV Files (*.csv)";

    //Open a browser & select a file
    QString f_dir = QFileDialog::getOpenFileName(this, "Select Roster", QDir::homePath(), file_filter);

    //Show the user the selected file
    ui->fileLabel->setText("File: " + f_dir);

    //Convert to STD String
    std::string file_dir = qStr_to_stdStr(f_dir);


    vectorStr2D file;
    vectorStr to_ignore{"Department", "Floor"};
    CSVReader rdr(file_dir, to_ignore, ",");

    if(rdr.open_file())
    {
        file = rdr.read_csv();
    }

    //--TESTING--
    row_pos dates_pos(0, 1);
    col_pos names_pos(0, 1);
    vectorStr non_shifts{"N/A", "Hol"};
    string roster_title = "Week 1"; //MAKE UNIQUE ONLY
    //-----------

    rr = new Roster(roster_title, file, names_pos, dates_pos, non_shifts);

    //Check roster is valid
    string empl_not_found, error;
    if(!rr->check_db_contains_rost_empl(*EMPL_DB, empl_not_found))
    {
        //Invalid Roster: Employee Not Found In Database

        error = "Error: Employee " + empl_not_found
                + " could not be found in the database.";

        ui->uplRostOKButton->setEnabled(false);
        ui->isValidRostLabel->setText(QString::fromStdString(error));
    }
    else if(!rr->check_formatted_correctly())
    {
        //Invalid Roster: Not Formatted Correctly

        error = "Error: Roster Not Formatted Correctly";

        ui->uplRostOKButton->setEnabled(false);
        ui->isValidRostLabel->setText(QString::fromStdString(error));
    }
    else
    {
        //Valid Roster

        ui->uplRostOKButton->setEnabled(true);
        ui->isValidRostLabel->setText("Roster Valid");
    }
}

void UploadRosterDialog::on_uplRostOKButton_clicked()
{
    //Upload the roster to the employee database
    EMPL_DB->add_new_roster(*rr);

    //Close the window
    this->close();
}
