#ifndef LIGHTINSTRUCTIONS_H
#define LIGHTINSTRUCTIONS_H

#include <QString>
#include <QByteArray>

class LightInstructions
{
private:
    QByteArray instruction;
public:
    LightInstructions();
    LightInstructions(QString, QString);
    QByteArray getInstruction(void);
    void setInstruction(QString);
};

#endif // LIGHTINSTRUCTIONS_H
