#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>
#include <QDebug>
#include <QQuickView>
#include <QQmlComponent>
#include <QWindow>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickView>
#include <QQmlComponent>
#include <QWindow>
#include <QQmlContext>
#include <QQmlEngine>

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


    Pending = new QListView(this);
    Pending->setDragEnabled(true); //перетаскивание
    Pending->setAcceptDrops(true);
    Pending->setDropIndicatorShown(true); //индикатор падения
    Pending->setDefaultDropAction(Qt::MoveAction);
    ui->pcLayout->addWidget(Pending); /*добавляем виджет в
    pcLayout(p-pending, c-complited)*/

    //перемещение задачи в раздел "не выполнено"
    Completed = new QListView(this);
    Completed->setDragEnabled(true);
    Completed->setAcceptDrops(true);
    Completed->setDropIndicatorShown(true);
    Completed->setDefaultDropAction(Qt::MoveAction);
    ui->pcLayout->addWidget(Completed);

    Pending->setModel(new QStringListModel());
    Completed->setModel(new QStringListModel());

    Pending->setStyleSheet
    ("QListView { font-size: 10pt; font-weight: bold; }"
     "QListView::item { background-color: #DCDCDC; padding: 7%;"
     "border: 1px solid #C0C0C0; }"
     "QListView::item::hover { background-color: #C0C0C0 }");

    Completed->setStyleSheet
    ("QListView { font-size: 10pt; font-weight: bold; }"
     "QListView::item { background-color: #98FB98; padding: 7%;"
     "border: 1px solid #90EE90; }"
     "QListView::item::hover { background-color: #90EE90 }");
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

    QList<Task*> tasks = fileManager->GetGroupTasks(current->text());
    qDebug() << "Количество задач в группе: " << tasks.length();
    for(int i = 0; i < tasks.length(); i++){
        qDebug() << "> [" << i << "] " << tasks[i]->name;
    }

    ui->selectedGroupName->setText(current->text()); // отображаем заголовок текущей группы
}

void MainWindow::on_addNewGroup_clicked()
{
    // добавление новой группы
    bool buttonOk;
    QString newGroupName = QInputDialog::getText(0, "Новая группа", "Введите название новой группы:", QLineEdit::Normal, "", &buttonOk);
    if (buttonOk && newGroupName.length() > 0) { // если нажата OK и введено имя
        ui->taskGroupsList->addItem(newGroupName); // добавляем новую группу в список
        TaskGroup* newGroup = new TaskGroup;
        newGroup->name = newGroupName;
        this->fileManager->groups.append(newGroup);
    }
}

void MainWindow::on_exitButton_released()
{
    QApplication::quit();
}

void MainWindow::on_calendar_clicked()
{
    qmlRegisterType<AddNewTaskDialog>("ToDo", 1, 0, "AddNewTask");
    AddNewTaskDialog *addNewTaskDialog = new AddNewTaskDialog(this->ui->calendar);
    QQuickView *view = new QQuickView;
//    view->setMinimumHeight(500);
//    view->setMinimumWidth(350);
    view->setResizeMode(QQuickView::SizeViewToRootObject);
    view->setSource(QUrl::fromLocalFile(":/AddNewTaskDialog.qml"));
    view->show();
    view->rootContext()->setContextProperty("addNewTask", addNewTaskDialog);
    addNewTaskDialog->fileManager = this->fileManager; // передаем указатель на file manager
    addNewTaskDialog->currentGroup = ui->taskGroupsList->currentItem()->text(); // сообщяем имя текущей группы
    addNewTaskDialog->view = view;
}


void MainWindow::on_AddButton_clicked()
{
    Pending->model()->insertRow(Pending->model()->rowCount()); //Вставляем пустую строчку
    QModelIndex oIndex = Pending->model()->index(
                Pending->model()->rowCount() - 1, 0);//получить последнюю строчку

    Pending->edit(oIndex);
}


void MainWindow::on_DeleteButton_clicked()
{
    QModelIndex oIndex = Pending->currentIndex();

    Pending->model()->removeRow(oIndex.row());
}

