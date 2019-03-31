#include "includes.h"
#include "globals.h"
#include "game.h"
#include "menus.h"
#include "map.h"
#include "robot.h"
#include <vector>
#include <cctype>
#include <unistd.h>
#include <chrono> // for high_resolution_clock
#include <iomanip>

using namespace std;

Game::Game(int gamemode, int searchMethod, int level, int heur)
{

    //Ler aqui dos ficheiros
    this->level = level;
    readDataFromFiles();

    //TODO: Deixar o user escolher o lvl onde vai começar (0,1,2,...)

    switch (gamemode)
    {
    case 0:
        cout << "Starting a Singleplayer Game\n";
        this->soloMode();
        break;

    case 1:
        cout << "Starting a AI Game\n";
        this->botMode(searchMethod, heur);
        break;

    default:
        cout << "Invalid Mode\n";
        break;
    }
}

void Game::readDataFromFiles()
{
    Map m;
    Robot r;
    vector<vector<char>> v;
    vector<char> in_v;

    //Ler aqui dos ficheiros

    ifstream f_input("./maps.txt");
    string input;
    istringstream iss;
    getline(f_input, input); //To catch the first NEWMAP
    u_int state = 0;
    while (getline(f_input, input))
    {
        switch (state)
        {
        case 0:
            int cols, lines;
            iss.str(input);
            iss >> lines >> cols;
            m.setColsLines(cols, lines);
            state = 1;
            break;
        case 1:
            if (input == "ROBOTS")
            {
                state = 2;
                m.setLayout(v);
                v.clear();
                break;
            }

            for (u_int i = 0; i < input.size(); i++)
            {
                if (input[i] == 'X')
                    in_v.push_back('1');
                else if (input[i] == '0')
                    in_v.push_back('0');
                else
                    in_v.push_back(input[i]);
            }
            v.push_back(in_v);
            in_v.clear();
            break;
        case 2:
            if (input == "NEWMAP")
            {
                state = 0;
                maps.push_back(m);
                m.clearPosVectors();
                break;
            }
            r.icon = input[0];
            if (input[2] == 'P')
                r.is_helper = false;
            else
                r.is_helper = true;
            input = input.substr(4); // get the init and final coordinates all together on one string
            iss.clear();
            iss.str(input);
            iss >> r.line_c >> r.col_c >> r.final_line >> r.final_col;
            m.addInitPos(r.col_c, r.line_c);
            m.addFinalPos(r.final_col, r.final_line);
            m.robots.push_back(r);
            break;
        }
    }

    maps.push_back(m); // for the last map that does not finish when the next one starts, with NEWMAP

    f_input.close();
}

void Game::soloMode()
{
    /*
        SINGLEPLAYER
        
        1- Mostrar tabuleiro atual;
        2- Check if jogo acabou; -> Se acabou não pede/calcula jogada e dá uma mensagem de vitoria
        3- Pedir jogada      // Calcular jogada (Quando pede ajuda);
        4- Mover Robot pedido;
    */

    while (!isGameOver)
    {

        Map &currMap = maps.at(level); //reference to the current map

        if (currMap.checkGameOver())
        {

            currMap.createLayoutWithRobots(); //updates layoutWithRobots
            currMap.displayWithRobots(currMap.layoutWithRobots);

            cout << "Congratulations! Proceed to next level? (Y/N):  ";
            //cout << "Map 1: " << maps.at(0).robots.size() << '\n';
            //cout << "Map 2: " << maps.at(1).robots.size() << '\n';
            char c;
            bool isCValid = false;
            do
            {
                cin >> c;
                if (c == 'N' || c == 'n')
                {
                    return;
                }
                else if (c == 'Y' || c == 'y')
                {
                    isCValid = true;
                }

            } while (!isCValid);

            //O user quer continuar a jogar
            level++;
            if (level >= (int)maps.size())
                isGameOver = true;
            continue;
        }

        currMap.createLayoutWithRobots(); //updates layoutWithRobots
        currMap.displayWithRobots(currMap.layoutWithRobots);
        bool isInputValid = true; //to check if an input is valid
        int index, dir;

        do
        {
            isInputValid = true;
            cout << "Move: ";
            char r, d;
            cin >> r >> d;
            cin.ignore(256, '\n');
            index = interpretInputRobot(r);
            dir = interpretInputDir(d);

            //Checks for valid input
            if (index == -1)
                isInputValid = false;
            if (dir == -1)
                isInputValid = false;
            if (index >= (int)currMap.robots.size()) //check if the selected robot exists
                if (dir != 4 && dir != 5)
                    isInputValid = false;

            //Print if error
            if (!isInputValid)
                cout << "Invalid Input!\n";

        } while (!isInputValid);

        if (dir == 4)
        {
            cout << "Leaving game...\n";
            return;
        }
        if (dir == 5)
        {
            Node startN;
            startN.robots = currMap.robots;
            Node ret = switchAlgorithm(6, startN, currMap, 3); //use A* with heuristic nº3
            cout << "The best move is: " << this->convertOutputIndex(ret.moveSeq.at(0).first) << this->convertOutputDir(ret.moveSeq.at(0).second) << '\n';
            //cin.get();
            cin.ignore(256, '\n');
        }
        else
        {
            currMap.moveRobot(index, dir);
        }
    }

    cout << "\nYou finished all the levels!\n\n";
}

