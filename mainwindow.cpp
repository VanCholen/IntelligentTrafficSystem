#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopWidget>
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPoint>
#include <QSplitter>
#include <QSpacerItem>
#include <QByteArray>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 设置主窗口大小
    this->setSize();

    // 右侧控制面板设计
    controllerPanel = new QDockWidget(tr("控制面板"), this);
    controllerWidget = new Controller(this);
    controllerPanel->setWidget(controllerWidget);
    controllerPanel->setFeatures(QDockWidget::NoDockWidgetFeatures);
    controllerPanel->setAllowedAreas(Qt::RightDockWidgetArea);
    controllerPanel->setFixedWidth(300);
    this->addDockWidget(Qt::RightDockWidgetArea, controllerPanel);
    controllerPanel->setVisible(true);


    //创建左边组件
    leftWidget = new LeftWidget();
    // 创建主布局
    mainlayout = new QHBoxLayout();
    mainlayout->addWidget(leftWidget);
    map = new CholenMap();
    map->setGeometry(0,0,map->size().width(),map->size().height());

//    mainlayout->addWidget(map);
    // 调用setStretchFactor函数用于设定可伸缩控件，第一个参数是指定设置的控件序号，
    // 控件序号按对象中控件插入的先后次序从0开始依次编号；第二个参数是一个大于0的值，表示此控件为可伸缩控件。
//    mainlayout->setStretchFactor(leftWidget, 1);
//    mainlayout->setStretchFactor(map, 8);
    QVBoxLayout* midLayout = new QVBoxLayout();
    midLayout->addWidget(map);
    mainlayout->addLayout(midLayout);
    mainlayout->setStretchFactor(leftWidget, 1);
    mainlayout->setStretchFactor(midLayout, 8);
//    QSpacerItem* horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
//    mainlayout->addItem(horizontalSpacer);

    ui->centralWidget->setLayout(mainlayout);

    //qDebug()<<map->size();    // QSize(640, 480)






    controllerWidget->setMap(map);



    // 一次性连接所有槽函数
    this->setSignalConnection();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::homeSlot()
{
    this->controllerWidget->getDataCheckBox()->setCheckState(Qt::Unchecked);
    this->controllerWidget->getLocationCheckBox()->setChecked(Qt::Unchecked);
    this->controllerWidget->getRoadCheckBox()->setChecked(Qt::Unchecked);
    for(int i=0;i<3;i++){
        this->map->showStatus[i] = 0;
    }
    this->map->update();
}

void MainWindow::roadControlSlot()
{
    this->controllerWidget->getDataCheckBox()->setCheckState(Qt::Unchecked);
    this->controllerWidget->getLocationCheckBox()->setChecked(Qt::Unchecked);
    this->controllerWidget->getRoadCheckBox()->setChecked(Qt::Checked);
    this->map->showStatus[0] = 1;
    this->map->showStatus[1] = 0;
    this->map->showStatus[2] = 0;
    this->map->update();
}

void MainWindow::dataMonitorSlot()
{
    this->controllerWidget->getDataCheckBox()->setCheckState(Qt::Checked);
    this->controllerWidget->getLocationCheckBox()->setChecked(Qt::Unchecked);
    this->controllerWidget->getRoadCheckBox()->setChecked(Qt::Unchecked);
    this->map->showStatus[0] = 0;
    this->map->showStatus[1] = 1;
    this->map->showStatus[2] = 0;
    this->map->update();
}

void MainWindow::carLocationSlot()
{
    this->controllerWidget->getDataCheckBox()->setCheckState(Qt::Unchecked);
    this->controllerWidget->getLocationCheckBox()->setChecked(Qt::Checked);
    this->controllerWidget->getRoadCheckBox()->setChecked(Qt::Unchecked);
    this->map->showStatus[0] = 0;
    this->map->showStatus[1] = 0;
    this->map->showStatus[2] = 1;
    this->map->update();
}

void MainWindow::carControlSlot()
{
    this->controllerWidget->getDataCheckBox()->setCheckState(Qt::Unchecked);
    this->controllerWidget->getLocationCheckBox()->setChecked(Qt::Unchecked);
    this->controllerWidget->getRoadCheckBox()->setChecked(Qt::Unchecked);
    this->map->showStatus[0] = 1;
    this->map->showStatus[1] = 1;
    this->map->showStatus[2] = 1;
    this->map->update();
}

void MainWindow::applySlot()
{
    QString roadSelectText = this->controllerWidget->getRoadSelectCombox()->currentText();
    QString modeSelectText = this->controllerWidget->getModeSelectCombox()->currentText();
    QString lightTimeSelectText = this->controllerWidget->getLightTimeSelectCombox()->currentText();
    QString roadNum = (QString)roadSelectText.at(2);
    QString num = (QString)lightTimeSelectText.at(2)+(QString)lightTimeSelectText.at(3);
    //this->map->serialportassistant->port.isOpen()
    if(this->map->serialportassistant->port.isOpen()){ // 端口打开
        // 构建灯的指令  来改变灯的状态
        LightInstructions ins(roadNum, num);

        // 发送灯的指令
        this->map->serialportassistant->port.write(ins.getInstruction());

    }
}








void MainWindow::setSize()
{
    this->move(QPoint(10, 10));
    QDesktopWidget* desktop = QApplication::desktop();
    //获取主屏幕分辨率
    QRect screenRect = desktop->screenGeometry();
    this->setFixedSize(screenRect.width()-450, screenRect.height()-200);
//    this->setFixedSize(screenRect.size().width(), screenRect.size().height());
}

void MainWindow::setSignalConnection()
{
    // 连接综合信息槽函数
    connect(leftWidget->getBtnHome(), SIGNAL(clicked()), this, SLOT(homeSlot()));

    // 连接道路管控槽函数
    connect(leftWidget->getBtnRoadControl(), SIGNAL(clicked()), this, SLOT(roadControlSlot()));

    // 连接流量监控槽函数
    connect(leftWidget->getBtnDataMonitor(), SIGNAL(clicked()), this, SLOT(dataMonitorSlot()));

    // 连接车辆定位槽函数
    connect(leftWidget->getBtnCarLacation(), SIGNAL(clicked()), this, SLOT(carLocationSlot()));

    // 连接车辆控制槽函数
    connect(leftWidget->getBtnCarControl(), SIGNAL(clicked()), this, SLOT(carControlSlot()));

    //
    connect(ui->actionConnect, SIGNAL(triggered()), map, SLOT(showSerialPortAssistant()));

    // 连接应用按钮和槽函数
    connect(this->controllerWidget->getApplyBtn(), SIGNAL(clicked()), this, SLOT(applySlot()));

}

