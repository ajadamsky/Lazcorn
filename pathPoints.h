//
// Created by BearMace on 06/11/2017.
//

#ifndef LAZCORN_PATHPOINTS_H
#define LAZCORN_PATHPOINTS_H


#include <map>

class pathPoints
{
public:
    struct Cordinates
    {
        int x;
        int y;
    };
    std::map<int,Cordinates>targetPoints;
    void initTargetPoints();
protected:

};


#endif //LAZCORN_PATHPOINTS_H
