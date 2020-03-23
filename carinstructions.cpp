#include "carinstructions.h"



CarInstructions::CarInstructions()
{

}

CarInstructions::CarInstructions(QString instruction)
{
    this->instruction = QByteArray::fromHex(instruction.toLocal8Bit());
}

QByteArray CarInstructions::getInstruction()
{
    return this->instruction;
}

void CarInstructions::setInstruction(QString instruction)
{
    this->instruction = QByteArray::fromHex(instruction.toLocal8Bit());
}
