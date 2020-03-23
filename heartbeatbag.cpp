#include "heartbeatbag.h"

HeartBeatBag::HeartBeatBag()
{

}

void HeartBeatBag::setID(QString ID)
{
    this->ID = ID
}

void HeartBeatBag::setData(QString data)
{
    this->data = data;
}

QString HeartBeatBag::getID()
{
    return this->ID;
}

QString HeartBeatBag::getData()
{
    return this->data;
}
