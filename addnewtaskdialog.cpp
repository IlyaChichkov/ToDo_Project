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
    int hour = writables[2].toInt();
    int minute = writables[3].toInt();
    int day = writables[4].toInt();
    QString month = writables[5].toString();
    int year = writables[6].toInt();
//    qDebug() << text << '\n' << desc << '\n' << hour << '\n' << minute << '\n' <<  day << '\n' <<  month << '\n' << year;
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
//    task->hour = hour;
//    task->minute = minute;
//    task->day = day;
//    task->month = month;
//    task->year = year;
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

//    qDebug() << task->name << task->desc;
//    this->fileManager->AddTaskToGroup(currentGroup, task);
//    this->fileManager->SaveData();
    destruct();
}
