//
// Created by kevas on 27/03/2023.
//

#include "Crawler.h"
#include "Bug.h"
using namespace std;

Crawler ::Crawler(int id1, int x1, int y1, int direction1, int size1)
        : Bug(id1, x1, y1, direction1, size1) {

}


void Crawler::move()
{
    srand(time(nullptr));
    int direction = this->direction;


    std::pair<int, int> position = this->position;


    while (isWayBlocked())
    {
        direction = rand() % 4 + 1;
        this->setDirection(direction);
    }


        //// if not blocked move according to its direction
        if (direction ==directions::North)
        {
                position.second --;
        }else if(direction ==directions::East)
        {
                position.first ++;
        }else if(direction ==directions::South)
        {
                position.second ++;
        }else if(direction ==directions::West)
        {
                position.first --;
        }


    if (this->isAlive())
    {
    this->setPosition(position);
    this->addPath(position);
    }

}

void Crawler::print()const
{
    string direction;
    std::pair<int, int> PAIR1 = this->getPosition();
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
         <<  ", type: " << "Crawler"
         <<  ", position: " <<"( "<< PAIR1.first <<", " << PAIR1.second << " )"
         <<  ", size: "<< this->size
         << ", direction: " <<direction << endl;

}

string Crawler::getType()const
{
    return  to_string(this->getId())+" Crawler";
}