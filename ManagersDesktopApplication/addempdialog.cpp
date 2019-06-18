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
void AddEmpDialog::on_buttonBox_accepted()
{

    /*Inputs: First Name, Last Name, Department*/
    string inp[3] = { qStr_to_stdStr(ui->firstNameLineEdit->text()),
                      qStr_to_stdStr(ui->lastNameLineEdit->text()),
                      qStr_to_stdStr(ui->deptLineEdit->text()) };

    //Create a new employee with these inputs
    Employee new_emp(inp[0], inp[1], inp[2]);

    //TODO: Add the employee to the database
    EMPL_DB->add_employee(new_emp);

    main_window->refresh_empl_table_view(EMPL_DB);
}
