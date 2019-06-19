#include "uploadrosterdialog.h"
#include "ui_uploadrosterdialog.h"

UploadRosterDialog::UploadRosterDialog(QWidget *parent) :
    QDialog(parent),
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
    std::string dir = qStr_to_stdStr(f_dir);

    //Create Roster
    Roster rr(dir, ",", 0, true);

}
