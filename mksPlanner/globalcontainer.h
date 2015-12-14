#ifndef GLOBALCONTAINER_H
#define GLOBALCONTAINER_H

#include <QObject>
#include "persistance/materialslibrary.h"
#include <QMap>

class GlobalContainer : public QObject
{
    Q_OBJECT
public:
    static GlobalContainer &instance();

    void setMaterialLibrary(MaterialsLibrary *materialLibrary);
    MaterialsLibrary *materialLibrary() const;

    int counter(const QString &counterName);
    void setCounter(const QString &counterName, int value);

private:
    explicit GlobalContainer(QObject *parent = 0);

signals:

public slots:

private:
    static GlobalContainer _instance;

    MaterialsLibrary *_materialLibrary;
    QMap<QString, int> _counter;
};

#endif // GLOBALCONTAINER_H
