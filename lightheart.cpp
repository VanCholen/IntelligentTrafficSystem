#include "lightheart.h"

LightHeart::LightHeart()
{

}

void LightHeart::setID(QString id)
{
    this->ID = id;
}

void LightHeart::setStatus(QString status)
{
    this->status = status;
}

QString LightHeart::getID()
{
    return this->ID;
}

QString LightHeart::getStatus()
{
    return this->status;
}
