//
// Created by kevas on 30/03/2023.
//

#ifndef BUGS_LIFE_BOARD_H
#define BUGS_LIFE_BOARD_H

#include <vector>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Bug.h"

class Board{
    struct Data{
        std::string type;
        int id;
        int x;
        int y;
        int direction;
        int size;
        int hopLength ;

    };
private:
std::vector <Bug*>cells[100];
std::vector<Bug*>bugs;
Bug*super;
int size;

public:
    Board();
    void intialize(std::string filename);
    void parseLine(std::string line, Data &bug)const;
    void tap();
    void findBugById(int id)const;
    void displayBugs()const;
    void displayCells()const;
    void displayPath()const;
    void boardSFMLSimulation();
    void boardSFMLPlay();
    void boardSFMLTap();
    void runSimulation();
    void writeToFile()const;
    int countAlive()const;

    void HandleEvents(sf::RectangleShape &detailPortrait, sf::Text &detailText, sf::Text &detailSize,
                 sf::RenderWindow &window,
                 std::list<sf::CircleShape> &circles, const sf::Event &event);

    void drawSprites(const sf::RectangleShape &detailPortrait, const sf::Text &detailText, const sf::Text &detailSize,
                     sf::RenderWindow &window, std::list<sf::CircleShape> &circles, std::list<sf::Text> &sizes) const;


    void createSprites(const sf::Font &font, sf::Texture &textureCrawler, sf::Texture &textureHopper,
                       sf::Texture &textureDiagonal, std::list<sf::CircleShape> &circles, std::list<sf::Text> &sizes);
};
#endif //BUGS_LIFE_BOARD_H
