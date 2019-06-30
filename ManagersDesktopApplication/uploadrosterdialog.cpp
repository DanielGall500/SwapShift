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
        file = rdr.read_csv();
    else
        throw "File Cannot Be Opened";

    //--TESTING--
    row_pos dates_pos(0, 1);
    col_pos names_pos(0, 1);
    vectorStr non_shifts{"N/A", "Hol"};
    //-----------

    //Get roster title
    string r_title = qStr_to_stdStr(ui->rostTitleLineEdit->text());

    //Create a new roster
    rr = new Roster(r_title, file, names_pos, dates_pos, non_shifts);

    //Check roster is valid
    string empl_not_found, error;
    if(!rr->check_db_contains_rost_empl(*EMPL_DB, empl_not_found))
    {
        //Invalid Roster: Employee Not Found In Database
        valid_roster_uploaded = false;
        update_upl_button();

        error = "Error: Employee " + empl_not_found
                + " could not be found in the database.";

        ui->isValidRostLabel->setText(QString::fromStdString(error));
    }
    else if(!rr->check_formatted_correctly())
    {
        //Invalid Roster: Not Formatted Correctly
        valid_roster_uploaded = false;
        update_upl_button();

        error = "Error: Roster Not Formatted Correctly";
        ui->isValidRostLabel->setText(QString::fromStdString(error));
    }
    else
    {
        cout << "DEBUG" << endl;

        //Valid Roster
        valid_roster_uploaded = true;
        update_upl_button();

        cout << "DEBUG" << endl;

        //Update status
        ui->isValidRostLabel->setText("Roster Valid");

        cout << "DEBUG" << endl;

        //Disable the roster title line edit
        ui->rostTitleLineEdit->setEnabled(false);

        cout << "DEBUG" << endl;
    }
}

void UploadRosterDialog::on_uplRostOKButton_clicked()
{
    //Upload the roster to the employee database
    EMPL_DB->add_new_roster(*rr);

    //DELETE
    rr->print_summary();
    EMPL_DB->print_summary();

    //Close the window
    this->close();
}

void UploadRosterDialog::update_upl_button()
{
    if(valid_roster_uploaded && valid_roster_title)
        ui->uplRostOKButton->setEnabled(true);
    else
        ui->uplRostOKButton->setEnabled(false);
}

void UploadRosterDialog::on_rostTitleLineEdit_textChanged(const QString &title)
{
    vectorStr prev_titles = EMPL_DB->get_roster_titles();

    string r_title = qStr_to_stdStr(title);

    //Default to true
    valid_roster_title = true;

    /* Check 1:
       Check if roster title is an empty string */
    if(title.isEmpty())
    {
        valid_roster_title = false;
        ui->isValidRostLabel->setText("Invalid Title");
    }


    /*Check 2:
      Check if the title entered has already been
      used for another roster */
    for(string &t : prev_titles)
    {
        if(t == r_title)
        {
            ui->isValidRostLabel->setText(
                        "This roster title has been used before. Please use a different one.");

            valid_roster_title = false;
            break;
        }
    }

    //Allow the user to upload a file
    if(valid_roster_title)
    {
        ui->chooseFileButton->setEnabled(true);
        ui->isValidRostLabel->setText("Valid Title");
    }
    else
        ui->chooseFileButton->setEnabled(false);

    //Check if upload button should be enabled
    update_upl_button();
}
