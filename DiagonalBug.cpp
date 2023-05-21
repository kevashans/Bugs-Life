#include "DiagonalBug.h"
using namespace std;
//
// Created by kevas on 12/04/2023.
//
DiagonalBug ::DiagonalBug(int id1, int x1, int y1, int direction1, int size1)
        : Bug(id1, x1, y1, direction1, size1) {

}

//bool DiagonalBug::diagonallyBlocked() const
//{
//    int direction = this->direction;
//    ////right most
//    if (position.first == 9 && (direction == diagonalDirections::NorthEast || diagonalDirections::SouthEast) ){
//        return true;
//
//    }////left most
//    else if(position.first ==0 && (direction == diagonalDirections::NorthWest || diagonalDirections::SouthWest)){
//        return true;
//    }
//    ////bottom most
//    else if(position.second ==9 && (direction == diagonalDirections::SouthWest|| diagonalDirections::SouthEast)){
//        return true;
//    } ////topmost
//    else if(position.second ==0 && (direction == diagonalDirections::NorthWest|| diagonalDirections::NorthEast)){
//        return true;
//    }////top right
//    else if(position.first == 9 && position.second == 0 && (direction == diagonalDirections::NorthEast || diagonalDirections::SouthEast || diagonalDirections::NorthWest)){
//        return true;
//    }
//    ////top left
//    else if(position.first == 0 && position.second == 0 && (direction == diagonalDirections::NorthWest|| diagonalDirections::SouthWest || diagonalDirections::NorthEast)){
//        return true;
//    }
//    ////bottom left
//    else if(position.first == 0 && position.second == 9 && (direction == diagonalDirections::NorthWest|| diagonalDirections::SouthWest || diagonalDirections::SouthEast)){
//        return true;
//    }
//    ////bottom right
//    else if(position.first == 9 && position.second == 9 && (direction == diagonalDirections::NorthEast|| diagonalDirections::SouthEast || diagonalDirections::SouthWest)){
//        return true;
//    }
//    else{
//        return false;
//    }
//}

void DiagonalBug::move()
{
    int direction = this->direction;
    srand(time(nullptr));
    int new_direction = direction;

    std::pair<int, int> position = this->position;

    while (direction == new_direction)
    {
        new_direction = rand() % 4 + 1;
//        this->setDirection(new_direction);
    }


    if (direction ==diagonalDirections::NorthEast )
    { ////NE (if not at the North eastern border)
        if(position.second - 1 >= 0 && position.first +1 <= 9)
        {
            position.second --;
            position.first ++;

        }else
        {
            this->setDirection(new_direction);
        }
    }else if(direction ==diagonalDirections::SouthEast)
    {////SE (if not at the south eastern border)
        if(position.second + 1 <= 9 && position.first +1 <=9)
        {
            position.first ++;
            position.second++;
        }else
        {
            this->setDirection(new_direction);
        }
    }else if(direction ==diagonalDirections::SouthWest)
    {////SW (if not at the South Western border)
        if(position.second + 1 <= 9 && position.first -1 >=0)
        {
            position.second ++;
            position.first--;
        }else
        {
            this->setDirection(new_direction);
        }
    }else if(direction ==diagonalDirections::NorthWest)
    {////NW (if not at the North western border)
        if(position.second - 1 >= 0 && position.first -1 >=0)
        {
            position.first --;
            position.second--;
        }else
        {
            this->setDirection(new_direction);
        }
    }

    if(this->alive)
    {
        this->setPosition(position);
        this->addPath(position);
    }

}
void DiagonalBug::print()const
{
    string direction;
    std::pair<int, int> PAIR1 = this->getPosition();

    if (this->direction==diagonalDirections::NorthEast)
    {
        direction = "North East";
    }else if(this->direction==diagonalDirections::SouthEast)
    {
        direction ="South East";
    }else if(this->direction==diagonalDirections::SouthWest)
    {
        direction ="South West";
    }else if(this->direction==diagonalDirections::NorthWest)
    {
        direction ="North West";
    }

    cout << left << "id: " <<this->id
         <<  ", type: " << "DiagonalBug"
         <<  ", position: " <<"( "<< PAIR1.first <<", " << PAIR1.second << " )"
         <<  ", size: "<< this->size
         << ", direction: " <<direction << endl;


}

string DiagonalBug::getType()const
{
    return  to_string(this->getId())+" DiagonalBug";
}
