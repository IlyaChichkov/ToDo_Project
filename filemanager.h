#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QList>

#include <QFile>
#include <QCoreApplication>
#include <QTextStream>
#include <QDir>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include <taskgroup.h>
#include <task.h>

#include <QDebug>

class FileManager : public QObject
{
    Q_OBJECT
private:
    QString fileName = "data.json";
    void CreateStandartDataFile();
public:
    QList<TaskGroup*> groups;

    explicit FileManager(QObject *parent = nullptr);
    ~FileManager();

    QList<TaskGroup*> LoadData();
    QList<QString> GetGroupsNames();
    QList<Task*> GetGroupTasks(QString groupName);

signals:

};

#endif // FILEMANAGER_H
