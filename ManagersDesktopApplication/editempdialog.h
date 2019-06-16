#ifndef EDITEMPDIALOG_H
#define EDITEMPDIALOG_H

#include <QDialog>

namespace Ui {
class EditEmpDialog;
}

class EditEmpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditEmpDialog(QWidget *parent = nullptr);
    ~EditEmpDialog();

private:
    Ui::EditEmpDialog *ui;
};

#endif // EDITEMPDIALOG_H
