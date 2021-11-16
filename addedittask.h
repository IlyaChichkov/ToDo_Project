#ifndef ADDEDITTASK_H
#define ADDEDITTASK_H

#include <QDialog>
#include <filemanager.h>

#include "task.h"

namespace Ui {
class AddEditTask;
}

class AddEditTask : public QDialog
{
    Q_OBJECT

public:
    explicit AddEditTask(QWidget *parent = nullptr);
    ~AddEditTask();
    Task* changeTask();
    QString currentGroup;
    FileManager* fileManager;

public slots:
    void on_cancelButton_clicked();
    void on_createButton_clicked();

private:
    Ui::AddEditTask *ui;
};

#endif // ADDEDITTASK_H
