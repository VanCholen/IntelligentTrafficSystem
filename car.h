#ifndef CAR_H
#define CAR_H

#include <QPixmap>
#include <QHash>
class Car
{
public:
    Car();
    Car(QPixmap);


private:
    QPoint getLocation(QString);
    void setHashMap(QHash);
};

#endif // CAR_H
