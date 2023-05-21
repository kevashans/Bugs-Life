//
// Created by kevas on 27/03/2023.
//

#ifndef BUGS_LIFE_CRAWLER_H
#define BUGS_LIFE_CRAWLER_H

#include "Bug.h"

class Crawler : public Bug{
private:

public:

    Crawler(int id, int x, int y, int direction, int size);

    virtual void move();
    virtual void print()const;
    virtual std::string getType()const;
};
#endif //BUGS_LIFE_CRAWLER_H
