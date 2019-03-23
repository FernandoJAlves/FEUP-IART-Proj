#include "includes.h"
#include "menus.h"
#include "game.h"

int mainMenu()
{  
    int input;
    cout << "Select your gamemode: \n";
    cout << "1 - Human player\n";
    cout << "2 - Bot Player\n";
    cout << "0 - Leave Game\n";
    cout << "Option: ";
    cin >> input;

    switch (input)
    {
    case 1:
        Game(0);
        break;
    case 2:
        Game(1);
        break;
    case 0:
        cout << "\nExiting game...\n";
        exit(1);

    default:
        cout << "Invalid mode input!\n";
        break;
    }

    return 0;
}