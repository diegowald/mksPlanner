#ifndef PROJECTUPDATER_H
#define PROJECTUPDATER_H

#include "persistance/updater.h"

class ProjectUpdater : public Updater
{
    Q_OBJECT
public:
    explicit ProjectUpdater(QObject *parent = 0);

private:
    void scriptsVersion1();

};

#endif // PROJECTUPDATER_H
