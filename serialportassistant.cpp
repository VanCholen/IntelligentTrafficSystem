#include "serialportassistant.h"
#include "ui_serialportassistant.h"


#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>

SerialPortAssistant::SerialPortAssistant(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialPortAssistant)
{
    ui->setupUi(this);
    this->refreshSlot();
    this->setFixedSize(this->size().width(), this->size().height());

    carHeart = new CarHeart;
    lightHeart = new LightHeart;
//    bufferCardID = "-1";
    carHeart->ID = "1";
    carHeart->cardID = "-1";



    connect(ui->refreshBtn, SIGNAL(clicked()), this, SLOT(refreshSlot()));
    connect(ui->connectBtn, SIGNAL(clicked()), this, SLOT(connectSlot()));
    connect(ui->disconnectBtn, SIGNAL(clicked()), this, SLOT(disconnectSlot()));
    connect(ui->clearBtn, SIGNAL(clicked()), this, SLOT(clearSlot()));

    connect(&readTimer, SIGNAL(timeout()), this, SLOT(readSlot()));
    connect(ui->sendBtn, SIGNAL(clicked()), this, SLOT(writeSlot()));
}

SerialPortAssistant::~SerialPortAssistant()
{
    delete ui;
}

void SerialPortAssistant::configPort()
{
    QSerialPort::BaudRate baud = (QSerialPort::BaudRate)ui->baudCombox->currentText().toInt();
    QSerialPort::DataBits dataBits = (QSerialPort::DataBits)ui->dataCombox->currentText().toInt();
    QSerialPort::Parity parity;
    QSerialPort::StopBits stopBits;

    switch (ui->parityCombox->currentIndex()) {
    case 0:
        parity = QSerialPort::NoParity;
        break;
    case 1:
        parity = QSerialPort::EvenParity;
        break;
    case 2:
        parity = QSerialPort::OddParity;
        break;
    case 3:
        parity = QSerialPort::SpaceParity;
        break;
    case 4:
        parity = QSerialPort::MarkParity;
        break;
//    default:
//        break;
    }

    switch (ui->stopCombox->currentIndex()) {
    case 0:
        stopBits = QSerialPort::OneStop;
        break;
    case 1:
        stopBits = QSerialPort::OneAndHalfStop;
        break;
    case 2:
        stopBits = QSerialPort::TwoStop;
        break;
//    default:
//        break;
    }

    this->port.setBaudRate(baud);
    this->port.setDataBits(dataBits);
    this->port.setParity(parity);
    this->port.setStopBits(stopBits);
}



void SerialPortAssistant::refreshSlot()
{
    ui->portCombox->clear();
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts()){
        ui->portCombox->addItem(info.portName());
    }
}

void SerialPortAssistant::connectSlot()
{
    QString name = ui->portCombox->currentText();
    if(!name.isEmpty()){
        this->port.setPortName(ui->portCombox->currentText());
        if(this->port.open(QIODevice::ReadWrite)){
            // 配置端口
            this->configPort();
            // 启动读取
            this->readTimer.start(100);

        } else {   // 打开失败
            QMessageBox::warning(this, tr("打开串口"), tr("%1").arg(port.errorString()), QMessageBox::Ok);
        }
    }else{   // 没有设备
        QMessageBox::warning(this, tr("打开串口"), tr("没有可用的端口"), QMessageBox::Ok);
    }
}

void SerialPortAssistant::disconnectSlot()
{
    this->readTimer.stop();
    this->port.close();
}

void SerialPortAssistant::readSlot()
{
    QByteArray buf;
    // 端口打开时读取数据
    if(this->port.isOpen()){
        buf = this->port.readAll();
        if(!buf.isEmpty()){
            QString lightOrCar = buf.mid(5, 1);
            if(ui->hexDisplayCheckBox->isChecked()){
                /* 协议解析
                 *
                 *
                 *
                */
                if(lightOrCar=="B"){ // 灯
                    QByteArray lightID = buf.mid(6,1);
                    QByteArray status = buf.mid(8, 2);
                    ui->textEdit->append("灯编号:"+lightID.toHex());
                    if(status=="0"){
                         ui->textEdit->append("红灯:"+status.toHex());
                    }else if(status=="1"){
                        ui->textEdit->append("绿灯:"+status.toHex());
                    }

                    lightHeart->ID = buf.mid(6, 1);
                    lightHeart->status = buf.mid(8, 2);
                }else if(lightOrCar=="A"){ //车心跳包
                    ui->textEdit->append("车编号:"+buf.mid(6, 1).toHex());
                    ui->textEdit->append("当前卡号:"+buf.mid(8, 8).toHex());
                    carHeart->ID = buf.mid(6, 1);
                    carHeart->cardID = buf.mid(8, 8);
                }

            }else{
                /* 协议解析
                 *
                 *
                 *
                */
                if(lightOrCar=="B"){ // 灯
                    ui->textEdit->append("灯编号:"+buf.mid(6, 1));
                    QString status = buf.mid(8, 2);
                    if(status=="0"){
                         ui->textEdit->append("红灯:"+status);
                    }else if(status=="1"){
                        ui->textEdit->append("绿灯:"+status);
                    }

                    lightHeart->ID = buf.mid(6, 1);
                    lightHeart->status = buf.mid(8, 2);
                }else if(lightOrCar=="A"){ //车心跳包
                    ui->textEdit->append("车编号:"+buf.mid(6, 1));
                    ui->textEdit->append("当前卡号:"+buf.mid(8, 8));
                    carHeart->ID = buf.mid(6, 1);
                    carHeart->cardID = buf.mid(8, 8);
                }




            }



        }

    }





}

void SerialPortAssistant::writeSlot()
{
    QString text = ui->lineEdit->text();
    if(!text.isEmpty()){
        if(ui->hexSendCheckBox->isChecked()){
            port.write(QByteArray::fromHex(text.toLocal8Bit()));
        }else{
            port.write(text.toLocal8Bit());

        }
    }
}

void SerialPortAssistant::clearSlot()
{
    ui->textEdit->clear();
}
