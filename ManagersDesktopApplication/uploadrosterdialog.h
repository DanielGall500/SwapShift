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

public:
    explicit UploadRosterDialog(EmployeeDatabase *db, QWidget *parent = nullptr);
    ~UploadRosterDialog();

private slots:
    void on_chooseFileButton_clicked();

    void on_uplRostOKButton_clicked();

private:
    Ui::UploadRosterDialog *ui;

};

#endif // UPLOADROSTERDIALOG_H
