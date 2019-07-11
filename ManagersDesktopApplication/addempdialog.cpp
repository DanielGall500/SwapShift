#include "addempdialog.h"
#include "ui_addempdialog.h"
#include "menuwindow.h"

AddEmpDialog::AddEmpDialog(MenuWindow *mw, EmployeeDatabase *db, QWidget *parent) :
    QDialog(parent), main_window(mw), EMPL_DB(db),
    ui(new Ui::AddEmpDialog)
{
    ui->setupUi(this);
}

AddEmpDialog::~AddEmpDialog()
{
    delete ui;
}

//OK is clicked
void AddEmpDialog::on_addEmpButtonBox_accepted()
{
    /*Inputs: First Name, Last Name, Department*/
    string inp[3] = { qStr_to_stdStr(ui->firstNameLineEdit->text()),
                      qStr_to_stdStr(ui->lastNameLineEdit->text()),
                      qStr_to_stdStr(ui->deptLineEdit->text()) };

    //Create a new employee with these inputs
    Employee new_emp(inp[0], inp[1], inp[2]);

    //CHECK: Is Employee name already in database?
    if(EMPL_DB->empl_exists(new_emp.get_first_name(), new_emp.get_last_name()))
    {
        //ERROR: EMPLOYEE ALREADY EXISTS
        QMessageBox::critical(this, "Cannot Add Employee",
                              "An employee by this name already exists.");
    }
    else
    {
        //Add the employee to the database
        EMPL_DB->add_employee(new_emp);


        main_window->refresh_empl();
        //UPDATE TABLE***
        //main_window->refresh_empl_table_view(EMPL_DB);
    }
}

//Refresh The Ok/Cancel Button
void AddEmpDialog::refresh_button_box()
{
    if(valid_f_name && valid_l_name && valid_dept)
        ui->addEmpButtonBox->setEnabled(true);
    else
        ui->addEmpButtonBox->setEnabled(false);
}

//SLOTS: LINE EDITS
void AddEmpDialog::on_firstNameLineEdit_textChanged(const QString &arg1)
{
    if(arg1.isEmpty())
        valid_f_name = false;
    else
        valid_f_name = true;

    refresh_button_box();
}

void AddEmpDialog::on_lastNameLineEdit_textChanged(const QString &arg1)
{
    if(arg1.isEmpty())
        valid_l_name = false;
    else
        valid_l_name = true;

    refresh_button_box();
}


void AddEmpDialog::on_deptLineEdit_textChanged(const QString &arg1)
{
    if(arg1.isEmpty())
        valid_dept = false;
    else
        valid_dept = true;

    refresh_button_box();
}
