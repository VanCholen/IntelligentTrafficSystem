#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>

#include "cholenmap.h"

namespace Ui {
class Controller;
}

class Controller : public QWidget
{
    Q_OBJECT

public:
    explicit Controller(QWidget *parent = 0);
    ~Controller();

private:
    Ui::Controller *ui;
    CholenMap* map;

public slots:
    void checkedRoadInfo(void);
    void checkedDataInfo(void);
    void checkedLocationInfo(void);
//    void

public:
    void setMap(CholenMap*);
    QCheckBox* getLocationCheckBox(void);
    QCheckBox* getDataCheckBox(void);
    QCheckBox* getRoadCheckBox(void);
    QPushButton* getApplyBtn(void);
    QComboBox* getRoadSelectCombox(void);
    QComboBox* getModeSelectCombox(void);
    QComboBox* getLightTimeSelectCombox(void);
    QLineEdit* getShowLineEdit(void);
};

#endif // CONTROLLER_H
