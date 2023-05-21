//
// Created by kevas on 30/03/2023.
//

#include <fstream>
#include <sstream>
#include "Board.h"
#include "Hopper.h"
#include "Crawler.h"
#include "DiagonalBug.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <ctime>


using namespace std;
Board::Board()
{
    this->super = new Crawler(0,0,0,4,12);
    this->size = 100;

}
void Board::parseLine(string line, Data &bug) const
{

    try
    {
        stringstream ss(line);
        string temp;

        getline(ss, bug.type, ';');

        getline(ss, temp, ';');
        bug.id = stoi(temp);

        getline(ss, temp, ';');
        bug.x = stoi(temp);

        getline(ss, temp, ';');
        bug.y = stoi(temp);

        getline(ss, temp, ';');
        bug.direction = stoi(temp);

        getline(ss, temp, ';');
        bug.size = stoi(temp);

        getline(ss, temp, ';');
        bug.hopLength = stoi(temp);
    }
    catch (exception e)
    {
        cout << "Error" << endl;
    }
}

void Board::intialize(std::string fname)
{
    ifstream fin(fname);
    this->cells;
    if (fin.good())
    {
        string line;

        while(!fin.eof()){
            getline(fin,line);

            Data b;

            parseLine(line,b);

            if (b.type == "H")
            {
                Hopper *h1 = new Hopper(b.id, b.x,b.y,b.direction,b.size,b.hopLength);
                this->bugs.push_back(h1);
                this->cells[(b.x * 10) + b.y].push_back(h1);

            }else if(b.type =="C")
            {
                Crawler *c1 = new Crawler(b.id, b.x,b.y,b.direction,b.size);
                this->bugs.push_back(c1);
                this->cells[(b.x * 10) + b.y].push_back(c1);
            }else if(b.type =="D")
            {
                DiagonalBug *d1 = new DiagonalBug(b.id, b.x,b.y,b.direction,b.size);
                this->bugs.push_back(d1);
                this->cells[(b.x * 10) + b.y].push_back(d1);
            }


        }
        fin.close();
        cout << "File closed" << endl;
    }
    else
    {
        cout << "Error opening file" << endl;
    }
}
void Board::displayBugs() const
{
    for (int i = 0; i < this->bugs.size(); ++i)
    {
        bugs[i]->print();
    }
}

void Board::findBugById(int id) const
{
    bool found = false;
    for (int i = 0; i < this->bugs.size(); ++i)
    {
        if (bugs[i]->getId() == id)
        {
            bugs[i]->print();
            found = true;
        }
    }
    if (!found)
    {
        cout << "Bug with id " << id << " not found." << endl;
    }
}

void Board::displayCells()const
{
    bool comma;
    for (int i = 0; i < this->size; ++i)
    {
        ////print celss
        comma=true;
        cout << "(" <<i/10<<", "<< i%10 << ")" ;
        if(this->cells[i].size()>0)
        {
            for (int j = 0; j < this->cells[i].size(); ++j)
            {
                ////so no comma appears at the end
                if (j == this->cells[i].size()-1){
                    comma = false;
                }
                ////print bugs information
                if(this->cells[i].at(j)->isAlive())
                {
                    cout << " ";
                    cout << this->cells[i].at(j)->getType();
                    if (comma){
                        cout << ",";
                    }
                }


            }
        }
        cout << endl;
    }

}

