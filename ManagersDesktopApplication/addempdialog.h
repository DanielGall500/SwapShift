#ifndef ADDEMPDIALOG_H
#define ADDEMPDIALOG_H

#include <QDialog>

namespace Ui {
class AddEmpDialog;
}

class AddEmpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddEmpDialog(QWidget *parent = nullptr);
    ~AddEmpDialog();

private:
    Ui::AddEmpDialog *ui;
};

#endif // ADDEMPDIALOG_H
