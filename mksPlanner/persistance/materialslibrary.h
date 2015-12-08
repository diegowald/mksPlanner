#ifndef MATERIALSLIBRARY_H
#define MATERIALSLIBRARY_H

#include <QObject>
#include "persistance/librarybase.h"

class MaterialsLibrary : public LibraryBase
{
    Q_OBJECT
public:
    explicit MaterialsLibrary(QObject *parent = 0);

signals:

public slots:
};

#endif // MATERIALSLIBRARY_H
