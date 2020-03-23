#ifndef LIGHTHEART_H
#define LIGHTHEART_H

#include <QString>


class LightHeart
{
public:
    LightHeart();
    void setID(QString id);
    void setStatus(QString status);
    QString getID();
    QString getStatus();

public:
    QString ID;
    QString status;
};

#endif // LIGHTHEART_H
