#include "taskgroup.h"
#include <QtAlgorithms>

TaskGroup::TaskGroup(QObject *parent) : QObject(parent)
{

}

TaskGroup::~TaskGroup()
{
    qDeleteAll(tasks);
    tasks.clear();
}
