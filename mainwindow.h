#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QLabel>
#include <QInputDialog>

#include "filemanager.h"
#include "addnewtaskdialog.h"
#include "addedittask.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    FileManager* fileManager;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void SetGroupsListWidget(QList<QString> groupNames);
private slots:

    void on_taskGroupsList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_exitButton_released();

    void on_addNewGroup_clicked();

    void on_addNewTask_clicked();

    void on_EditTask_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
