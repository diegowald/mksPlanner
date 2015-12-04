#ifndef UNIT_H
#define UNIT_H

#include <QObject>

class Unit : public QObject
{
    Q_OBJECT
public:
    explicit Unit(QObject *parent = 0);

signals:

public slots:

private:
    int _id;
    QString _name;
    QString _description;
};

#endif // UNIT_H
