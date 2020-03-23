#include "cholenmap.h"
#include <QPainter>
#include <QRect>
#include <QPen>
#include <QColor>


#include<QDebug>


CholenMap::CholenMap(QWidget *parent) : QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    serialportassistant = new SerialPortAssistant();

    // 设置默认显示Home综合信息
    for(int i=0;i<3;i++){
        showStatus[i] = 0;
    }

    homePixmap.load(":/images/pic.png");
    mapPixmap.load(":/images/map.png");
    mapPixmap.scaled(this->size());
    carPixmap.load(":/images/car1.png");


    // 构建电子地图
    this->createHashMap();


    // 初始化小车当前位置
    currentLocation = "-1";

    // 初始化红绿灯状态
    currentLightStatus = "-1";


    // 界面刷新计时
    updateTimer.start(100);


    // 刷新界面
    connect(&updateTimer, SIGNAL(timeout()), this, SLOT(updateMap()));
}

void CholenMap::showSerialPortAssistant()
{
    this->serialportassistant->show();
}

void CholenMap::updateMap()
{
    repaint();
}

void CholenMap::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    // 抗锯齿
    painter.setRenderHint(QPainter::Antialiasing);
    QColor redColor(Qt::red);
    QColor greenColor(Qt::green);
    QBrush redBrush(Qt::red);
    QBrush greenBrush(Qt::green);


    int status = showStatus[0] + showStatus[1]*10 + showStatus[2]*100;
    // 绘制Home主界面    综合信息
    if(status==0){
        // 绘制背景地图
        painter.drawPixmap(0, 0, width(), height(), homePixmap);
    }

    // 绘制道路管控界面  路口信息(即红绿灯信息)
    if(status==1){
        // 绘制背景地图
        painter.drawPixmap(0, 0, width(), height(), mapPixmap);

        if(currentLightStatus=="-1"){

        }else{// 绘图
            if(currentLightStatus=="1"){ //水平绿灯亮
                painter.setPen(redColor);
                painter.setBrush(redBrush);
                QRect rect(470, 10, 60, 10);// 中间往下平移345
                painter.drawRect(rect);
                rect.moveTopLeft(QPoint(470, 60));
                painter.drawRect(rect);
                rect.moveTopLeft(QPoint(470, 355));
                painter.drawRect(rect);
                rect.moveTopLeft(QPoint(470, 405));
                painter.drawRect(rect);
                rect.moveTopLeft(QPoint(470, 700));
                painter.drawRect(rect);
                rect.moveTopLeft(QPoint(470, 745));
                painter.drawRect(rect);

                rect.moveTopLeft(QPoint(25, 355));
                painter.drawRect(rect);
                rect.moveTopLeft(QPoint(930, 355));
                painter.drawRect(rect);
                rect.moveTopLeft(QPoint(25, 405));
                painter.drawRect(rect);
                rect.moveTopLeft(QPoint(930, 405));
                painter.drawRect(rect);


                painter.setPen(greenColor);
                painter.setBrush(greenBrush);
                QRect rect1(455, 20, 15, 40);
                painter.drawRect(rect1);
                rect1.moveTopLeft(QPoint(530, 20));
                painter.drawRect(rect1);
                rect1.moveTopLeft(QPoint(455, 365));
                painter.drawRect(rect1);
                rect1.moveTopLeft(QPoint(530, 365));
                painter.drawRect(rect1);
                rect1.moveTopLeft(QPoint(455, 710));
                painter.drawRect(rect1);
                rect1.moveTopLeft(QPoint(530, 710));
                painter.drawRect(rect1);

                rect1.moveTopLeft(QPoint(10, 365));
                painter.drawRect(rect1);
                rect1.moveTopLeft(QPoint(85, 365));
                painter.drawRect(rect1);
                rect1.moveTopLeft(QPoint(915, 365));
                painter.drawRect(rect1);
                rect1.moveTopLeft(QPoint(990, 365));
                painter.drawRect(rect1);
            }else if(currentLightStatus=="0"){ // 水平红灯亮
                painter.setPen(greenColor);
                painter.setBrush(greenBrush);
                QRect rect(470, 10, 60, 10);// 中间往下平移345
                painter.drawRect(rect);
                rect.moveTopLeft(QPoint(470, 60));
                painter.drawRect(rect);
                rect.moveTopLeft(QPoint(470, 355));
                painter.drawRect(rect);
                rect.moveTopLeft(QPoint(470, 405));
                painter.drawRect(rect);
                rect.moveTopLeft(QPoint(470, 700));
                painter.drawRect(rect);
                rect.moveTopLeft(QPoint(470, 745));
                painter.drawRect(rect);

                rect.moveTopLeft(QPoint(25, 355));
                painter.drawRect(rect);
                rect.moveTopLeft(QPoint(930, 355));
                painter.drawRect(rect);
                rect.moveTopLeft(QPoint(25, 405));
                painter.drawRect(rect);
                rect.moveTopLeft(QPoint(930, 405));
                painter.drawRect(rect);


                painter.setPen(redColor);
                painter.setBrush(redBrush);
                QRect rect1(455, 20, 15, 40);
                painter.drawRect(rect1);
                rect1.moveTopLeft(QPoint(530, 20));
                painter.drawRect(rect1);
                rect1.moveTopLeft(QPoint(455, 365));
                painter.drawRect(rect1);
                rect1.moveTopLeft(QPoint(530, 365));
                painter.drawRect(rect1);
                rect1.moveTopLeft(QPoint(455, 710));
                painter.drawRect(rect1);
                rect1.moveTopLeft(QPoint(530, 710));
                painter.drawRect(rect1);

                rect1.moveTopLeft(QPoint(10, 365));
                painter.drawRect(rect1);
                rect1.moveTopLeft(QPoint(85, 365));
                painter.drawRect(rect1);
                rect1.moveTopLeft(QPoint(915, 365));
                painter.drawRect(rect1);
                rect1.moveTopLeft(QPoint(990, 365));
                painter.drawRect(rect1);
            }

        }




        currentLightStatus = serialportassistant->lightHeart->status;





    }

    // 绘制流量监控界面
    if(status==10){
        // 绘制背景地图
        painter.drawPixmap(0, 0, width(), height(), mapPixmap);


        painter.setPen(greenColor);
        painter.setBrush(greenBrush);
        QRect rect(115, 15, 265, 12);
        painter.drawRect(rect);
        rect.moveTopLeft(QPoint(115, 53));
        painter.drawRect(rect);
        rect.moveTopLeft(QPoint(620, 15));
        painter.drawRect(rect);
        rect.moveTopLeft(QPoint(620, 53));
        painter.drawRect(rect);

        rect.moveTopLeft(QPoint(115, 700));
        painter.drawRect(rect);
        rect.moveTopLeft(QPoint(115, 740));
        painter.drawRect(rect);
        rect.moveTopLeft(QPoint(620, 700));
        painter.drawRect(rect);
        rect.moveTopLeft(QPoint(620, 740));
        painter.drawRect(rect);

        QRect rect1(20, 95, 12, 190);
        painter.drawRect(rect1);
        rect1.moveTopLeft(QPoint(70, 95));
        painter.drawRect(rect1);
        rect1.moveTopLeft(QPoint(925, 95));
        painter.drawRect(rect1);
        rect1.moveTopLeft(QPoint(975, 95));
        painter.drawRect(rect1);
        rect1.moveTopLeft(QPoint(20, 475));
        painter.drawRect(rect1);
        rect1.moveTopLeft(QPoint(70, 475));
        painter.drawRect(rect1);
        rect1.moveTopLeft(QPoint(925, 475));
        painter.drawRect(rect1);
        rect1.moveTopLeft(QPoint(975, 475));
        painter.drawRect(rect1);

        QRect rect2(465, 130, 12, 155);
        painter.drawRect(rect2);
        rect2.moveTopLeft(QPoint(465, 480));
        painter.drawRect(rect2);
        rect2.moveTopLeft(QPoint(520, 130));
        painter.drawRect(rect2);
        rect2.moveTopLeft(QPoint(520, 480));
        painter.drawRect(rect2);

        QRect rect3(165, 360, 215, 12);
        painter.drawRect(rect3);
        rect3.moveTopLeft(QPoint(165, 395));
        painter.drawRect(rect3);
        rect3.moveTopLeft(QPoint(620, 360));
        painter.drawRect(rect3);
        rect3.moveTopLeft(QPoint(620, 395));
        painter.drawRect(rect3);


    }

    // 绘制车辆定位界面
    if(status==100){
        // 绘制背景地图
        painter.drawPixmap(0, 0, width(), height(), mapPixmap);
        if(currentLocation!="-1"){
            QRect rect(122, 40 ,35, 35);
            if(getLocation(currentLocation)!=QPoint(0, 0)){
                rect.moveTopLeft(getLocation(currentLocation));
                painter.drawPixmap(rect, carPixmap);

            }else{
                QRect rect(this->size().width()/2-130, this->size().height()/2-30, 310, 200);
                painter.save();
                painter.setPen(QPen(Qt::red));
                QFont font("Consolas", 30);
                font.setBold(true);
                painter.setFont(font);
                painter.drawText(rect, "此卡不存在！");
                painter.restore();

            }
        }
        currentLocation = serialportassistant->carHeart->cardID;
    }

    // 绘制车辆控制界面
    if(status==111){
        // 绘制背景地图
        painter.drawPixmap(0, 0, width(), height(), mapPixmap);
    }

    // 绘制定位界面和流量界面
    if(status==110){

    }

    // 绘制定位界面和路口界面
    if(status==101){

    }

    // 绘制流量界面和路口界面
    if(status==11){

    }

















}

