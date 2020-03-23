#ifndef SERIALPORTASSISTANT_H
#define SERIALPORTASSISTANT_H

#include <QWidget>

#include <QtSerialPort/QSerialPort>
#include <QByteArray>
#include <QTimer>

#include "carheart.h"
#include "lightheart.h"


namespace Ui {
class SerialPortAssistant;
}

class SerialPortAssistant : public QWidget
{
    Q_OBJECT

public:
    explicit SerialPortAssistant(QWidget *parent = 0);
    ~SerialPortAssistant();

private:
    Ui::SerialPortAssistant *ui;
    QTimer readTimer;

public:
     QSerialPort port;
private:
    // 配置端口
    void configPort(void);


public:
    LightHeart* lightHeart;
    CarHeart*   carHeart;


public slots:
    // 刷新端口
    void refreshSlot(void);

    //打开串口
    void connectSlot(void);

    //关闭串口
    void disconnectSlot(void);

    // 读数据
    void readSlot(void);

    // 写数据
    void writeSlot(void);

    // 清除
    void clearSlot(void);
};

#endif // SERIALPORTASSISTANT_H
