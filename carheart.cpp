#include "carheart.h"

CarHeart::CarHeart()
{
    carLocation=new headPoint[9];//构建节点地图
    carPath= new path[12];


    carLocation[0].firstin=carPath+0;
    carLocation[0].X=0;
    carLocation[0].Y=1;
    carPath[0].ivex=0;
    carPath[0].ilink=carPath+1;
    carPath[1].ivex=0;
    carPath[1].ilink=carPath+8;
    carPath[8].ivex=0;
    carPath[8].ilink=NULL;

    carLocation[1].firstin=carPath;
    carLocation[1].X=-1;
    carLocation[1].Y=1;
    carPath[0].jvex=1;
    carPath[0].jlink=carPath+10;
    carPath[10].ivex=1;
    carPath[10].ilink=NULL;

    carLocation[2].firstin=carPath+10;
    carLocation[2].X=-1;
    carLocation[2].Y=0;
    carPath[10].jvex=2;
    carPath[10].jlink=carPath+9;
    carPath[9].ivex=2;
    carPath[9].ilink=carPath+11;
    carPath[11].ivex=2;
    carPath[11].ilink=NULL;

    carLocation[3].firstin=carPath+11;
    carLocation[3].X=-1;
    carLocation[3].Y=-1;
    carPath[11].jvex=3;
    carPath[11].jlink=carPath+5;
    carPath[5].ivex=3;
    carPath[5].ilink=NULL;

    carLocation[4].firstin=carPath+6;
    carLocation[4].X=0;
    carLocation[4].Y=-1;
    carPath[6].ivex=4;
    carPath[6].ilink=carPath+4;
    carPath[4].ivex=4;
    carPath[4].ilink=carPath+5;
    carPath[5].jvex=4;
    carPath[5].jlink=NULL;

    carLocation[5].firstin=carPath+6;
    carLocation[5].X=0;
    carLocation[5].Y=0;
    carPath[6].jvex=5;
    carPath[6].jlink=carPath+9;
    carPath[9].jvex=5;
    carPath[9].jlink=carPath+8;
    carPath[8].jvex=5;
    carPath[8].jlink=carPath+7;
    carPath[7].jvex=5;
    carPath[7].jlink=NULL;

    carLocation[6].firstin=carPath+2;
    carLocation[6].X=1;
    carLocation[6].Y=1;
    carPath[2].ivex=6;
    carPath[2].ilink=carPath+1;
    carPath[1].jvex=6;
    carPath[1].jlink=NULL;

    carLocation[7].firstin=carPath+2;
    carLocation[7].X=1;
    carLocation[7].Y=0;
    carPath[2].jvex=7;
    carPath[2].jlink=carPath+3;
    carPath[3].ivex=7;
    carPath[3].ilink=carPath+7;
    carPath[7].ivex=7;
    carPath[7].ilink=NULL;

    carLocation[8].firstin=carPath+3;
    carLocation[8].X=1;
    carLocation[8].Y=-1;
    carPath[3].jvex=8;
    carPath[3].jlink=carPath+4;
    carPath[4].jvex=8;
    carPath[4].jlink=NULL;
}

void CarHeart::setID(QString id)
{
    this->ID = id;
}

void CarHeart::setCardID(QString cardID)
{
    this->cardID = cardID;
}

QString CarHeart::getID()
{
    return this->ID;
}

QString CarHeart::getCardID()
{
    return this->cardID;
}

