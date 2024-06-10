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
    m_trieTime = QStringList();
    m_trieQuery = QStringList();
    m_count = 1;
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

void Controller::readNomal(QJsonArray &data, int count)
{
    QElapsedTimer timer;
    timer.start();

    m_database.clear();
    int index = 0;
    for (const QJsonValue &value : data) {
        if(index >= count) {
            break;
        } else {
            m_database.append(value.toString());
            index++;
        }
    }
    m_nomalTime.append(QString::number(m_count) + ". LOAD: " + QString::number(timer.nsecsElapsed()/1000000.0000) + " (ms)");
    emit nomalTimeChanged();
}

void Controller::readTrie(QJsonArray &data, int count)
{
    QElapsedTimer timer;
    timer.start();

    m_trie.clear();
    int index = 0;
    for (const QJsonValue &value : data) {
        if(index >= count) {
            break;
        } else {
            m_trie.append(value.toString());
            index++;
        }
    }
    m_trieTime.append(QString::number(m_count) + ". LOAD: " + QString::number(timer.nsecsElapsed()/1000000.0000) + " (ms)");
    emit trieTimeChanged();
}

void Controller::queryNomal(QString query)
{
    QElapsedTimer timer;
    timer.start();

    for (const QString &str : m_database) {
        if(str.startsWith(query))
            m_nomalQuery.append(str);
    }

    m_nomalTime.append(QString::number(m_count) + ". SEARCH: " + QString::number(timer.nsecsElapsed()/1000000.0000) + " (ms)");
    emit nomalQueryChanged();
    emit nomalTimeChanged();
}

void Controller::queryTrie(QString query)
{
    QElapsedTimer timer;
    timer.start();

    m_trieQuery = m_trie.search(query);

    m_trieTime.append(QString::number(m_count) + ". SEARCH: " + QString::number(timer.nsecsElapsed()/1000000.0000) + " (ms)");
    emit trieQueryChanged();
    emit trieTimeChanged();
}

void Controller::readDatabase(int count)
{
    //QString path = "D:/test_trie/data.json";
    QString path = "C:/Users/TT/Desktop/NCT/test_trie/data.json";

    QFile file(path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open file: " << path;
        return;
    }
    QString str = file.readAll();
    QJsonArray data = QJsonDocument::fromJson(str.toUtf8()).array();

    readNomal(data, count);
    readTrie(data, count);

    m_count++;
    file.close();
    qDebug() << "Load database successfully!";
}

void Controller::queryData(QString query)
{
    m_nomalQuery.clear();
    m_trieQuery.clear();
    if(query.isEmpty())
        return;

    queryNomal(query);
    queryTrie(query);

    m_count++;
}
