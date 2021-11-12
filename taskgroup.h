#ifndef TASKGROUP_H
#define TASKGROUP_H

#include <QObject>
#include <task.h>

class TaskGroup : public QObject
{
    Q_OBJECT
public:
    explicit TaskGroup(QObject *parent = nullptr);
    ~TaskGroup();

    QString name;
    QList<Task*> tasks;

signals:

};

#endif // TASKGROUP_H
