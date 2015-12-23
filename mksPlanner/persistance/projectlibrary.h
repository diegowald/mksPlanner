#ifndef PROJECTLIBRARY_H
#define PROJECTLIBRARY_H

#include <QObject>
#include "persistance/librarybase.h"


class ProjectLibrary : public LibraryBase
{
    Q_OBJECT
public:
    explicit ProjectLibrary(QObject *parent = 0);

protected:
    virtual void internalSaveTables(const QString &filename);
    virtual void internalLoadTables(const QString &filename);

signals:

public slots:
};

#endif // PROJECTLIBRARY_H