void Board::tap()
{
    srand(time(nullptr));

    ////check if there are more than one bug alive
    if(countAlive() > 1)
    {
        for (int i = 0; i < this->bugs.size(); ++i)
        {
            ////variables
            Bug *b = this->bugs.at(i);
            std::pair<int, int> position = b->getPosition();



            ////remove from old position
            vector<Bug*>& cell = this->cells[(position.first * 10) + position.second];

            for (int j = 0; j < cell.size(); ++j)
            {
                if (cell.at(j)->getId() == b->getId())
                {
                    cell.erase(this->cells[(position.first * 10) + position.second].begin() + j);
                }

            }


            //// move and add to new position
            b->move();

            std::pair<int, int> newPosition = b->getPosition();
            this->cells[(newPosition.first * 10) + newPosition.second].push_back(b);

        }

        //// eat function
        for (int i = 0; i < this->size; ++i)
        {
            ////compare each bug
            for (int j = 0; j < this->cells[i].size(); ++j)
            {

                Bug* bug1 = this->cells[i].at(j);

                for (int k = 0; k < this->cells[i].size(); ++k)
                {

                    Bug* bug2 = this->cells[i].at(k);

                    //// if bug2 bigger
                    if (bug2->getSize() > bug1->getSize() &&
                            bug2->isAlive() && bug1->isAlive())
                    {
                        bug1->setAlive(false);
                        bug1->setEatenBy(bug2->getId());
                        bug2->setSize(bug2->getSize()+bug1->getSize());
                   ////if bug1 bigger
                    } else if (bug2->getSize() < bug1->getSize() &&
                               bug2->isAlive() && bug1->isAlive())
                    {
                        bug2->setAlive(false);
                        bug2->setEatenBy(bug1->getId());
                        bug1->setSize(bug2->getSize()+bug1->getSize());

                    }
                    //// bug must be alive and must not be compared to itself
                    else if (bug2->getSize() == bug1->getSize() &&
                            bug1->getId() != bug2->getId() &&
                            bug2->isAlive() && bug1->isAlive())
                    {
                        int rand = ::rand() % 2 + 1;
                        if (rand == 1)
                        {
                            bug2->setAlive(false);
                            bug2->setEatenBy(bug1->getId());
                            bug1->setSize(bug2->getSize()+bug1->getSize());
                        } else if (rand == 2)
                        {
                            bug1->setAlive(false);
                            bug1->setEatenBy(bug2->getId());
                            bug2->setSize(bug2->getSize()+bug1->getSize());
                        }
                    }
                }
            }
        }
    }
};

void Board::displayPath() const
{
////go through all the bugs
    for (int i = 0; i < this->bugs.size(); ++i)
    {
        Bug *b1 = this->bugs.at(i);
        ////display the type of bug
        cout << b1->getType() << ": " << endl;
        const std::list<std::pair<int, int>> path = b1->getPath();

        ////go through the bug path history
        for (std::list<std::pair<int, int>>::const_iterator it = path.begin(); it != path.end(); ++it)
        {
            ////display the path history
            cout << "(" << it->first << "," << it->second << ")";

        }
        ////if dead display eater
        if (!b1->isAlive())
        {
            if (b1->getEatenBy() == 0)
            {
                cout << "; eaten by : Player";
            }else
            {
                cout << "; eaten by : " << b1->getEatenBy();
            }
        }
        cout << endl;
    }

}
int Board::countAlive() const
{
    int count =0;
    ////go through bugs
    for (int i = 0; i < this->bugs.size(); ++i) {
        if (this->bugs.at(i)->isAlive()){
            //// if alive count
            count++;
        }
    }
    return count;

}
void Board::writeToFile() const
{
    //// source: https://cplusplus.com/doc/tutorial/files/
    time_t now = time(0);
    tm* dt = localtime(&now);
    ofstream myfile("bugs_life_history_" + to_string(dt->tm_mday) + "-" + to_string(dt->tm_mon) + "-"+to_string(dt->tm_year-100)+"_"+to_string(dt->tm_hour)+"-"+to_string(dt->tm_min) + ".out");

////non player bugs
    for (int i = 0; i < this->bugs.size(); ++i)
    {
        Bug* b = this->bugs.at(i);
        const std::list<std::pair<int, int>> path = b->getPath();

        myfile << b->getType();

        if(path.size() > 0)
        {
            for (std::list<std::pair<int, int>>::const_iterator it = path.begin();
                 it != path.end(); ++it)
            {
                myfile << "(" << it->first << "," << it->second << ")";
            }
        }

        if (!this->bugs.at(i)->isAlive())
        {
            if(b->getEatenBy()==0)
            {
                myfile << " eaten by: Player";
            }
            else
            {
                myfile << " eaten by: " + to_string(b->getEatenBy())  ;
            }
        }
        myfile <<"\n";
    }

    ////super bug

    if (super->getPath().size() > 0)
    {
        myfile << "Player ";

        const std::list<std::pair<int, int>> path = this->super->getPath();
        for (std::list<std::pair<int, int>>::const_iterator it = path.begin();
             it != path.end(); ++it)
        {
            myfile << "(" << it->first << "," << it->second << ")";

        }
    }

    if (!this->super->isAlive())
    {
        myfile << " eaten by: " + to_string(this->super->getEatenBy())  ;
    }
    myfile <<"\n";
    myfile.close();
}

