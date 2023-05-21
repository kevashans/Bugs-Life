#include "Bug.h"

//
// Created by kevas on 24/03/2023.
//


Bug::Bug(int id, int x, int y, int direction, int size)
{
    this->id = id;
    std::pair<int, int> PAIR1;
    PAIR1.first =  x;
    PAIR1.second = y;
    this->position = PAIR1;
    this->direction =direction;
    this ->size = size;
    this->alive = true;
    this->clicked=false;

}

int Bug::getId() const
{
    return this->id;
}

const std::pair<int, int> Bug::getPosition() const
{
    return this->position;
}

int Bug::getDirection() const
{
    return this->direction;
}

int Bug::getSize() const
{
    return this->size;
};

bool Bug::isAlive() const
{
    return this->alive;
};

const std::list<std::pair<int, int>> Bug::getPath() const
{
    return this->path;
};

void Bug::setId(int id)
{
    this->id = id;
};


void Bug::setPosition(const std::pair<int, int> &position)
{
    this->position = position;
}

void Bug::setDirection(int direction)
{
    this->direction = direction;
};

void Bug::setSize(int size)
{
    this->size = size;
};

void Bug::setAlive(bool alive)
{
    this->alive = alive;
};

void Bug::addPath(const std::pair<int, int> &x)
{
    this->path.push_back(x);
};

bool Bug::isWayBlocked()
{
    if (this->position.first == 9 && this->direction == directions::East)
    {
        return true;
    } else if (this->position.second == 0 && this->direction == directions::North)
    {
        return true;
    } else if (this->position.first == 0 && this->direction == directions::West)
    {
        return true;
    } else if (this->position.second == 9 && this->direction == directions::South)
    {
        return true;
    } else
    {
        return false;
    }

}

void Bug::setEatenBy(const int &eatenBy)
{
    this->eatenBy = eatenBy;
}

int Bug::getEatenBy() const
{
    return eatenBy;
}

bool Bug::isClicked() const {
    return clicked;
}

void Bug::setClicked(bool clicked) {
    Bug::clicked = clicked;
};

