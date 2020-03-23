#ifndef CHOLENMAP_H
#define CHOLENMAP_H

#include <QWidget>
#include <QPixmap>
#include <QPaintEvent>
#include <QHash>
#include <QPoint>
#include <QTimer>

#include "serialportassistant.h"

class CholenMap : public QWidget
{
    Q_OBJECT
public:
    explicit CholenMap(QWidget *parent = 0);

signals:

public slots:
    // 显示串口通信助手
    void showSerialPortAssistant(void);

    void updateMap(void);

private:
    QPixmap                homePixmap;
    QPixmap                mapPixmap;
    QPixmap                carPixmap;
    QHash<QString, QPoint> hashMap;
    QTimer                 updateTimer;

    QString                currentLocation;
    QString                currentLightStatus;
public:
    // showStatus 表示按下不同按钮后显示的不同界面  默认为0
    // 0----->综合信息  000
    // 1----->道路管控  001
    // 2----->流量监控  010
    // 3----->车辆定位  100
    // 4----->车辆控制  111
    int                   showStatus[3];




public:
    // 串口助手
    SerialPortAssistant* serialportassistant;


protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);



private:
    // 构建哈希表  电子地图 设置hashMap
    void createHashMap(void);

    // 获得小车的位置
    QPoint getLocation(QString);




};

#endif // CHOLENMAP_H
