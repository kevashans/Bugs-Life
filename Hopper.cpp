#include "Hopper.h"
#include <iostream>


//
// Created by kevas on 24/03/2023.
//
using namespace std;
Hopper::Hopper(int id, int x, int y, int direction, int size, int hoplength): Bug(id, x, y, direction, size){

    this->hopLength = hoplength;
}

void Hopper::move()
{
    int direction = this->direction;
    srand(time(nullptr));
//    int new_direction = direction;
    std::pair<int, int> position = this->position;

    while (isWayBlocked())
    {
        direction = rand() % 4 + 1;
        this->setDirection(direction);
    }

    if (direction == directions::South)
    {
        //// if after hopping does not exceed northern boundary
        if(position.second + this->hopLength <= 9)
        {
        position.second += this->hopLength;
        }
        else ////if it exceeds the boundary put it at the edge
        {
            position.second = 9;
//            this->setDirection(new_direction);
        }
    }else if(direction ==directions::East)
    {
        //// if after hopping does not exceed eastern boundary
        if(position.first + this->hopLength <= 9)
        {
        position.first += this->hopLength;
        }else////if it exceeds the boundary put it at the edge
        {
            position.first = 9;
//            this->setDirection(new_direction);
        }
    }else if(direction == directions::North)
    {
        //// if after hopping does not exceed Northern boundary
        if(position.second - this->hopLength >= 0)
        {
        position.second -= this->hopLength;
        }else////if it exceeds the boundary put it at the edge
        {
            position.second = 0;
//            this->setDirection(new_direction);
        }
    }else if(direction == directions::West)
    {
        //// if after hopping does not exceed western boundary
        if(position.first- this->hopLength >= 0)
        {
        position.first -= this->hopLength;
        }else////if it exceeds the boundary put it at the edge
        {
            position.first = 0;
//            this->setDirection(new_direction);
        }
    }

    if(this->alive)
    {
    this->setPosition(position);
    this->addPath(position);
    }
}

void Hopper::print()const
{

    string direction;
    std::pair<int, int> PAIR1 = this->position;
//        cout << PAIR1.first;
    if (this->direction==directions::North)
    {
        direction = "North";
    }else if(this->direction==directions::East)
    {
        direction ="East";
    }else if(this->direction==directions::South)
    {
        direction ="South";
    }else if(this->direction==directions::West)
    {
        direction ="West";
    }

    cout << left << "id: " <<this->id
         <<  ", type: " << "Hopper"
         <<  ", position: " <<"( "<< PAIR1.first <<", " << PAIR1.second << " )"
         <<  ", size: "<< this->size
            <<  ", hopLength: "<< this->hopLength
         << ", direction: " <<direction << endl;

}

string Hopper::getType()const
{
    return  to_string(this->getId())+" Hopper";
}