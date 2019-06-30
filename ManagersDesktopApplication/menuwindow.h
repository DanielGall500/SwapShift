#ifndef MenuWindow_H
#define MenuWindow_H

#include <QMainWindow>
#include <qlabel.h>
#include <QString>
#include <QTableWidget>
#include <QMessageBox>
#include "EmployeeDatabase/EmployeeDatabase.h"
#include "Employee/Employee.h"
#include "addempdialog.h"
#include "editempdialog.h"
#include "uploadrosterdialog.h"
#include "emplrostermodel.h"

namespace Ui {
class MenuWindow;
}

class MenuWindow : public QMainWindow
{
    Q_OBJECT

    //EMPLOYEE DISPLAY
    QTableWidget *empl_tbl;

    //ROSTER DISPLAY
    EmplRosterModel *rost_model;
    QTableView *rost_tbl;

    //MAIN DATABASE
    EmployeeDatabase *EMPL_DB;

    int name_hdr_indx = 0,
        dept_hdr_indx = 1,
        ID_hdr_indx = 2;

public:
    explicit MenuWindow(EmployeeDatabase *db, QWidget *parent = nullptr);
    ~MenuWindow();

private slots:
    void on_emplButton_clicked();

    void on_addEmplButton_clicked();

    void on_editEmplButton_clicked();

    void on_emplTableDisp_itemSelectionChanged();

    void on_delEmplButton_clicked();

    void on_emplBackButton_clicked();

    void on_uplRostButton_clicked();

    void on_curRostButton_clicked();

    void on_currRostBackButton_clicked();

    void on_rostSelectCombo_activated(const QString &arg1);

private:
    Ui::MenuWindow *ui;

    //Friend Classes
    friend class EditEmpDialog;
    friend class AddEmpDialog;

    /* Employee DB Display Widget */
    //First time setup of the table
    void setup_empl_table_view(EmployeeDatabase *empl_db);

    //Refresh when edits are made
    void refresh_empl_table_view(EmployeeDatabase *empl_db);

    //Get the index of the selected row
    std::string selectedRowEmplID();

    /*Current Rosters Table View*/
    void curr_rost_display(string roster);
};

#endif // MenuWindow_H
