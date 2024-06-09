#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

class Controller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList nomalQuery       READ nomalQuery         NOTIFY nomalQueryChanged)
    Q_PROPERTY(QStringList nomalTime        READ nomalTime          NOTIFY nomalTimeChanged)

public:
    explicit Controller(QObject *parent = nullptr);

    QStringList nomalQuery() {return m_nomalQuery;};
    QStringList nomalTime() {return m_nomalTime;};

    void convertObjectToArray();
    Q_INVOKABLE void readDatabase(int count);
    Q_INVOKABLE void queryData(QString query);

signals:
    void nomalQueryChanged();
    void nomalTimeChanged();

private:
    QStringList m_database;
    QStringList m_nomalQuery;
    QStringList m_nomalTime;
    int m_count;
};

#endif // CONTROLLER_H
