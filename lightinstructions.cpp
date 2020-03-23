#include "lightinstructions.h"
#include <QDebug>

LightInstructions::LightInstructions()
{

}

LightInstructions::LightInstructions(QString roadNum, QString lightTime)
{
    QString front = "FEFE12FFFF42";
    QString rear = "0000000000000000AAFF";
    QString finnal;
    if(lightTime.trimmed().toInt()>=10){
        finnal = front + "3" + roadNum.trimmed() + lightTime.trimmed() + rear;
    }else{
        finnal = front + "3" + roadNum.trimmed() + "0" + lightTime.trimmed() + rear;
    }
    this->instruction = finnal.toLocal8Bit();
    qDebug()<<finnal;
    qDebug()<<this->getInstruction();
}



QByteArray LightInstructions::getInstruction()
{
    return this->instruction;
}

void LightInstructions::setInstruction(QString instruction)
{
    this->instruction = QByteArray::fromHex(instruction.toLocal8Bit());
}
