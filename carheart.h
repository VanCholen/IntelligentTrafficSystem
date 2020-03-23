#ifndef CARHEART_H
#define CARHEART_H

#include <QString>
#include <QPoint>
struct path{//表节点
    int pathPower;//路径权值默认为1
    int mark;
    int ivex;
    path* ilink;
    int jvex;
    path* jlink;
    path(){
        pathPower=1;
        mark=0;
        ivex=-1;
        ilink=this;
        jvex=-1;
        jlink=this;
    }
};
struct headPoint{//点节点
    int headPointID;
    int X;
    int Y;
    //QPoint point;
    path* firstin;
};

class CarHeart
{

public:
    CarHeart();
    void setID(QString id);
    void setCardID(QString cardID);
    QString getID();
    QString getCardID();
    void setPathPower(int pathNum,int power);
    int getPathNum();
    void pathShield(int pathNum);
    void pathPlanningPackage(int endPoint,int* turn);


    void getNextCross();
    void getDirection();
    void setDirection();
    void getCarLocation();
    void setCarLocation();
    void carPathPlanning(int endPoint,int*record,int* turn);//record:大小为8，路径记录，turn:大小为7，下一个路口方向记录
    ~CarHeart();

private:

    int routePlanning(int beginPoint,int endPoint,int* record,int recordNum=0,int* passPoint=NULL,int passPointNum=0);
    void orderToTurn(int* record,int* turn,int directionX,int directionY);
public:
    QString    ID;
    QString    cardID;
private:
    QPoint     carNextCrossPoint;
    int        carNextCrossNum;
    int        carDirectionX;
    int        carDirectionY;
    headPoint* carLocation;
    path*      carPath;
    int*       turn;
    //static QPoint[52];
    //enum directionX {};//每一张卡有一个方向



};

#endif // CARHEART_H
