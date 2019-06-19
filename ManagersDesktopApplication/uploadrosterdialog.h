#ifndef UPLOADROSTERDIALOG_H
#define UPLOADROSTERDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QDir>
#include "Roster/Roster.h"
#include "globals.h"

namespace Ui {
class UploadRosterDialog;
}

class UploadRosterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UploadRosterDialog(QWidget *parent = nullptr);
    ~UploadRosterDialog();

private slots:
    void on_chooseFileButton_clicked();

private:
    Ui::UploadRosterDialog *ui;

};

#endif // UPLOADROSTERDIALOG_H
