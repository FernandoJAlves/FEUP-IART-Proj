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
        levelMenu(0, 0);
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

int levelMenu(int gamemode, int searchMethod)
{
    int input;
    cout << "Select the level: \n";
    cout << "1 - Level One (Easy - 1 Robot)\n";
    cout << "2 - Level Two (Easy - 2 Robots)\n";
    cout << "3 - Level Three (Easy - 1 Robot and 1 Helper)\n";
    cout << "4 - Level Four\n";
    cout << "5 - Level Five\n";
    cout << "0 - Leave Game\n";
    cout << "Option: ";
    cin >> input;

    switch (input)
    {
    case 1:
        Game(gamemode, searchMethod, 0);
        break;
    case 2:
        Game(gamemode, searchMethod, 1);
        break;
    case 3:
        Game(gamemode, searchMethod, 2);
        break;
    case 4:
        Game(gamemode, searchMethod, 3);
        break;
    case 5:
        Game(gamemode, searchMethod, 4);
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
        levelMenu(1, 1);
        break;
    case 2:
        levelMenu(1, 2);
        break;
    case 3:
        levelMenu(1, 3);
        break;
    case 4:
        levelMenu(1, 4);
        break;
    case 5:
        levelMenu(1, 5);
        break;
    case 6:
        levelMenu(1, 6);
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

int heuristicMenu()
{

    //TODO: Fazer o input mais resistente (string e chars, não estourar)
    int input;
    cout << "Select the Heuristic: \n";
    cout << "1 - Default Heuristic\n";
    cout << "2 - Lines/Columns Alligned\n";
    cout << "3 - Lines/Columns Obstacles\n";
    cout << "Option: ";
    cin >> input;

    switch (input)
    {
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 3;

    default:
        cout << "Invalid mode input!\n";
        return -1;
    }

    return 0;
}
