#include "leftwidget.h"
#include "ui_leftwidget.h"

LeftWidget::LeftWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LeftWidget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
}

LeftWidget::~LeftWidget()
{
    delete ui;
}

QPushButton *LeftWidget::getBtnCarControl()
{
    return ui->BtnCarControl;
}

QPushButton *LeftWidget::getBtnCarLacation()
{
    return ui->BtnCarLocation;
}

QPushButton *LeftWidget::getBtnDataMonitor()
{
    return ui->BtnDataMonitor;
}

QPushButton *LeftWidget::getBtnHome()
{
    return ui->BtnHome;
}

QPushButton *LeftWidget::getBtnRoadControl()
{
    return ui->BtnRoadControl;
}
