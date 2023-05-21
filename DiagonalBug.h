//
// Created by kevas on 12/04/2023.
//

#ifndef BUGS_LIFE_DIAGONALBUG_H
#define BUGS_LIFE_DIAGONALBUG_H

#include "Bug.h"
enum diagonalDirections{NorthEast=1,SouthEast=2,SouthWest=3,NorthWest=4};
class DiagonalBug : public Bug{
public:
    DiagonalBug(int id, int x, int y, int direction, int size);
    DiagonalBug();

    virtual void move();
    virtual void print()const;
    virtual std::string getType()const;
    bool diagonallyBlocked()const;

};
#endif //BUGS_LIFE_DIAGONALBUG_H