int CarHeart::routePlanning(int beginPoint,int endPoint,int* record,int recordNum,int* passPoint,int passPointNum)
{
    path* pathPointer;
    //headPoint* headPointer;
    int *newRecord=new int[8];
    for(int i=0;i<8;i++){//更新标记路径初始化
        newRecord[i]=-1;
    }
    int w=0,minw=10000;
    if(beginPoint==endPoint){//最后一个节点
        record[recordNum]=beginPoint;
        for(int i=recordNum+1;i<8;i++){//最后一个节点之后的节点回归初始化
            record[i]=-1;
        }
        return 0;
    }

    //headPointer=carLocation+beginPoint;

    //循环递归————遍历经过节点的路径
    for(pathPointer=carLocation[beginPoint].firstin;pathPointer!=NULL;){


        if(pathPointer->ivex==beginPoint){//屏蔽已经路过的路径
            int j=0;
            for(;j<passPointNum;j++){
                if(pathPointer->jvex==passPoint[j]){
                    break;
                }
            }
            if(j<passPointNum)
                goto cont;


            int* passPointNew=new int[passPointNum+1];//更新路过的路径
            for(int i=0;i<passPointNum;i++)
            {
                passPointNew[i]=passPoint[i];
            }
            passPointNew[passPointNum]=beginPoint;

            //递归遍历下一个节点的路径
            w=pathPointer->pathPower + routePlanning(pathPointer->jvex,endPoint,newRecord,recordNum+1,passPointNew,passPointNum+1);

            //找出最小代价的子路径及其值
            if(w<minw)
            {
                minw=w;
                for(int i=recordNum+1;i<8;i++){
                    record[i]=newRecord[i];
                }
            }

            //清除内存
            delete(passPointNew);

        }else if(pathPointer->jvex==beginPoint){
            int j=0;
            for(;j<passPointNum;j++){//屏蔽已路过的路径
                if(pathPointer->ivex==passPoint[j]){
                    break;
                }
            }
            if(j<passPointNum)
                goto cont;


            int* passPointNew=new int[passPointNum+1];//更新已路过的路径
            for(int i=0;i<passPointNum;i++)
            {
                passPointNew[i]=passPoint[i];
            }
            passPointNew[passPointNum]=beginPoint;
            //递归调用————遍历下一个节点的路径
            w=pathPointer->pathPower + routePlanning(pathPointer->ivex,endPoint,newRecord,recordNum+1,passPointNew,passPointNum+1);
            //找出最优子路径
            if(w<minw)
            {
                minw=w;
                for(int i=recordNum+1;i<8;i++){
                    record[i]=newRecord[i];
                }
            }
            delete(passPointNew);

        }else{//路径错误
            printf("DATA ERROR!!!");
            exit(1);
        }
        //更新节点指向下一条路径
        cont:if(pathPointer->ivex==beginPoint){
            pathPointer=pathPointer->ilink;
        }else if(pathPointer->jvex==beginPoint){
            pathPointer=pathPointer->jlink;
        }



    }
    //更新路径标记
    record[recordNum]=beginPoint;

    //清除内存
    delete(newRecord);
    delete(pathPointer);
    //delete(headPointer);
    //返回最短权值
    return minw;

}
/*
 * 函数名：orderTOTurn
 *函数功能：节点转换成方向
 * record:节点标记
 * turn:命令标记————1：前、2：后、3：左、4：右
 * directionX:标记小车方向X方向
 * directionY：标记小车Y方向
 *
*/

void CarHeart::orderToTurn(int* record,int* turn,int directionX,int directionY)
{
    int locationX1,locationX2;
    int locationY1,locationY2;
    /*if(directionX==directionY)
    {
        cout<<"LOCATION ERROR!!!";
    }*/
    for(int i=0;record[i+1]!=-1&&i<7;i++){
        locationX1=carLocation[record[i]].X;
        locationY1=carLocation[record[i]].Y;
        locationX2=carLocation[record[i+1]].X;
        locationY2=carLocation[record[i+1]].Y;
        if(locationX2-locationX1-directionX==0&&locationY2-locationY1-directionY==0){
            turn[i]=1;
        }else if(locationX2-locationX1+directionX==0&&locationY2-locationY1+directionY==0){
            turn[i]=2;
            directionX=-directionX;
            directionY=-directionY;
        }else{
            if(directionX!=0){
                if(locationX2-locationX1-directionY==0&&locationY2-locationY1-directionX==0){
                    turn[i]=3;
                    int k=directionY;;
                    directionY=directionX;
                    directionX=k;
                }else{
                    turn[i]=4;
                    int k=directionY;;
                    directionY=-directionX;
                    directionX=k;
                }
            }else{
                if(locationX2-locationX1+directionY==0&&locationY2-locationY1+directionX==0){
                    turn[i]=3;
                    int k=directionY;;
                    directionY=directionX;
                    directionX=-k;
                }else{
                    turn[i]=4;
                    int k=directionY;
                    directionY=directionX;
                    directionX=k;
                }
            }
        }
    }
}

void CarHeart::carPathPlanning(int endPoint,int*record,int* turn)
{
    for(int i=0;i<8;i++){
        record[i]=-1;
    }
    for(int i=0;i<7;i++){
        turn[i]=-1;
    }
    int w=routePlanning(carNextCrossNum,endPoint,record);
    orderToTurn(record,turn,carDirectionX,carDirectionY);
}

void CarHeart::setPathPower(int pathNum,int power)
{
    carPath[pathNum].pathPower=power;
}

