#include "controller.h"
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QElapsedTimer>

Controller::Controller(QObject *parent) : QObject(parent)
{
    readDatabase(300);
    m_nomalTime = QStringList();
    m_nomalQuery = QStringList();
    m_count = 0;
}

void Controller::convertObjectToArray()
{
    QString pathObject = "D:/test_trie/dataobj.json";
    QString pathArray = "D:/test_trie/data.json";

    QFile fileObj(pathObject);
    if(!fileObj.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open file: " << pathObject;
        return;
    }
    QString str = fileObj.readAll();
    QJsonObject dataObj = QJsonDocument::fromJson(str.toUtf8()).object();
    fileObj.close();

    QJsonArray dataArr;
    for (const QString &str : dataObj.keys()) {
        dataArr.append(str);
    }

    QFile fileArr(pathArray);
    if(!fileArr.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open file: " << pathArray;
        return;
    }
    QJsonDocument dataDoc(dataArr);
    fileArr.write(dataDoc.toJson());
    fileArr.close();

    qDebug() << "Convert JsonObject to JsonArray successfully!";
}

void Controller::readDatabase(int count)
{
    QString path = "D:/test_trie/data.json";

    QFile file(path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open file: " << path;
        return;
    }
    QString str = file.readAll();
    QJsonArray dataArr = QJsonDocument::fromJson(str.toUtf8()).array();

    file.close();

    m_database.clear();
    int index = 0;
    for (const QJsonValue &value : dataArr) {
        if(index >= count) {
            break;
        } else {
            m_database.append(value.toString());
            index++;
        }
    }
    qDebug() << "Load database successfully!";
}

void Controller::queryData(QString query)
{
    m_nomalQuery.clear();
    if(query.isEmpty())
        return;

    QElapsedTimer timer;
    timer.start();
    for (const QString &str : m_database) {
        if(str.contains(query))
            m_nomalQuery.append(str);
    }

    m_nomalTime.append(QString::number(m_count) + ". SEARCH: " + QString::number(timer.nsecsElapsed()) + " (nanosecond)");
    m_count++;
    emit nomalQueryChanged();
    emit nomalTimeChanged();
}
