#include "filemanager.h"
#include "mainwindow.h"
#include <QtAlgorithms>

FileManager::FileManager(QObject *parent) : QObject(parent) // конструктор
{
    qDebug() << "File Manager Created!";
    LoadData();
}

FileManager::~FileManager() // деструктор
{
    qDeleteAll(this->groups);
    this->groups.clear();
    qDebug() << "File Manager Deleted!";
}

QList<TaskGroup*> FileManager::LoadData()
{
    qDebug() << "Loading Data...";
    QFile dataFile(this->fileName);

    if(!dataFile.exists()){ // файл с данными не найден
        qDebug() << "File do not exist";
        CreateStandartDataFile();
    }

    dataFile.open(QIODevice::ReadOnly | QIODevice::Text); // открываем файл для чтения
    QByteArray saveData = dataFile.readAll(); // сохраняем в массив

    QJsonDocument jsonDocument(QJsonDocument::fromJson(saveData)); // формируем JSON документ
    QJsonValue jgroups = jsonDocument.object().value("groups"); // выбираем элемент
    QJsonArray jgroupsArray = jgroups.toArray(); // читаем массив элемента
    foreach (const QJsonValue & value, jgroupsArray) {
        QJsonObject jgroup = value.toObject(); // получаем элемент массива

        TaskGroup* loadedGroup = new TaskGroup(); // создаем группу
        loadedGroup->name = jgroup["name"].toString(); // присваиваем имя из файла сохранения
        QJsonArray jtasksArray = jgroup.value("tasks").toArray(); // читаем массив элемента

        for(int i = 0; i < jtasksArray.count(); i++){ // перебираем все задачи в группе
            QJsonObject jtask = jtasksArray[i].toObject();
            Task* loadedTask = new Task();
            loadedTask->name = jtask["name"].toString();
            loadedTask->desc = jtask["desc"].toString();
            loadedGroup->tasks.append(loadedTask); // добавляем задачу в список задач группы
        }
        this->groups.append(loadedGroup); // добавляем группу в список
    }

    dataFile.close();
    return this->groups;
}

QList<QString> FileManager::GetGroupsNames()
{
    QList<QString> groupsNames;

    for(int i = 0; i < this->groups.length(); i++){
        groupsNames.append(this->groups[i]->name);
    }

    return groupsNames;
}

QList<Task *> FileManager::GetGroupTasks(QString groupName)
{
    QList<Task *> tasks;
    for(int i = 0; i < this->groups.length(); i++){
        // qDebug() << "Check group: " << this->groups[i]->name;
        if(this->groups[i]->name == groupName){ // проверяем имя группы
            tasks = (this->groups[i]->tasks);
        }
    }
    return tasks;
}

void FileManager::AddTaskToGroup(QString groupName, Task *task)
{
    for(int i = 0; i < this->groups.length(); i++){
        if(this->groups[i]->name == groupName){ // проверяем имя группы
            this->groups[i]->tasks.append(task);
        }
    }
}

void FileManager::SaveData()
{
    qDebug() << "Saving Data...";
    QFile dataFile(this->fileName);
    dataFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream iStream(&dataFile); // открываем поток

    QJsonObject root;

    QJsonArray groupsList;

    // создание групп
    for(int i = 0; i < groups.length(); i++){
        // создание задач в группе
        TaskGroup* currentGroup = groups[i];
        QJsonArray tasksList;
        for(int j = 0; j < currentGroup->tasks.length(); j++){
            qDebug() << "Groups creating";
            QJsonObject task{
                {"name", currentGroup->tasks[j]->name},
                {"desc", currentGroup->tasks[j]->desc}
            };
            tasksList.append(task);
        }
        qDebug() << "Groups creating";
        QJsonObject group{
            {"name", currentGroup->name},
            {"tasks", tasksList}
        };
        groupsList.append(group);
    }

    /*
    QJsonArray groupsList;
    QJsonObject group;
    QJsonArray tasks;
    QJsonObject task;
    // создаем стандартную задачу (приветствие)
    task.insert("name", "Первая задача");
    task.insert("desc", "В данном окне будут отображаться ваши задачи.");
    tasks.append(task);
    group.insert("name", "Добро пожаловать");
    group.insert("tasks", tasks);

    groupsList.append(group); */
    root.insert("groups", groupsList);

    QJsonDocument document;
    document.setObject(root);
    QByteArray bytes = document.toJson( QJsonDocument::Indented );

    iStream << bytes;
    dataFile.close(); // закрываем файл
}

void FileManager::CreateStandartDataFile()
{
    QFile dataFile(this->fileName);
    dataFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream iStream(&dataFile); // открываем поток

    QJsonObject root;
    QJsonArray groupsList;
    QJsonObject group;
    QJsonArray tasks;
    QJsonObject task;
    // создаем стандартную задачу (приветствие)
    task.insert("name", "Первая задача");
    task.insert("desc", "В данном окне будут отображаться ваши задачи.");
    tasks.append(task);
    group.insert("name", "Добро пожаловать");
    group.insert("tasks", tasks);

    groupsList.append(group);
    root.insert("groups", groupsList);

    QJsonDocument document;
    document.setObject(root);
    QByteArray bytes = document.toJson( QJsonDocument::Indented );

    iStream << bytes; // записываем данные
    dataFile.close(); // закрываем файл
}


