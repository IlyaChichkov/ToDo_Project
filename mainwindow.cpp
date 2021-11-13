#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>
#include <QDebug>

#include "addnewtaskdialog.h"

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

void MainWindow::SetGroupsListWidget(QList<QString> groupNames)
{
    ui->taskGroupsList->clear(); // очищаем текущие значения наименований групп
    foreach (QString name, groupNames) {
        ui->taskGroupsList->addItem(name); // добавлям в список имя группы
    }

    ui->selectedGroupName->setText(ui->taskGroupsList->item(0)->text()); // отображаем заголовок первой группы в списке
}

void MainWindow::on_taskGroupsList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    //  при выделение группы мышью

    // вывод в консоль имени первой задачи в группе
    // qDebug() << fileManager->GetGroupTasks(current->text())[0]->name;

    ui->selectedGroupName->setText(current->text()); // отображаем заголовок текущей группы
}

void MainWindow::on_addNewGroup_clicked()
{
    // добавление новой группы
    bool buttonOk;
    QString newGroupName = QInputDialog::getText(0, "Новая группа", "Введите название новой группы:", QLineEdit::Normal, "", &buttonOk);
    if (buttonOk && newGroupName.length() > 0) { // если нажата OK и введено имя
        ui->taskGroupsList->addItem(newGroupName); // добавляем новую группу в список
    }
}

void MainWindow::on_exitButton_released()
{
    QApplication::quit();
}

void MainWindow::on_addNewTask_clicked()
{
    AddNewTaskDialog *addNewTaskDialog = new AddNewTaskDialog(this->ui->addNewTask);
    // Благодаря этому аттрибуту не нужно delete addNewTaskDialog и не нужно сохранять указатель в класс
    addNewTaskDialog->setAttribute(Qt::WA_DeleteOnClose);
    addNewTaskDialog->show();
}

