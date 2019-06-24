#ifndef UPLOADROSTERDIALOG_H
#define UPLOADROSTERDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QDir>
#include "Roster/Roster.h"
#include "globals.h"
#include "EmployeeDatabase/EmployeeDatabase.h"
#include "CSVReader/CSVReader.h"

namespace Ui {
class UploadRosterDialog;
}

class UploadRosterDialog : public QDialog
{
    Q_OBJECT

    EmployeeDatabase *EMPL_DB;

    //Stores new roster
    Roster *rr;

    bool valid_roster_uploaded = false,
         valid_roster_title = false;

public:
    explicit UploadRosterDialog(EmployeeDatabase *db, QWidget *parent = nullptr);
    ~UploadRosterDialog();

private slots:
    void on_chooseFileButton_clicked();

    void on_uplRostOKButton_clicked();

    void on_rostTitleLineEdit_textChanged(const QString &title);

private:
    Ui::UploadRosterDialog *ui;

    void update_upl_button();

};

#endif // UPLOADROSTERDIALOG_H
