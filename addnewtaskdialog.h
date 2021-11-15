#ifndef ADDNEWTASKDIALOG_H
#define ADDNEWTASKDIALOG_H

#include <QDialog>
#include <filemanager.h>

#include "task.h"

namespace Ui {
class AddNewTaskDialog;
}

class AddNewTaskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewTaskDialog(QWidget *parent = nullptr);
    ~AddNewTaskDialog();
    Task* CreateNewTask();
    QString currentGroup;
    FileManager* fileManager;

public slots:
    void on_cancelButton_clicked();
    void on_createButton_clicked();

private:
    Ui::AddNewTaskDialog *ui;
};

#endif // ADDNEWTASKDIALOG_H
