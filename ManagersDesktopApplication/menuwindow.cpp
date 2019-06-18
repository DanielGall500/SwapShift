#include "menuwindow.h"
#include "ui_menuwindow.h"
#include "globals.h"

extern const QString ssTitleStr = "SwapShift";

MenuWindow::MenuWindow(EmployeeDatabase *db, QWidget *parent) :
    QMainWindow(parent), EMPL_DB(db),
    ui(new Ui::MenuWindow)
{
    ui->setupUi(this);


}

MenuWindow::~MenuWindow()
{
    delete ui;
    EMPL_DB->print_summary();
}

//--EMPLOYEE PAGE: TABLE VIEW--
void MenuWindow::setup_empl_table_view(EmployeeDatabase *empl_db)
{
    empl_tbl = ui->emplTableDisp;
    vector<Employee> empl_vec = empl_db->get_db_vector();

    //Make Table Read-Only
    empl_tbl->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //No. Rows = Size of employee database
    //Columns: Name, Department, ID
    size_t rows = empl_vec.size();
    size_t cols = 3;

    //Column Headers
    QStringList headers = {"Name", "Department", "Unique ID"};
    empl_tbl->setColumnCount((signed)cols);
    empl_tbl->setHorizontalHeaderLabels(headers);

    //Add items to table
    for(size_t r = 0; r < rows; r++)
    {
       Employee &e = empl_vec[r];

       string entries[3] = {e.get_full_name(), e.get_department(),
                            std::to_string(e.get_employee_ID())};

       //Add a new row for a new employee
       empl_tbl->insertRow((signed)r);

       for(size_t c = 0; c < cols; c++)
       {
           //Create an item for our next entry
           QTableWidgetItem *nxt_itm = new QTableWidgetItem();

           /* Set the value of the next item:
            * c = 0 -> Name
              c = 1 -> Department
              c = 2 -> Unique ID */
           nxt_itm->setText(QString::fromStdString(entries[c]));

           //Add the item to the table
           empl_tbl->setItem((signed)r, (signed)c, nxt_itm);
       }


    }


}

void MenuWindow::refresh_empl_table_view(EmployeeDatabase *empl_db)
{
    //Clear the previous rows in the employee table
    empl_tbl->setRowCount(0);

    //Reload the employee data
    vector<Employee> empl_vec = empl_db->get_db_vector();

    //No. Rows = Size of employee database
    //Columns: Name, Department, ID
    size_t rows = empl_vec.size();
    size_t cols = 3;

    //Add items to table
    for(size_t r = 0; r < rows; r++)
    {
       Employee &e = empl_vec[r];

       string entries[3] = {e.get_full_name(), e.get_department(),
                            std::to_string(e.get_employee_ID())};

       std::cout << "Reloading " << e.get_full_name() << endl;

       //Add a new row for a new employee
       empl_tbl->insertRow((signed)r);

       for(size_t c = 0; c < cols; c++)
       {
           //Create an item for our next entry
           QTableWidgetItem *nxt_itm = new QTableWidgetItem();

           /* Set the value of the next item:
            * c = 0 -> Name
              c = 1 -> Department
              c = 2 -> Unique ID */
           nxt_itm->setText(QString::fromStdString(entries[c]));

           //Add the item to the table
           empl_tbl->setItem((signed)r, (signed)c, nxt_itm);
       }


    }
}

//--EMPLOYEE PAGE: SLOTS--
void MenuWindow::on_emplButton_clicked()
{
    //Move to the employee page
    ui->stackedWidget->setCurrentIndex(1);

    //Can only select rows on the employee table view
    ui->emplTableDisp->setSelectionBehavior( QAbstractItemView::SelectRows );

    //Initialise the table view
    setup_empl_table_view(EMPL_DB);

}

//On Clicking An Employee(Row) In The Table
void MenuWindow::on_emplTableDisp_itemSelectionChanged()
{
    //Find how many rows the user has selected
    QItemSelectionModel *itmMod = ui->emplTableDisp->selectionModel();
    int numRowsSelected = itmMod->selectedRows().size();

    /* If the user has selected no rows, or selected more than
       one, we disable the edit and delete employee button */
    ui->editEmplButton->setEnabled(numRowsSelected == 1);
    ui->delEmplButton->setEnabled(numRowsSelected == 1);
}

//Om Clicking 'Add Employee' Button
void MenuWindow::on_addEmplButton_clicked()
{
    AddEmpDialog newAddEmpDial(EMPL_DB);
    newAddEmpDial.setModal(true);
    newAddEmpDial.setWindowTitle("Add Employee");
    newAddEmpDial.exec();
}

//On Clicking 'Edit Employee' Button
void MenuWindow::on_editEmplButton_clicked()
{
    //Find the employee name in the row the user has selected
    int selected_row_indx = ui->emplTableDisp->currentRow();
    QString curr_selected_emp_name = ui->emplTableDisp->item(selected_row_indx, name_hdr_indx)->text();

    //Convert to STD String
    string name = qStr_to_stdStr(curr_selected_emp_name);

    //Create an Edit Employee Dialog Box
    EditEmpDialog newEditEmpDialog(this, EMPL_DB, name);
    newEditEmpDialog.setModal(true);
    newEditEmpDialog.setWindowTitle("Edit Employee");
    newEditEmpDialog.exec();
}



void MenuWindow::on_delEmplButton_clicked()
{
    //TODO: ADD 'ARE YOU SURE' DIALOG


}








