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
        Game(0, 0);
        break;
    case 2:
        botModeMenu();
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

int botModeMenu()
{
    //TODO: Fazer o input mais resistente (string e chars, não estourar)
    int input;
    cout << "Select your Search Method: \n";
    cout << "1 - DFS\n";
    cout << "2 - BFS\n";
    cout << "3 - Aprofundamento Progressivo\n";
    cout << "4 - Custo Uniforme\n";
    cout << "5 - Pesquisa Gulosa\n";
    cout << "6 - A*\n";
    cout << "0 - Leave Game\n";
    cout << "Option: ";
    cin >> input;

    switch (input)
    {
    case 1:
        Game(1, 1);
        break;
    case 2:
        Game(1, 2);
        break;
    case 3:
        Game(1, 3);
        break;
    case 4:
        Game(1, 4);
        break;
    case 5:
        Game(1, 5);
        break;
    case 6:
        Game(1, 6);
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