void Board::runSimulation()
{
    //variables
    int count;
    bool finished =false;


    while (!finished)
    {
        //// source: chatGPT
        ////The chrono library, a flexible collection of types that track time with varying degrees of precision (https://en.cppreference.com/w/cpp/chrono)
        ////time point at start
        auto start = std::chrono::high_resolution_clock::now();

        ////repeated functions
        tap();
        //// if only one bug left end simulation
        if(countAlive() == 1)
        {
            finished =true;
        }

        //display status
        cout << "_______________________________" << endl;
        cout << "Alive: "<<countAlive()<<endl;
        displayPath();

        ////time point after start
        auto end = std::chrono::high_resolution_clock::now();
        ////functions duration to finish
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        //// 1 second - duration (if function finishes in under one second wait the remainder of the time)
        std::this_thread::sleep_for(std::chrono::milliseconds(1000) - duration);

    }
    //// when finished, write to file
    writeToFile();
}

void Board::boardSFMLPlay()
{
    ////window
    sf::RenderWindow window(sf::VideoMode(1400, 1000), "SFML works!");
    ////variables
    bool lost = false;
    sf::Font font;
    font.loadFromFile("OpenSans-Bold.ttf");
    sf::Texture textureSuper;
    textureSuper.loadFromFile("Super.png");
    sf::Texture textureCrawler;
    textureCrawler.loadFromFile("Crawler.png");
    sf::Texture textureHopper;
    textureHopper.loadFromFile("Hopper.png");
    sf::Texture textureDiagonal;
    textureDiagonal.loadFromFile("Diagonal.png");
    sf::RectangleShape square(sf::Vector2f(100, 100));
    square.setOutlineColor(sf::Color::Black);
    square.setOutlineThickness(2);
    ////DETAIL
    //portrait
    sf::Texture textureDetail;
    sf::RectangleShape detailPortrait(sf::Vector2f(300, 300));
    detailPortrait.setPosition(1010, 10);
    //type
    sf::Text detailText;
    detailText.setPosition(1010, 400);
    detailText.setFont(font);
    detailText.setFillColor(sf::Color::Green);
    //size
    sf::Text detailSize;
    detailSize.setPosition(1010, 450);
    detailSize.setFont(font);
    detailSize.setFillColor(sf::Color::Red);

    ////lists of bug sprites and its sizes
    list<sf::CircleShape> circles;
    list<sf::Text> sizes;
    ////super
    sf::CircleShape super(50);
    sf::FloatRect superBound = super.getGlobalBounds();
    super.setTexture(&textureSuper);
    pair<int, int> positionSup = this->super->getPosition();
    pair<int, int> newPos = positionSup;
    ////lost message
    sf::Text lostMsg;
    lostMsg.setFont(font);
    lostMsg.setString("YOU LOST");
    lostMsg.setFillColor(sf::Color::Red);
    lostMsg.setCharacterSize((int) 70);
    lostMsg.setPosition(50, 50);
    ////Win message
    sf::Text winMsg;
    winMsg.setFont(font);
    winMsg.setString("YOU WON");
    winMsg.setFillColor(sf::Color::Green);
    winMsg.setCharacterSize((int) 70);
    winMsg.setPosition(50, 50);

    auto start =  std::chrono::high_resolution_clock::now();
    while (window.isOpen())
    {
        circles.clear();
        sizes.clear();

        ////bugs sprite
        createSprites(font, textureCrawler, textureHopper, textureDiagonal, circles, sizes);

        sf::Event event;

        while (window.pollEvent(event))
        {
            HandleEvents(detailPortrait, detailText, detailSize, window, circles, event);

            positionSup = this->super->getPosition();
            ////desplay detail when clicking super bug
            if (superBound.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
            {
                detailPortrait.setTexture(super.getTexture());
                detailText.setString("Player");
                detailSize.setString(to_string(this->super->getSize()));
            }

            ////super bug functionalities

            if (event.type == sf::Event::KeyPressed && !lost)
            {
                if (event.key.code == sf::Keyboard::Up) {
                    if (positionSup.second != 0)
                    {
                        newPos.second--;
                    }
                } else if (event.key.code == sf::Keyboard::Down)
                {
                    if (positionSup.second != 9)
                    {
                        newPos.second++;
                    }
                } else if (event.key.code == sf::Keyboard::Right)
                {
                    if (positionSup.first != 9)
                    {
                        newPos.first++;
                    }
                } else if (event.key.code == sf::Keyboard::Left)
                {
                    if (positionSup.first != 0)
                    {
                        newPos.first--;
                    }
                }

            }
            this->super->setPosition(newPos);
        }
        this->super->addPath(positionSup);

        super.setPosition(this->super->getPosition().first * 100, this->super->getPosition().second * 100);
        superBound= super.getGlobalBounds();
        ////super bug eating function
        ////check the cell where the superbug is for other bugs
        for (int i = 0; i < this->cells[(newPos.first * 10) + newPos.second].size(); ++i)
        {
            Bug *bug = this->cells[(newPos.first * 10) + newPos.second].at(i);

            ////if super is bigger or the same size as the other bug , super wins
            if (bug->getSize() < this->super->getSize() && bug->isAlive() ||
                bug->getSize() == this->super->getSize() && bug->isAlive())
            {
                bug->setEatenBy(this->super->getId());
                bug->setAlive(false);
                this->super->setSize(this->super->getSize() + bug->getSize());
            } ////if super is a smaller than the other bug , super lose
            else if (bug->getSize() > this->super->getSize() && bug->isAlive())
            {
                this->super->setAlive(false);
                this->super->setEatenBy(bug->getId());
                lost = true;
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        ////if duration longer or equal to one second
        if(end - start >=std::chrono::milliseconds(1000) )
        {
            ////adjust the timer for the next loop (removed the sleep function)
            start = end;
            tap();
        }
        window.clear();
        ////arena
        for (int i = 0; i < 10; ++i)
        {
            for (int j = 0; j < 10; ++j)
            {
                square.setFillColor(sf::Color::White); // white
                square.setPosition(i * square.getSize().x, j * square.getSize().y);
                window.draw(square);
            }
        }
        ////super bug variables
        sf::Text sizeSup;
        sizeSup.setFont(font);
        sizeSup.setString(to_string(this->super->getSize()));
        sizeSup.setCharacterSize((int) 25);
        sizeSup.setFillColor(sf::Color::White);
        sizeSup.setPosition((this->super->getPosition().first * 100) + 25,
                            (this->super->getPosition().second * 100) + 39);


        window.draw(super);
        window.draw(sizeSup);
        //// if superbug eaten display lost message
        if (lost)
        {
            window.draw(lostMsg);
        }
        //// if only superbug left
        if (countAlive() == 0)
        {
            window.draw(winMsg);
        }
        ////other bugs
        drawSprites(detailPortrait, detailText, detailSize, window, circles, sizes);

    }
}





void Board::boardSFMLSimulation()
{
    ////variables
    sf::Font font;
    font.loadFromFile("OpenSans-Bold.ttf");
    sf::Texture textureCrawler;
    textureCrawler.loadFromFile("Crawler.png");
    sf::Texture textureHopper;
    textureHopper.loadFromFile("Hopper.png");
    sf::Texture textureDiagonal;
    textureDiagonal.loadFromFile("Diagonal.png");
    sf::RectangleShape square(sf::Vector2f(100, 100));
    square.setOutlineColor(sf::Color::Black);
    square.setOutlineThickness(2);
    ////DETAIL
    //portrait
    sf::Texture textureDetail;
    sf::RectangleShape detailPortrait(sf::Vector2f(300, 300));
    detailPortrait.setPosition(1010,10);
    //type
    sf::Text detailText;
    detailText.setPosition(1010,400);
    detailText.setFont(font);
    detailText.setFillColor(sf::Color::Green);
    //size
    sf::Text detailSize;
    detailSize.setPosition(1010,450);
    detailSize.setFont(font);
    detailSize.setFillColor(sf::Color::Red);



    ////window
    sf::RenderWindow window(sf::VideoMode(1400, 1000), "SFML works!");



    ////lists of bug sprites and its sizes
    list<sf::CircleShape> circles;
    list<sf::Text> sizes;



    auto start =  std::chrono::high_resolution_clock::now();
    while (window.isOpen())
    {
        circles.clear();
        sizes.clear();
        ////tap every second


        ////bugs sprite
        createSprites(font, textureCrawler, textureHopper, textureDiagonal, circles, sizes);


        sf::Event event;
        while (window.pollEvent(event))
        {
            HandleEvents(detailPortrait, detailText, detailSize, window, circles, event);
        }


        auto end = std::chrono::high_resolution_clock::now();

        ////if duration longer or equal to one second
        if(end - start >=std::chrono::milliseconds(1000) )
        {
            ////adjust the timer for the next loop (removed the sleep function)
            start = end;
            tap();
        }
        window.clear();

        ////arena
        for (int i = 0; i < 10; ++i)
        {
            for (int j = 0; j < 10; ++j)
            {
                square.setFillColor(sf::Color::White); // white
                square.setPosition(i * square.getSize().x, j * square.getSize().y);
                window.draw(square);
            }
        }

        ////draw sprites
        drawSprites(detailPortrait, detailText, detailSize, window, circles, sizes);


    }
}

void
Board::drawSprites(const sf::RectangleShape &detailPortrait, const sf::Text &detailText, const sf::Text &detailSize,
                   sf::RenderWindow &window, list<sf::CircleShape> &circles, list<sf::Text> &sizes) const{
    ////draw bug sprites
    for (list<sf::CircleShape>::iterator it = circles.begin(); it != circles.end(); ++it)
    {
        window.draw(*it);
    }
    ///draw bug size numbers
    for (list<sf::Text>::iterator it = sizes.begin(); it != sizes.end(); ++it)
    {
        window.draw(*it);
    }
    ////draw detail tab if a bug is selected
    if (detailPortrait.getTexture()!= NULL)
    {
        window.draw(detailPortrait);
        window.draw(detailText);
        window.draw(detailSize);
    }

    window.display();
}

void Board::HandleEvents(sf::RectangleShape &detailPortrait, sf::Text &detailText, sf::Text &detailSize,
                         sf::RenderWindow &window, list<sf::CircleShape> &circles, const sf::Event &event) {
    ////when closed write history
    if (event.type == sf::Event::Closed)
    {
        window.close();
        writeToFile();

    } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        for (sf::CircleShape &sprite: circles)
        {
            sf::FloatRect bounds = sprite.getGlobalBounds();
            if (bounds.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
            {
                ////sprite flashes red when clicked
                sprite.setFillColor(sf::Color::Red);

                ////set texture of the detail tab to be the clicked bug texture
                detailPortrait.setTexture(sprite.getTexture());
                ////display the clicked bug size and type
                for (int i = 0; i < bugs.size(); ++i)
                {
                   if(bugs.at(i)->getPosition().first == sprite.getPosition().x / 100 && bugs.at(i)->getPosition().second == sprite.getPosition().y / 100 )
                   {
                       detailText.setString(bugs.at(i)->getType());
                       detailSize.setString( "Size: " + to_string(bugs.at(i)->getSize()));
                   }
                }
                break;
            }
        }
    }
}

void Board::boardSFMLTap()
{
    ////variables
    sf::Font font;
    font.loadFromFile("OpenSans-Bold.ttf");
    sf::Texture textureCrawler;
    textureCrawler.loadFromFile("Crawler.png");
    sf::Texture textureHopper;
    textureHopper.loadFromFile("Hopper.png");
    sf::Texture textureDiagonal;
    textureDiagonal.loadFromFile("Diagonal.png");
    sf::RectangleShape square(sf::Vector2f(100, 100));
    square.setOutlineColor(sf::Color::Black);
    square.setOutlineThickness(2);
    ////DETAIL
    //portrait
    sf::Texture textureDetail;
    sf::RectangleShape detailPortrait(sf::Vector2f(300, 300));
    detailPortrait.setPosition(1010,10);
    //type
    sf::Text detailText;
    detailText.setPosition(1010,400);
    detailText.setFont(font);
    detailText.setFillColor(sf::Color::Green);
    //size
    sf::Text detailSize;
    detailSize.setPosition(1010,450);
    detailSize.setFont(font);
    detailSize.setFillColor(sf::Color::Red);

    ////window
    sf::RenderWindow window(sf::VideoMode(1400, 1000), "SFML works!");

    ////lists of bug sprites and its sizes
    list<sf::CircleShape> circles;
    list<sf::Text> sizes;



    while (window.isOpen())
    {
        circles.clear();
        sizes.clear();
        ////tap every second


        ////bugs sprite
        createSprites(font, textureCrawler, textureHopper, textureDiagonal, circles, sizes);

        sf::Event event;
        while (window.pollEvent(event))
        {
            HandleEvents(detailPortrait, detailText, detailSize, window, circles, event);
            ///left mouse button calls the tap function
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    tap();
                }
            }

        }

        window.clear();

        ////arena
        for (int i = 0; i < 10; ++i)
        {
            for (int j = 0; j < 10; ++j)
            {
                square.setFillColor(sf::Color::White); // white
                square.setPosition(i * square.getSize().x, j * square.getSize().y);
                window.draw(square);
            }
        }

        ////draw sprites
        drawSprites(detailPortrait, detailText, detailSize, window, circles, sizes);


    }
}

void Board::createSprites(const sf::Font &font, sf::Texture &textureCrawler, sf::Texture &textureHopper,
                          sf::Texture &textureDiagonal, list<sf::CircleShape> &circles, list<sf::Text> &sizes) {
    ////create sprites for each bugs
    for (int i = 0; i < bugs.size(); ++i)
    {

        Bug *b = bugs.at(i);
        if (b->isAlive())
        {
            ////create circle
            pair<int,int> position = b->getPosition();
            sf::CircleShape shape(50);
            shape.setPosition(position.first*100,position.second*100);

            if (b->getType().find("Crawler")!= std::string::npos)
            {
                shape.setTexture(&textureCrawler);
            }else if(b->getType().find("Hopper")!= std::string::npos)
            {
                shape.setTexture(&textureHopper);
            }else if(b->getType().find("Diagonal")!= std::string::npos)
            {
                shape.setTexture(&textureDiagonal);
            }
            circles.push_back(shape);


            ////sizes
            sf::Text size;
            size.setFont(font);
            size.setString(to_string(b->getSize()));
            size.setCharacterSize((int)25);
            size.setFillColor(sf::Color::Cyan);
            size.setPosition((position.first*100)+ 25, (position.second*100) + 39);
            sizes.push_back(size);
        }
    }
}










