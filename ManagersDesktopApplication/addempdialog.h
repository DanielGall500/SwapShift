#ifndef ADDEMPDIALOG_H
#define ADDEMPDIALOG_H

#include <QDialog>
#include "Employee/Employee.h"
#include "EmployeeDatabase/EmployeeDatabase.h"
#include "globals.h"

namespace Ui {
class AddEmpDialog;
}

class MenuWindow;

class AddEmpDialog : public QDialog
{
    Q_OBJECT

    MenuWindow *main_window;
    EmployeeDatabase *EMPL_DB;

public:
    explicit AddEmpDialog(MenuWindow *mw, EmployeeDatabase *db, QWidget *parent = nullptr);
    ~AddEmpDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddEmpDialog *ui;
};

#endif // ADDEMPDIALOG_H
