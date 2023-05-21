//
// Created by kevas on 24/03/2023.
//

#ifndef BUGS_LIFE_HOPPER_H
#define BUGS_LIFE_HOPPER_H

#include "Bug.h"

class Hopper : public Bug{
private:
    int hopLength ;
public:
    Hopper(int id, int x, int y, int direction, int size, int hoplength);
    Hopper();

    virtual void move();
    virtual void print()const;
    virtual std::string getType()const;

};
#endif //BUGS_LIFE_HOPPER_H