int CarHeart::getPathNum()
{
    int pathNum;
    if(getCardID()=="1248BD86"&&getCardID()=="A49F9610"&&getCardID()=="3221C10A"){
        pathNum=0;
    }else if(getCardID()=="2BD900E3"&&getCardID()=="A5A5DF90"&&getCardID()=="322C481A"){
        pathNum=1;
    }else if(getCardID()=="120CAF86"&&getCardID()=="A689AB30"&&getCardID()=="A5D2A9B0"){
        pathNum=2;
    }else if(getCardID()=="2F21759A"&&getCardID()=="A588A260"&&getCardID()=="2C789B89"){
        pathNum=3;
    }else if(getCardID()=="122A0C86"&&getCardID()=="A5A3C720"&&getCardID()=="A68986C0"){
        pathNum=4;
    }else if(getCardID()=="1265D076"&&getCardID()=="A5AB68A0"&&getCardID()=="12BE3D86"){
        pathNum=5;
    }else if(getCardID()=="12DFA786"&&getCardID()=="A4D09BA0"&&getCardID()=="2BD7A2D2"){
        pathNum=11;
    }else if(getCardID()=="2DA3D72B"&&getCardID()=="A46E87F0"&&getCardID()=="A46C6F70"){
        pathNum=10;
    }else if(getCardID()=="A49F4660"&&getCardID()=="A4D675D0"){
        pathNum=0;
    }else if(getCardID()=="A46CF260"&&getCardID()=="121AE576"){
        pathNum=1;
    }else if(getCardID()=="A49FB710"&&getCardID()=="2BD82DE7"){
        pathNum=2;
    }else if(getCardID()=="2BD2F7CA"&&getCardID()=="A4A4AC20"){
        pathNum=3;
    }else if(getCardID()=="A6036850"&&getCardID()=="12B97286"){
        pathNum=4;
    }else if(getCardID()=="1267E486"&&getCardID()=="A49F0A50"){
        pathNum=5;
    }else if(getCardID()=="A83CBBE0"&&getCardID()=="12F55986"){
        pathNum=11;
    }else if(getCardID()=="322AAEEA"&&getCardID()=="A49F32C0"){
        pathNum=10;
    }else if(getCardID()=="315F9FFA"&&getCardID()=="2BC8A8AA"){
        pathNum=8;;
    }else if(getCardID()=="A61123D0"&&getCardID()=="A689CA50"){
        pathNum=6;
    }else if(getCardID()=="3224E1FA"&&getCardID()=="322F64AA"){
        pathNum=8;
    }else if(getCardID()=="2CBE4C79"&&getCardID()=="034B89D7"){
        pathNum=6;
    }else if(getCardID()=="129DCE76"&&getCardID()=="A5D3FEB0"){
        pathNum=9;
    }else if(getCardID()=="313E2DFA"&&getCardID()=="126A3586"){
        pathNum=7;
    }else if(getCardID()=="A4726290"&&getCardID()=="A689F370"){
        pathNum=9;
    }else if(getCardID()=="A466F160"&&getCardID()=="12A43296"){
        pathNum=7;
    }
    return pathNum;

}

