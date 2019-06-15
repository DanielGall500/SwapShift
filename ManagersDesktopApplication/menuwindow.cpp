#include "MenuWindow.h"
#include "ui_MenuWindow.h"
#include "globals.h"

extern const QString ssTitleStr = "SwapShift";

MenuWindow::MenuWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenuWindow)
{
    ui->setupUi(this);

    //Menu Title Label

    //Stacked Widget


}

MenuWindow::~MenuWindow()
{
    delete ui;
}

void MenuWindow::on_emplButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

    Employee x("John Gallagher", 1, "Shopfloor");
    Employee y("Aoife Colleran", 2, "Quit");
    Employee z("David Smith", 3, "Fruit&Veg");

    vector<Employee> empl_db{ x, y, z };

    init_empl_table_view(empl_db);

}

void MenuWindow::init_empl_table_view(vector<Employee> empl_db)
{
    QTableWidget *empl_tbl = ui->emplTableDisp;

    //Make Table Read-Only
    empl_tbl->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //No. Rows = Size of employee database
    //Columns: Name, Department, ID
    size_t rows = empl_db.size();
    size_t cols = 3;

    //Column Headers
    QStringList headers = {"Name", "Department", "Unique ID"};
    empl_tbl->setColumnCount(cols);
    empl_tbl->setHorizontalHeaderLabels(headers);

    //Add items to table
    for(size_t r = 0; r < rows; r++)
    {
       Employee &e = empl_db[r];

       string entries[3] = {e.get_full_name(), e.get_department(),
                            std::to_string(e.get_employee_ID())};

       //Add a new row for a new employee
       empl_tbl->insertRow(r);

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
           empl_tbl->setItem(r, c, nxt_itm);
       }


    }


}










