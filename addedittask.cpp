#include "addedittask.h"
#include "ui_addedittask.h"
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>

#include <QDebug>
#include "task.h"

AddEditTask::AddEditTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEditTask)
{
    ui->setupUi(this);
}

void AddEditTask::on_cancelButton_clicked(){
    this->close();
}

void AddEditTask::on_createButton_clicked(){
    Task* task = changeTask();
    if(!task)
        return;

    qDebug() << task->name;
    this->fileManager->AddTaskToGroup(currentGroup, task);
    this->fileManager->SaveData();
    this->close();
}

Task* AddEditTask::changeTask(){
    // Проверка на пустоту поля name в задаче
    if(!ui->name->text().length()){
        QMessageBox msg;
        msg.setText("Задача должна иметь имя");
        msg.setWindowTitle("Неверный ввод");
        msg.exec();
        return nullptr;
    }

    Task* task = new Task();
    task->name = ui->name->text();
    task->desc = ui->desc->toPlainText();
    return task;
}

AddEditTask::~AddEditTask()
{
    delete ui;
}



