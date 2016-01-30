#ifndef MATERIALESUPDATER_H
#define MATERIALESUPDATER_H

#include "persistance/updater.h"

class MaterialesUpdater : public Updater
{
    Q_OBJECT
public:
    explicit MaterialesUpdater(QObject *parent = 0);

    void scriptsVersion1();
    void scriptsVersion2();
};

#endif // MATERIALESUPDATER_H