void CarHeart::getNextCross()
{
    if(getCardID()=="1248BD86"&&getCardID()=="A49F9610"&&getCardID()=="3221C10A"){
        carDirectionX=-1;
        carDirectionY=0;
        carNextCrossPoint=QPoint(-1,1);
        carNextCrossNum=1;
    }else if(getCardID()=="2BD900E3"&&getCardID()=="A5A5DF90"&&getCardID()=="322C481A"){
        carDirectionX=-1;
        carDirectionY=0;
        carNextCrossPoint=QPoint(0,1);
        carNextCrossNum=0;
    }else if(getCardID()=="120CAF86"&&getCardID()=="A689AB30"&&getCardID()=="A5D2A9B0"){
        carDirectionX=0;
        carDirectionY=1;
        carNextCrossPoint=QPoint(1,1);
        carNextCrossNum=6;
    }else if(getCardID()=="2F21759A"&&getCardID()=="A588A260"&&getCardID()=="2C789B89"){
        carDirectionX=0;
        carDirectionY=1;
        carNextCrossPoint=QPoint(1,0);
        carNextCrossNum=7;
    }else if(getCardID()=="122A0C86"&&getCardID()=="A5A3C720"&&getCardID()=="A68986C0"){
        carDirectionX=1;
        carDirectionY=0;
        carNextCrossPoint=QPoint(1,-1);
        carNextCrossNum=8;
    }else if(getCardID()=="1265D076"&&getCardID()=="A5AB68A0"&&getCardID()=="12BE3D86"){
        carDirectionX=1;
        carDirectionY=0;
        carNextCrossPoint=QPoint(0,-1);
        carNextCrossNum=4;
    }else if(getCardID()=="12DFA786"&&getCardID()=="A4D09BA0"&&getCardID()=="2BD7A2D2"){
        carDirectionX=0;
        carDirectionY=-1;
        carNextCrossPoint=QPoint(-1,-1);
        carNextCrossNum=3;
    }else if(getCardID()=="2DA3D72B"&&getCardID()=="A46E87F0"&&getCardID()=="A46C6F70"){
        carDirectionX=0;
        carDirectionY=-1;
        carNextCrossPoint=QPoint(-1,0);
        carNextCrossNum=2;
    }else if(getCardID()=="A49F4660"&&getCardID()=="A4D675D0"){
        carDirectionX=1;
        carDirectionY=0;
        carNextCrossPoint=QPoint(0,1);
        carNextCrossNum=0;
    }else if(getCardID()=="A46CF260"&&getCardID()=="121AE576"){
        carDirectionX=1;
        carDirectionY=0;
        carNextCrossPoint=QPoint(1,1);
        carNextCrossNum=6;
    }else if(getCardID()=="A49FB710"&&getCardID()=="2BD82DE7"){
        carDirectionX=0;
        carDirectionY=-1;
        carNextCrossPoint=QPoint(1,0);
        carNextCrossNum=7;
    }else if(getCardID()=="2BD2F7CA"&&getCardID()=="A4A4AC20"){
        carDirectionX=0;
        carDirectionY=-1;
        carNextCrossPoint=QPoint(1,-1);
        carNextCrossNum=8;
    }else if(getCardID()=="A6036850"&&getCardID()=="12B97286"){
        carDirectionX=-1;
        carDirectionY=0;
        carNextCrossPoint=QPoint(0,-1);
        carNextCrossNum=4;
    }else if(getCardID()=="1267E486"&&getCardID()=="A49F0A50"){
        carDirectionX=-1;
        carDirectionY=0;
        carNextCrossPoint=QPoint(-1,-1);
        carNextCrossNum=3;
    }else if(getCardID()=="A83CBBE0"&&getCardID()=="12F55986"){
        carDirectionX=0;
        carDirectionY=1;
        carNextCrossPoint=QPoint(-1,0);
        carNextCrossNum=2;
    }else if(getCardID()=="322AAEEA"&&getCardID()=="A49F32C0"){
        carDirectionX=0;
        carDirectionY=1;
        carNextCrossPoint=QPoint(-1,1);
        carNextCrossNum=1;
    }else if(getCardID()=="315F9FFA"&&getCardID()=="2BC8A8AA"){
        carDirectionX=0;
        carDirectionY=-1;
        carNextCrossPoint=QPoint(0,0);
        carNextCrossNum=5;
    }else if(getCardID()=="A61123D0"&&getCardID()=="A689CA50"){
        carDirectionX=0;
        carDirectionY=-1;
        carNextCrossPoint=QPoint(0,-1);
        carNextCrossNum=6;
    }else if(getCardID()=="3224E1FA"&&getCardID()=="322F64AA"){
        carDirectionX=0;
        carDirectionY=1;
        carNextCrossPoint=QPoint(0,1);
        carNextCrossNum=0;
    }else if(getCardID()=="2CBE4C79"&&getCardID()=="034B89D7"){
        carDirectionX=0;
        carDirectionY=1;
        carNextCrossPoint=QPoint(0,0);
        carNextCrossNum=5;
    }else if(getCardID()=="129DCE76"&&getCardID()=="A5D3FEB0"){
        carDirectionX=-1;
        carDirectionY=0;
        carNextCrossPoint=QPoint(-1,0);
        carNextCrossNum=2;
    }else if(getCardID()=="313E2DFA"&&getCardID()=="126A3586"){
        carDirectionX=-1;
        carDirectionY=0;
        carNextCrossPoint=QPoint(0,0);
        carNextCrossNum=5;
    }else if(getCardID()=="A4726290"&&getCardID()=="A689F370"){
        carDirectionX=1;
        carDirectionY=0;
        carNextCrossPoint=QPoint(0,0);
        carNextCrossNum=5;
    }else if(getCardID()=="A466F160"&&getCardID()=="12A43296"){
        carDirectionX=1;
        carDirectionY=0;
        carNextCrossPoint=QPoint(1,0);
        carNextCrossNum=7;
    }


}

void CarHeart::pathShield(int pathNum)
{
    setPathPower(pathNum,10000);
}

void CarHeart::pathPlanningPackage(int endPoint,int* turn)
{
    int* record=new int[8];
    getNextCross();
    carPathPlanning(endPoint,record,turn);
}

CarHeart::~CarHeart(){
    delete(carLocation);
    delete(carPath);
}

