#include "mainwindow.h"
#include "filemanager.h"

#include <QApplication>

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    FileManager* fileManager = new FileManager();

    w.SetGroupsByList(fileManager->GetGroupsNames());

    return a.exec();
}
