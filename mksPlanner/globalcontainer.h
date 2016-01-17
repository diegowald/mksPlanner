#ifndef GLOBALCONTAINER_H
#define GLOBALCONTAINER_H

#include <QObject>
#include "persistance/materialslibrary.h"
#include "persistance/projectlibrary.h"
#include <QMap>


class GlobalContainer : public QObject
{
    Q_OBJECT
public:
    static GlobalContainer &instance();
    static void initialize();
    static void finalize();

    void setMaterialLibrary(MaterialsLibrary *materialLibrary);
    MaterialsLibrary *materialLibrary() const;

    int createProject();
    int loadProject(const QString &filename);
    ProjectLibrary *projectLibrary(int id) const;

    int counter(const QString &counterName);
    void setCounter(const QString &counterName, int value);

private:
    explicit GlobalContainer(QObject *parent = 0);

signals:

public slots:

private:
    static GlobalContainer *_instance;

    MaterialsLibrary *_materialLibrary;
    QMap<QString, int> _counter;
    QList<ProjectLibrary *> _projectLibraries;
};

#endif // GLOBALCONTAINER_H
