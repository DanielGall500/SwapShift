#ifndef EDITEMPDIALOG_H
#define EDITEMPDIALOG_H

#include <QDialog>
#include "Employee/Employee.h"
#include "EmployeeDatabase/EmployeeDatabase.h"
#include "globals.h"

namespace Ui {
class EditEmpDialog;
}

class MenuWindow;

class EditEmpDialog : public QDialog
{
    Q_OBJECT

    //Pointers to external class objects
    MenuWindow *main_window;
    EmployeeDatabase *EMPL_DB;

    //Employee's Variables
    QString f_name, l_name, dept;
    int empl_ID;


public:
    explicit EditEmpDialog(MenuWindow *mw, EmployeeDatabase *db, int empl_ID, QWidget *parent = nullptr);
    ~EditEmpDialog();

private slots:
    void on_editEmpButtonBox_accepted();

private:
    Ui::EditEmpDialog *ui;
};

#endif // EDITEMPDIALOG_H
