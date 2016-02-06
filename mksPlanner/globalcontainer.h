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

    void setLibrary(MaterialsLibrary *library);
    MaterialsLibrary *library() const;

    int createProject(const QString &filename);
    int loadProject(const QString &filename);
    ProjectLibrary *projectLibrary(int id) const;

    int counter(const QString &counterName);
    void setCounter(const QString &counterName, int value);

    bool unsavedProjects() const;
    void saveAllProjects();

private:
    explicit GlobalContainer(QObject *parent = 0);

signals:

public slots:

private:
    static GlobalContainer *_instance;

    MaterialsLibrary *_library;
    QMap<QString, int> _counter;
    QList<ProjectLibrary *> _projectLibraries;
};

#endif // GLOBALCONTAINER_H
