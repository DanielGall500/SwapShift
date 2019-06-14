#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QMainWindow>
#include <qlabel.h>
#include <QString>

namespace Ui {
class MenuWindow;
}

class MenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

private:
    Ui::MenuWindow *ui;
};

#endif // MENUWINDOW_H
