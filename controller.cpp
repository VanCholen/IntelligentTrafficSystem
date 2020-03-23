#include "controller.h"
#include "ui_controller.h"
#include<QDebug>

Controller::Controller(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Controller)
{
    ui->setupUi(this);

    connect(ui->checkBoxRoadInfo, SIGNAL(clicked()), this, SLOT(checkedRoadInfo()));
    connect(ui->checkBoxDataInfo, SIGNAL(clicked()), this, SLOT(checkedDataInfo()));
    connect(ui->checkBoxLocationInfo, SIGNAL(clicked()), this, SLOT(checkedLocationInfo()));
}

Controller::~Controller()
{
    delete ui;
}

void Controller::checkedRoadInfo()
{
    if(ui->checkBoxRoadInfo->isChecked()){
        this->map->showStatus[0] = 1;
    }else{
        this->map->showStatus[0] = 0;
//        qDebug()<<this->map->showStatus[0];
    }
}

void Controller::checkedDataInfo()
{
    if(ui->checkBoxDataInfo->isChecked()){
        this->map->showStatus[1] = 1;
    }else{
        this->map->showStatus[1] = 0;
    }
}

void Controller::checkedLocationInfo()
{
    if(ui->checkBoxLocationInfo->isChecked()){
        this->map->showStatus[2] = 1;
    }else{
        this->map->showStatus[2] = 0;
    }
}

void Controller::setMap(CholenMap *map)
{
    this->map = map;
}

QCheckBox *Controller::getLocationCheckBox()
{
    return this->ui->checkBoxLocationInfo;
}

QCheckBox *Controller::getDataCheckBox()
{
    return this->ui->checkBoxDataInfo;
}

QCheckBox *Controller::getRoadCheckBox()
{
    return this->ui->checkBoxRoadInfo;
}

QComboBox *Controller::getLightTimeSelectCombox()
{
    return this->ui->lightTimeSelectCB;
}

QLineEdit *Controller::getShowLineEdit()
{
    return this->ui->lineEditShowInstructions;
}

QPushButton *Controller::getApplyBtn()
{
    return this->ui->applyBtn;
}

QComboBox *Controller::getRoadSelectCombox()
{
    return this->ui->roadSelectCB;
}

QComboBox *Controller::getModeSelectCombox()
{
    return this->ui->modeSelectCB;
}
