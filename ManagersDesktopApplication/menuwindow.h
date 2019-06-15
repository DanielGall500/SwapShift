#ifndef MenuWindow_H
#define MenuWindow_H

#include <QMainWindow>
#include <qlabel.h>
#include <QString>
#include "EmployeeDatabase/EmployeeDatabase.h"

namespace Ui {
class MenuWindow;
}

class MenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

private slots:
    void on_emplButton_clicked();

private:
    Ui::MenuWindow *ui;

    /* Employee DB Display
     * r = rows, c = cols */
    void init_empl_table_view(vector<Employee> empl_db);
};

#endif // MenuWindow_H
