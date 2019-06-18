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

    /*Check if the user has entered valid
      employee info*/
    bool valid_f_name = false,
         valid_l_name = false,
         valid_dept = false;

public:
    explicit AddEmpDialog(MenuWindow *mw, EmployeeDatabase *db, QWidget *parent = nullptr);
    ~AddEmpDialog();

private slots:
    void on_addEmpButtonBox_accepted();

    void on_firstNameLineEdit_textChanged(const QString &arg1);

    void on_lastNameLineEdit_textChanged(const QString &arg1);

    void on_deptLineEdit_textChanged(const QString &arg1);

private:
    Ui::AddEmpDialog *ui;

    //Enabled if valid name & dept entered
    void refresh_button_box();
};

#endif // ADDEMPDIALOG_H
