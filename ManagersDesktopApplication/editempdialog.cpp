#include "editempdialog.h"
#include "ui_editempdialog.h"

EditEmpDialog::EditEmpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditEmpDialog)
{
    ui->setupUi(this);
}

EditEmpDialog::~EditEmpDialog()
{
    delete ui;
}
