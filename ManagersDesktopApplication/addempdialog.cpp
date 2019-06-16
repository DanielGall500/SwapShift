#include "addempdialog.h"
#include "ui_addempdialog.h"

AddEmpDialog::AddEmpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEmpDialog)
{
    ui->setupUi(this);
}

AddEmpDialog::~AddEmpDialog()
{
    delete ui;
}
