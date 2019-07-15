#include "menuwindow.h"
#include "ui_menuwindow.h"
#include "globals.h"

extern const QString ssTitleStr = "SwapShift";

MenuWindow::MenuWindow(EmployeeDatabase *db, QWidget *parent) :
    QMainWindow(parent), EMPL_DB(db),
    ui(new Ui::MenuWindow)
{
    ui->setupUi(this);

    sql_model_empl = new QSqlQueryModel();
    sql_model_rost = new QSqlQueryModel();

    //Setup the employee table for viewing
    setup_empl_table_view();

}

MenuWindow::~MenuWindow()
{
    delete ui;
}

void MenuWindow::setup_empl_table_view()
{
    empl_tbl = ui->emplTableDisplay;

    sql_model_empl->setQuery("SELECT * "
                             "FROM swapshift_db.employees");

    sql_model_empl->setHeaderData(0, Qt::Horizontal, "Employee ID");
    sql_model_empl->setHeaderData(1, Qt::Horizontal, "First Name");
    sql_model_empl->setHeaderData(2, Qt::Horizontal, "Last Name");
    sql_model_empl->setHeaderData(3, Qt::Horizontal, "Department");

    empl_tbl->setModel(sql_model_empl);
}

//--EMPLOYEE PAGE: SLOTS--
void MenuWindow::on_emplButton_clicked()
{
    //Move to the employee page
    ui->stackedWidget->setCurrentIndex(1);

    //Can only select rows on the employee table view
    ui->emplTableDisplay->setSelectionBehavior( QAbstractItemView::SelectRows );

    //Refresh the table view
   // refresh_empl_table_view(EMPL_DB);

}

//Refresh The Employee Table
void MenuWindow::refresh_empl()
{
    sql_model_empl->setQuery("SELECT *"
                        "FROM employees");
}

void MenuWindow::on_emplTableDisplay_clicked(const QModelIndex &index)
{
    //Update the global var for the selected row
    tbl_selection = index;

    //Find how many rows the user has selected
    QItemSelectionModel *itmMod = ui->emplTableDisplay->selectionModel();
    int numRowsSelected = itmMod->selectedRows().size();

    /* If the user has selected no rows, or selected more than
       one, we disable the edit and delete employee button */
    ui->editEmplButton->setEnabled(numRowsSelected == 1);
    ui->delEmplButton->setEnabled(numRowsSelected == 1);
}

//Om Clicking 'Add Employee' Button
void MenuWindow::on_addEmplButton_clicked()
{
    AddEmpDialog newAddEmpDial(this, EMPL_DB);
    newAddEmpDial.setModal(true);
    newAddEmpDial.setWindowTitle("Add Employee");
    newAddEmpDial.exec();
}

int MenuWindow::selectedRowEmplID()
{
    //id_col -> The ID Column Index
    int id_col = 0, empl_id;

    //We must specify which column holds the employee ID's
    QModelIndex column = tbl_selection.siblingAtColumn(id_col);

    //Get the data in this column
    empl_id = empl_tbl->model()->data(column).toInt();

    qDebug() << "Employee ID: " << empl_id;
    return empl_id;
}

//On Clicking 'Edit Employee' Button
void MenuWindow::on_editEmplButton_clicked()
{
    int ID = selectedRowEmplID();

    //Create an Edit Employee Dialog Box
    EditEmpDialog newEditEmpDialog(this, EMPL_DB, ID);
    newEditEmpDialog.setModal(true);
    newEditEmpDialog.setWindowTitle("Edit Employee");
    newEditEmpDialog.exec();
}


void MenuWindow::on_delEmplButton_clicked()
{
    QMessageBox::StandardButton delEmplMsgBox;

    //Dialog: 'Are You Sure?'
    delEmplMsgBox = QMessageBox::question(this, "Delete Employee", "Are you sure?",
                                   QMessageBox::Yes | QMessageBox::No);

    if(delEmplMsgBox == QMessageBox::Yes)
    {
        //Find the selected employee's ID
        int ID = selectedRowEmplID();

        //Delete them from the database
        EMPL_DB->del_employee(ID);

        //Refresh the table
        this->refresh_empl();
    }

}

//Employees Page: Back Button
void MenuWindow::on_emplBackButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}



//Upload Roster Button Clicked
void MenuWindow::on_uplRostButton_clicked()
{
    UploadRosterDialog uplRostDialog(EMPL_DB, this);
    uplRostDialog.setModal(true);
    uplRostDialog.setWindowTitle("Upload Roster");
    uplRostDialog.exec();
}

/* --CURRENT ROSTERS PAGE-- */
void MenuWindow::on_curRostButton_clicked()
{
    //Reset the roster selection combo box
    for(int i = 0; i < ui->rostSelectCombo->count(); i++)
        ui->rostSelectCombo->removeItem(i);

    //Add every roster title to combo box
    vectorStr titles = EMPL_DB->get_roster_titles();

    for(string t : titles)
        ui->rostSelectCombo->addItem(QString::fromStdString(t));

    //Initialise the display with the first roster
    if(titles.size() > 0)
        curr_rost_display(titles[0]);

    //Move to current rosters page
    ui->stackedWidget->setCurrentIndex(2);

}

void MenuWindow::curr_rost_display(string roster)
{
    rost_tbl = ui->currRostTableView;
    rost_model = new EmplRosterModel(EMPL_DB, roster, 0);
/*
    QSqlQuery q("SELECT * "
                "FROM shifts "
                "WHERE roster = 'rost1'",
                EMPL_DB->connect_db());

    q.bindValue(":R", QString::fromStdString(roster));
*/


    rost_tbl->setModel(rost_model);
    rost_tbl->show();
}



//Clicked Current Roster Page Back Button
void MenuWindow::on_currRostBackButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

//Clicked Roster Selection Combo Box
void MenuWindow::on_rostSelectCombo_activated(const QString &title)
{
    //Convert to STD
    string t = qStr_to_stdStr(title);

    //Display selected roster
    curr_rost_display(t);
}














