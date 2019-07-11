#include "editempdialog.h"
#include "ui_editempdialog.h"
#include "menuwindow.h"

EditEmpDialog::EditEmpDialog(MenuWindow *mw, EmployeeDatabase *db, int ID, QWidget *parent) :
    QDialog(parent), main_window(mw), EMPL_DB(db), empl_ID(ID),
    ui(new Ui::EditEmpDialog)
{
    ui->setupUi(this);

    //Store selected employee's info
    f_name = QString::fromStdString(db->get_empl_firstN(ID));
    l_name = QString::fromStdString(db->get_empl_lastN(ID));
    orig_dept = QString::fromStdString(db->get_empl_dept(ID));

    //Add the info to our line-edit widgets
    ui->firstNameLineEdit->setText(f_name);
    ui->lastNameLineEdit->setText(l_name);
    ui->deptLineEdit->setText(orig_dept);
}

EditEmpDialog::~EditEmpDialog()
{
    delete ui;
}

//Update Employee Info
void EditEmpDialog::on_editEmpButtonBox_accepted()
{
    //Set variables equal to the line edit boxes
    f_name    = ui->firstNameLineEdit->text();
    l_name    = ui->lastNameLineEdit->text();
    curr_dept = ui->deptLineEdit->text();

    /* Check (1): Does An Employee With This Name Already Exist?
     * Check (2): Did They Change The Department Of This Employee? */

    bool exists = EMPL_DB->empl_exists(qStr_to_stdStr(f_name), qStr_to_stdStr(l_name)),
         same_dept = (orig_dept == curr_dept);

    //Check if employee details should be updated
    if (exists && same_dept)
    {
        //ERROR: EMPLOYEE ALREADY EXISTS
        QMessageBox::critical(this, "Cannot Edit Employee",
                              "Employee details haven't been edited,"
                              "or this employee already exists");
    }
    else
    {
        //Update the employee information
        EMPL_DB->edit_empl_firstN(empl_ID, qStr_to_stdStr(f_name));
        EMPL_DB->edit_empl_lastN(empl_ID, qStr_to_stdStr(l_name));
        EMPL_DB->edit_empl_dept(empl_ID, qStr_to_stdStr(curr_dept));

        main_window->refresh_empl();
    }
}
