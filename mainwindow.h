#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFont>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDockWidget>

#include "controller.h"
#include "cholenmap.h"
#include "leftwidget.h"
#include "serialportassistant.h"
#include "lightinstructions.h"
#include "carinstructions.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    // 回到主界面(综合信息)
    void homeSlot(void);

    // 道路管控
    void roadControlSlot(void);

    // 流量监控
    void dataMonitorSlot(void);

    // 车辆定位
    void carLocationSlot(void);

    // 车辆控制
    void carControlSlot(void);

    // 点击应用槽函数
    void applySlot(void);

private:
    Ui::MainWindow *ui;
    // 控制面板组件Widget
    Controller* controllerWidget;

    // 控制面板QDockWidget
    QDockWidget* controllerPanel;

    // 左边控件
    LeftWidget* leftWidget;

    // 主布局
    QHBoxLayout* mainlayout;

    // 地图
    CholenMap* map;




private:
    // 设置显示大小
    void setSize(void);

    // 一次性连接所有信号
    void setSignalConnection(void);



};

#endif // MAINWINDOW_H
