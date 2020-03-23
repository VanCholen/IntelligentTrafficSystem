#ifndef HEARTBEATBAG_H
#define HEARTBEATBAG_H

#include <QString>

class HeartBeatBag
{

public:
    QString ID;
    QString data;




public:
    HeartBeatBag();
    void setID(QString);
    void setData(QString);
    QString getID();
    QString getData();
};

#endif // HEARTBEATBAG_H
