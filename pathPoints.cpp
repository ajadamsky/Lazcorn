//
// Created by BearMace on 06/11/2017.
//

#include "pathPoints.h"

void pathPoints::initTargetPoints()
{
    //this creates the path-Points {x,y}:
    Cordinates tmp1={-100,300};
    Cordinates tmp2={1300,300};
    Cordinates tmp3={-100,600};
    Cordinates tmp4={1300,600};
    //to be continued.....
    Cordinates tmp5={200,400};
    Cordinates tmp6={400,200};
    Cordinates tmp7={800,100};
    Cordinates tmp8={100,800};
    Cordinates tmp9={500,500};
    Cordinates tmp10={900,100};
    //now we create the map:
    targetPoints[0]=tmp1;
    targetPoints[1]=tmp2;
    targetPoints[2]=tmp3;
    targetPoints[3]=tmp4;
    targetPoints[4]=tmp5;
    targetPoints[5]=tmp6;
    targetPoints[6]=tmp7;
    targetPoints[7]=tmp8;
    targetPoints[8]=tmp9;
    targetPoints[9]=tmp10;
}
