#ifndef GLOBALCONTAINER_H
#define GLOBALCONTAINER_H

#include <QObject>
#include "persistance/materialslibrary.h"

class GlobalContainer : public QObject
{
    Q_OBJECT
public:
    static GlobalContainer &instance();

    void setMaterialLibrary(MaterialsLibrary *materialLibrary);
    MaterialsLibrary *materialLibrary() const;
private:
    explicit GlobalContainer(QObject *parent = 0);

signals:

public slots:

private:
    static GlobalContainer _instance;

    MaterialsLibrary *_materialLibrary;
};

#endif // GLOBALCONTAINER_H
