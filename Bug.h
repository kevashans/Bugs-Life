//
// Created by kevas on 24/03/2023.
//

#ifndef BUGS_LIFE_BUG_H
#define BUGS_LIFE_BUG_H

#include <utility>
#include <list>
#include <iostream>
enum directions{North=1,East=2,South=3,West=4};
class Bug{

protected:
    int id;
    std::string type;
    std::pair<int,int> position;
    int direction;
    int size;
    bool alive;
    int eatenBy;
    std::list<std::pair<int,int>> path;
    bool clicked;

public:
    Bug(int id, int x, int y, int direction, int size);

    Bug(int id, const std::pair<int, int> &position, int direction, int size);

    virtual void move()=0;
    virtual void print() const =0;
    virtual std::string getType() const=0;
    virtual bool isWayBlocked();

    int getId() const;

    const std::pair<int, int> getPosition() const;


    int getDirection() const;

    int getSize() const;

    bool isAlive() const;

    const std::list<std::pair<int, int>> getPath() const;

    void setId(int id);

    void setPosition(const std::pair<int, int> &position);

    void setDirection(int direction);

    void setSize(int size);

    void setAlive(bool alive);

    void setEatenBy(const int &eatenBy);

    int getEatenBy() const;

    void addPath(const std::pair<int, int> &path);

    bool isClicked() const;

    void setClicked(bool clicked);


};

#endif //BUGS_LIFE_BUG_H