void Game::botMode(int searchMethod, int heur)
{

    /*
        MULTIPLAYER

        1- Calcular melhor conjunto de jogadas
        2- Mostrar estado inicial (sleep(1))
        3- While houver jogadas:
            1- dar pop da 1ª jogada
            2- executar a jogada
            3- mostrar estado atual (sleep(1))

    */

    while (!isGameOver)
    {

        Map &currMap = maps.at(level); //reference to the current map

        Node startN;
        startN.robots = currMap.robots;

        // Record start time
        auto start = chrono::high_resolution_clock::now();

        Node ret = switchAlgorithm(searchMethod, startN, currMap, heur);

        // Record end time
        auto finish = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = finish - start;

        if (ret.depth == -1) //Algorithm did not find an answer
        {
            cout << "\nAlgorithm Could Not Find an Answer...\n";
            cout << "Expanded " << ret.expansions << " nodes\n";
            cout << fixed << setprecision(1) << "Elapsed time: " << elapsed.count() * 1000 << " ms\n\n";
            return;
        }
        else
        {
            cout << "\nAlgorithm Finished Calculation Successfully!\n";
            cout << "Solution Found has " << ret.depth << " steps\n";
            cout << "Expanded " << ret.expansions << " nodes\n";

            cout << fixed << setprecision(1) << "Elapsed time: " << elapsed.count() * 1000 << " ms";
            if (elapsed.count() > 1)
                cout << " (" << elapsed.count() << "s) \n\n";
            else
                cout << "\n\n";
        }

        vector<pair<int, int>> moveSeq = ret.moveSeq;

        u_int moveIndex = 0;

        while (moveIndex < moveSeq.size())
        {
            currMap.createLayoutWithRobots(); //updates layoutWithRobots
            currMap.displayWithRobots(currMap.layoutWithRobots);

            pair<int, int> p = moveSeq.at(moveIndex);
            moveIndex++;
            sleep(1);
            currMap.moveRobot(p.first, p.second);
        }

        currMap.createLayoutWithRobots(); //updates layoutWithRobots
        currMap.displayWithRobots(currMap.layoutWithRobots);

        char c;
        cout << "Congratulations! Proceed to next level? (Y/N):  ";

        bool isCValid = false;
        do
        {
            cin >> c;
            if (c == 'N' || c == 'n')
                return;

            else if (c == 'Y' || c == 'y')
                isCValid = true;

        } while (!isCValid);

        //O user quer continuar a jogar
        level++;
        if (level >= (int)maps.size())
            isGameOver = true;
        continue;
    }
}

int Game::interpretInputRobot(char robot)
{
    int aux = toupper(robot);
    int index = aux - 65; //A maiuculo = 65, por isso index começa em 0
    if (index >= 0 && index < 20)
    { //aceita 0 a 19 robots
        return index;
    }
    else
    {
        return -1;
    }
}

int Game::interpretInputDir(char dir)
{
    switch (dir)
    {
    case 'w':
    case 'W':
        //up
        return 0;
    case 'd':
    case 'D':
        //right
        return 1;
    case 's':
    case 'S':
        //down
        return 2;
    case 'a':
    case 'A':
        //left
        return 3;
    case 'q':
    case 'Q':
        //leave
        return 4;
    case 'h':
    case 'H':
        //help
        return 5;

    default:
        return -1;
    }
}

char Game::convertOutputIndex(int index)
{
    char ret = index + 97;
    return ret;
}

char Game::convertOutputDir(int dir)
{
    switch (dir)
    {
    case 0:
        return 'w';
    case 1:
        return 'd';
    case 2:
        return 's';
    case 3:
        return 'a';

    default:
        return 'h'; //ask for help
    }
}
