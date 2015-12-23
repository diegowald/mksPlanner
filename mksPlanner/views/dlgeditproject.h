#ifndef DLGEDITPROJECT_H
#define DLGEDITPROJECT_H

#include <QDialog>

namespace Ui {
class dlgEditProject;
}

class dlgEditProject : public QDialog
{
    Q_OBJECT

public:
    explicit dlgEditProject(QWidget *parent = 0);
    ~dlgEditProject();

private:
    Ui::dlgEditProject *ui;
};

#endif // DLGEDITPROJECT_H
