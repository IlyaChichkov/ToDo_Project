#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->taskGroupsList->addItem("Учеба");
    ui->taskGroupsList->addItem("Работа");
    ui->taskGroupsList->addItem("Кино и сериалы");
    ui->taskGroupsList->addItem("Книги");
    ui->taskGroupsList->addItem("Рецепты");
    ui->taskGroupsList->addItem("Личное");
    ui->taskGroupsList->addItem("Советы");
    ui->taskGroupsList->addItem("Игры");
    ui->taskGroupsList->addItem("Интересное");
    ui->taskGroupsList->addItem("Рыбалка");
    ui->taskGroupsList->addItem("Путешествие");
    ui->taskGroupsList->addItem("Машины");
    ui->taskGroupsList->addItem("Фото");
    ui->taskGroupsList->addItem("Остальное");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_taskGroupsList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    ui->selectedGroupName->setText(ui->taskGroupsList->currentItem()->text());
}

void MainWindow::on_exitButton_released()
{
    QApplication::quit();
}

void MainWindow::on_addNewGroup_clicked()
{
    bool bOk;
    QString newGroupName = QInputDialog::getText(0, "Новая группа", "Введите название новой группы:", QLineEdit::Normal, "", &bOk);
    if (bOk && newGroupName.length() > 0) {
        ui->taskGroupsList->addItem(newGroupName);
    }
}

void MainWindow::SetGroupsByList(QList<QString> groupsNames)
{
    ui->taskGroupsList->clear();
    foreach (QString name, groupsNames) {
        ui->taskGroupsList->addItem(name);
        ui->selectedGroupName->setText(name);
    }
}


