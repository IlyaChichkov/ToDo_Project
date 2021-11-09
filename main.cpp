#include "mainwindow.h"
#include "filemanager.h"

#include <QApplication>

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileManager* fileManager = new FileManager(&a); // инициализируем файловый менеджер

    MainWindow w; // создание главного окна
    w.fileManager = fileManager; // передаем указатель на файловый менеджер
    w.SetGroupsListWidget(fileManager->GetGroupsNames()); // загрузка списка групп
    w.show();
    return a.exec();
}
