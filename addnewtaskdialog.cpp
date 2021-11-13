#include "addnewtaskdialog.h"
#include "ui_addnewtaskdialog.h"
#include <QMessageBox>

#include <QDebug>
#include "task.h"
//Функция addNewTaskToGroup(task) должна быть реализована в filemanager
// #include "filemanager.h"

AddNewTaskDialog::AddNewTaskDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewTaskDialog)
{
    ui->setupUi(this);
}

void AddNewTaskDialog::on_cancelButton_clicked(){
    this->close();
}

void AddNewTaskDialog::on_createButton_clicked(){
    Task* task = createNewTask();
    if(!task)
        return;

    qDebug() << task->name;
    this->fileManager->AddTaskToGroup(currentGroup, task);
    this->fileManager->SaveData();
    this->close();
// Эта функция должна быть реализована в filemanager
//    addNewTaskToGroup(task);
}

Task* AddNewTaskDialog::createNewTask(){
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

AddNewTaskDialog::~AddNewTaskDialog()
{
    delete ui;
}
