#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "trie.h"

class Controller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList nomalQuery       READ nomalQuery         NOTIFY nomalQueryChanged)
    Q_PROPERTY(QStringList nomalTime        READ nomalTime          NOTIFY nomalTimeChanged)
    Q_PROPERTY(QStringList trieQuery       READ trieQuery         NOTIFY trieQueryChanged)
    Q_PROPERTY(QStringList trieTime        READ trieTime          NOTIFY trieTimeChanged)

public:
    explicit Controller(QObject *parent = nullptr);

    QStringList nomalQuery() {return m_nomalQuery;};
    QStringList nomalTime() {return m_nomalTime;};
    QStringList trieQuery() {return m_trieQuery;};
    QStringList trieTime() {return m_trieTime;};

    void convertObjectToArray();
    void readNomal(QJsonArray &data, int count);
    void readTrie(QJsonArray &data, int count);
    void queryNomal(QString query);
    void queryTrie(QString query);

    Q_INVOKABLE void readDatabase(int count);
    Q_INVOKABLE void queryData(QString query);

signals:
    void nomalQueryChanged();
    void nomalTimeChanged();
    void trieQueryChanged();
    void trieTimeChanged();

private:
    QStringList m_database;
    QStringList m_nomalQuery;
    QStringList m_nomalTime;
    QStringList m_trieQuery;
    QStringList m_trieTime;
    Trie m_trie;
    int m_count;
};

#endif // CONTROLLER_H
