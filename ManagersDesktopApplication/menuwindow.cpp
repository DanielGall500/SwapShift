#include "menuwindow.h"
#include "ui_menuwindow.h"
#include "globals.h"

extern const QString ssTitleStr = "SwapShift";

MenuWindow::MenuWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenuWindow)
{
    ui->setupUi(this);

    //Menu Title Label
    QFont titleFont("Arial", 18, QFont::Bold);
    ui->menuTitle->setFont(titleFont);
    ui->menuTitle->setAlignment(Qt::AlignCenter);
    ui->menuTitle->setStyleSheet("color: white");


}

MenuWindow::~MenuWindow()
{
    delete ui;
}