void CholenMap::mousePressEvent(QMouseEvent *e)
{
    // 测试地图坐标
    qDebug()<<e->pos();
}





// 构建哈希表
void CholenMap::createHashMap()
{
    // 外环
    hashMap.insert("1248BD86", QPoint(100, 3));// 130 H
    hashMap.insert("A49F9610", QPoint(230, 3));
    hashMap.insert("3221C10A", QPoint(360, 3));
    hashMap.insert("2BD900E3", QPoint(600, 3));
    hashMap.insert("A5A5DF90", QPoint(730, 3));
    hashMap.insert("322C481A", QPoint(860, 3));

    hashMap.insert("120CAF86", QPoint(965, 80));// 95 V
    hashMap.insert("A689AB30", QPoint(965, 175));
    hashMap.insert("A5D2A9B0", QPoint(965, 265));
    hashMap.insert("2F21759A", QPoint(965, 475));//
    hashMap.insert("A588A260", QPoint(965, 550));
    hashMap.insert("2C789B89", QPoint(965, 650));

    hashMap.insert("122A0C86", QPoint(860, 730));//
    hashMap.insert("A5A3C720", QPoint(730, 730));
    hashMap.insert("A68986C0", QPoint(600, 730));
    hashMap.insert("1265D076", QPoint(360, 730));
    hashMap.insert("A5AB68A0", QPoint(230, 730));
    hashMap.insert("12BE3D86", QPoint(100, 730));

    hashMap.insert("12DFA786", QPoint(8, 650));//
    hashMap.insert("A4D09BA0", QPoint(8, 550));
    hashMap.insert("2BD7A2D2", QPoint(8, 475));
    hashMap.insert("2DA3D72B", QPoint(8, 265));
    hashMap.insert("A46E87F0", QPoint(8, 175));
    hashMap.insert("A46C6F70", QPoint(8, 80));

    // 内环
    hashMap.insert("A49F4660", QPoint(100, 45));
    hashMap.insert("A4D675D0", QPoint(360, 45));
    hashMap.insert("A46CF260", QPoint(600, 45));
    hashMap.insert("121AE576", QPoint(860, 45));

    hashMap.insert("A49FB710", QPoint(915, 80));
    hashMap.insert("2BD82DE7", QPoint(915, 265));
    hashMap.insert("2BD2F7CA", QPoint(915, 475));
    hashMap.insert("A4A4AC20", QPoint(915, 650));

    hashMap.insert("A6036850", QPoint(860, 690));
    hashMap.insert("12B97286", QPoint(600, 690));
    hashMap.insert("1267E486", QPoint(360, 690));
    hashMap.insert("A49F0A50", QPoint(100, 690));

    hashMap.insert("A83CBBE0", QPoint(60, 650));
    hashMap.insert("12F55986", QPoint(60, 475));
    hashMap.insert("322AAEEA", QPoint(60, 265));
    hashMap.insert("A49F32C0", QPoint(60, 80));

    // 垂直中间左
    hashMap.insert("315F9FFA", QPoint(455, 125));
    hashMap.insert("2BC8A8AA", QPoint(455, 265));
    hashMap.insert("A61123D0", QPoint(455, 470));
    hashMap.insert("A689CA50", QPoint(455, 610));

    // 垂直中间右
    hashMap.insert("3224E1FA", QPoint(510, 125));
    hashMap.insert("322F64AA", QPoint(510, 265));
    hashMap.insert("2CBE4C79", QPoint(510, 470));
    hashMap.insert("034B89D7", QPoint(510, 610));

    // 水平上
    hashMap.insert("129DCE76", QPoint(155, 345));
    hashMap.insert("A5D3FEB0", QPoint(360, 345));
    hashMap.insert("313E2DFA", QPoint(600, 345));
    hashMap.insert("126A3586", QPoint(820, 345));

    // 水平下
    hashMap.insert("A4726290", QPoint(155, 385));
    hashMap.insert("A689F370", QPoint(360, 385));
    hashMap.insert("A466F160", QPoint(600, 385));
    hashMap.insert("12A43296", QPoint(820, 385));


    //test
//    hashMap.insert("A5A2F930", QPoint(100, 3));// 130 H
//    hashMap.insert("A4A56DE0", QPoint(230, 3));
//    hashMap.insert("A6118D60", QPoint(360, 3));
//    hashMap.insert("A4D6FFD0", QPoint(600, 3));
//    hashMap.insert("A4700C20", QPoint(730, 3));
//    hashMap.insert("A603D970", QPoint(860, 3));

}


QPoint CholenMap::getLocation(QString id)
{
//    qDebug()<<this->hashMap[id];
    return this->hashMap[id];
}


