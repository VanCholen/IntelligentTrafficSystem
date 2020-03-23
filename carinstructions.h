#ifndef CARINSTRUCTIONS_H
#define CARINSTRUCTIONS_H

#include <QString>
#include <QByteArray>
//#include <carheart.h>

class CarInstructions
{
private:
    QByteArray instruction;
public:
    CarInstructions();
    CarInstructions(QString);
    QByteArray getInstruction(void);
    void setInstruction(QString);
};

#endif // CARINSTRUCTIONS_H
