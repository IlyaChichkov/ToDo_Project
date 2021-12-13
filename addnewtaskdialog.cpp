#include "addnewtaskdialog.h"
#include <QMessageBox>

#include <QDebug>
#include "task.h"

AddNewTaskDialog::AddNewTaskDialog(QWidget *parent):
    QDialog(parent){

}

Task* AddNewTaskDialog::CreateNewTask(QVariantList &writables){
    // Проверка на пустоту поля name в задаче
    QString text = writables[0].toString();
    QString desc = writables[1].toString();
    if(!text.length()){
        QMessageBox msg;
        msg.setText("Задача должна иметь имя");
        msg.setWindowTitle("Неверный ввод");
        msg.exec();
        return nullptr;
    }

    Task* task = new Task();
    task->name = text;
    task->desc = desc;
    return task;
}

AddNewTaskDialog::~AddNewTaskDialog()
{
    view->close();
}

void AddNewTaskDialog::destruct(){
    delete this;
}


void AddNewTaskDialog::onCreateClicked(QVariantList writables){
    Task* task = CreateNewTask(writables);
    if(!task)
        return;

    qDebug() << task->name << task->desc;
    this->fileManager->AddTaskToGroup(currentGroup, task);
    this->fileManager->SaveData();

}
