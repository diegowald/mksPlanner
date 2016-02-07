#ifndef PROJECTLIBRARY_H
#define PROJECTLIBRARY_H

#include <QObject>
#include "persistance/librarybase.h"


class ProjectLibrary : public LibraryBase
{
    Q_OBJECT
public:
    explicit ProjectLibrary(const QString &filename, int idProyecto, bool nuevo, QObject *parent = 0);

protected:
    virtual void internalSaveTables(const QString &filename);
    virtual void internalLoadTables(const QString &filename);
    virtual void updateFromVersion(const QString &filename, const QString &versionInfo);

signals:

public slots:
private:
    int _idProyecto;
};

#endif // PROJECTLIBRARY_H
