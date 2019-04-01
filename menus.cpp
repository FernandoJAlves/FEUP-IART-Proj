#include "includes.h"
#include "menus.h"
#include "game.h"

int mainMenu()
{
    int input;
    do
    {
        if(cin.fail())
        {
            cout << "Invalid input...\n\n";
            cin.clear();
            cin.ignore(1000,'\n');
        }

        cout << "Select your gamemode: \n";
        cout << "1 - Human player\n";
        cout << "2 - Bot Player\n";
        cout << "0 - Leave Game\n";
        cout << "Option: ";
        cin >> input;

    } while(cin.fail());

    switch (input)
    {
    case 1:
        levelMenu(0, 0, 0);
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

int levelMenu(int gamemode, int searchMethod, int heur)
{

    int input;
    do
    {
        if(cin.fail())
        {
            cout << "Invalid input...\n\n";
            cin.clear();
            cin.ignore(1000,'\n');
        }

        cout << "Select the level: \n";
        cout << "1 - Level One (Easy - 1 Robot and 1 Helper)\n";
        cout << "2 - Level Two\n";
        cout << "3 - Level Three\n";
        cout << "4 - Level Four (Hard - 1 Robot and 3 Helpers)\n";
        cout << "5 - Level Five (Hard - 3 Robots and 1 Helper)\n";
        cout << "6 - Level Six (Hard - 1 Robots and 6 Helpers)\n";
        cout << "7 - Level Seven (Hard - 3 Robots and 1 Helper)\n";
        cout << "0 - Leave Game\n";
        cout << "Option: ";
        cin >> input;

    } while(cin.fail());

    switch (input)
    {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        Game(gamemode, searchMethod, (input-1), heur);
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

    int input;
    do
    {
        if(cin.fail())
        {
            cout << "Invalid input...\n\n";
            cin.clear();
            cin.ignore(1000,'\n');
        }

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

    } while(cin.fail());

    int h;

    switch (input)
    {
    case 1:
        levelMenu(1, 1, 0);
        break;
    case 2:
        levelMenu(1, 2, 0);
        break;
    case 3:
        levelMenu(1, 3, 0);
        break;
    case 4:
        levelMenu(1, 4, 0);
        break;
    case 5:
        h = heuristicMenu();
        if (h != -1)
            levelMenu(1, 5, h);
        else
            exit(1);
        break;
    case 6:
    {
        h = heuristicMenu();
        if (h != -1)
            levelMenu(1, 6, h);
        else
            exit(1);
        break;
    }

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

    int input;
    do
    {
        if(cin.fail())
        {
            cout << "Invalid input...\n\n";
            cin.clear();
            cin.ignore(1000,'\n');
        }

        cout << "Select the Heuristic: \n";
        cout << "1 - Default Heuristic\n";
        cout << "2 - Lines/Columns Alligned\n";
        cout << "3 - Lines/Columns Obstacles\n";
        cout << "4 - Area Occupied\n";
        cout << "Option: ";
        cin >> input;

    } while(cin.fail());


    switch (input)
    {
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 3;
    case 4:
        return 4;

    default:
        cout << "Invalid mode input!\n";
        return -1;
    }

    return 0;
}
