#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
//#include "Bug.h"
#include "Hopper.h"
#include "Crawler.h"
#include "Board.h"
#include <vector>
#include <sstream>
#include <iomanip>





using namespace std;
//void SFMLBoard();
void menu();

int main() {
    menu();
    return 0;
}

void menu()
{
    bool isRunning = true;
    Board *b = new Board();
    b->intialize("bugs.txt");



    int option1 = 0;
    while (isRunning) {
        cout << "1. Display all bugs" << endl
             << "2. Find bug by ID" << endl
             << "3. Tap the board" << endl
             << "4. Display history" << endl
             << "5. Display Cells" << endl
             << "6. Text based simulation" << endl
             << "7. SFML Simulation" << endl
             << "8. Play" << endl
             << "9. Tap Board" << endl
             << "10. Exit" << endl;
        cin >> option1;

        switch (option1) {
            case 1:
                b->displayBugs();
                break;
            case 2:
                cout << "Please enter bug ID: ";
                int inputId;
                cin >> inputId;
                 b->findBugById(inputId);
                break;
            case 3:
                b->tap();
                cout << "Tapped" << endl;
                break;
            case 4:
                b->displayPath();
                break;
            case 5:
                b->displayCells();
                break;
            case 6:
                b->runSimulation();
                break;
            case 7:
                b->boardSFMLSimulation();
                break;
            case 8:
                b->boardSFMLPlay();
                break;
            case 9:
                b->boardSFMLTap();
                break;
            case 10:
                cout << "Exiting program." << endl;
                b->writeToFile();
                isRunning = false;
                break;
            default:
                cout << "Invalid option, please try again." << endl;
                break;
        }
    }
}

