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
    void scriptsVersion2();
    void scriptsVersion3();
    void scriptsVersion4();
    void scriptsVersion5();
    void scriptsVersion6();

};

#endif // PROJECTUPDATER_H
