#ifndef ADDNEWTASKDIALOG_H
#define ADDNEWTASKDIALOG_H

#include <QDialog>
#include <filemanager.h>
#include <QQuickView>

#include "task.h"

//namespace Ui {
//class AddNewTaskDialog;
//}

class AddNewTaskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewTaskDialog(QWidget *parent = nullptr);
    ~AddNewTaskDialog();
    Task* CreateNewTask(QVariantList &writables);
    QString currentGroup;
    FileManager* fileManager;
    QQuickView *view;

    Q_INVOKABLE void onCreateClicked(QVariantList writables); // writables - всё, что нужно записать, после нажатия кнопки "Создать задачу"
    Q_INVOKABLE void destruct();

//public slots:
//    void on_cancelButton_clicked();
//    void on_createButton_clicked();

//private:
//    Ui::AddNewTaskDialog *ui;
};

#endif // ADDNEWTASKDIALOG_H
