#include "includes.h"
#include "globals.h"
#include "game.h"
#include "menus.h"
#include "map.h"
#include "robot.h"
#include <vector>
#include <cctype>
using namespace std;

Game::Game(int gamemode)
{

    Map m;
    Robot r;
    vector<vector<char>> v;

    //Ler aqui dos ficheiros
    stringstream ss;
    
    ifstream f_input("./maps.txt");
    string input;
    getline(f_input,input); //To catch the first NEWMAP
    ui state = 1;
    while(getline(f_input,input))
    {
        switch(state)
        {
            case 0:
                //mata
                break;
            case 1:
                int cols, lines;
                ss >> lines >> cols;
                //falta povoar aqui o map
                state = 2;
                break;
            case 2:
                if(input == "ROBOTS")
                {
                    state = 3;
                    continue;
                }
                vector<char> in_v;
                for(ui i=0; i < input.size();i++)
                {
                    if(input[i] == 'X')
                        in_v.push_back('1');
                    else if(input[i] == '0')
                        in_v.push_back('0');
                    else 
                        in_v.push_back(input[i]);
                }
                v.push_back(in_v);
                break;
            case 3:

        }
    }

    /*
    vector<vector<char>> v = {{'1', '1', '1', '1', '1', '1', '1'},
                              {'1', '0', '1', '0', '0', '0', '1'},
                              {'1', '0', '1', '0', '1', '0', '1'},
                              {'1', '0', '1', '0', '1', '0', '1'},
                              {'1', '0', '1', '0', '1', '0', '1'},
                              {'1', '0', '0', '0', '1', 'A', '1'},
                              {'1', '1', '1', '1', '1', '1', '1'}};

    m.setLayout(v);
    r.line_c = 1;
    r.col_c = 1;
    r.final_line = 5;
    r.final_col = 5;
    r.icon = 'a';
    m.robots.push_back(r);

    maps.push_back(m);*/

    f_input.close();

    switch (gamemode)
    {
    case 0:
        cout << "Starting a Singleplayer Game\n";
        this->soloMode();
        break;

    case 1:
        cout << "Starting a AI Game\n";
        this->botMode();
        break;

    default:
        cout << "Invalid Mode\n";
        break;
    }
}

void Game::soloMode()
{
    /*
        SINGLEPLAYER
        
        1- Mostrar tabuleiro atual;
        2- Check if jogo acabou; -> Se acabou não pede/calcula jogada e dá uma mensagem de vitoria
        3- Pedir jogada (SP) // Calcular jogada (Quando pede ajuda);
        4- Mover Robot pedido;
    */

    while (!isGameOver)
    {
        
        maps.at(level).createLayoutWithRobots();
        maps.at(level).displayWithRobots(maps.at(level).layoutWithRobots);
        bool isInputValid = true;
        int index, dir;
        do
        {
            cout << "Move: ";
            char r, d;
            cin >> r >> d;
            cin.ignore(256, '\n');
            index = interpretInputRobot(r);
            dir = interpretInputDir(d);
            if(index == -1)
                isInputValid = false;
            if(dir == -1)
                isInputValid = false;  

        }while (!isInputValid);

        cout << "Robot: " << index << "\nDir: " << dir << '\n';
        if(dir == 4){
            isGameOver = true;
            continue;
        }
    
    }
}

int Game::interpretInputRobot(char robot)
{
    int aux = toupper(robot);
    int index = aux-65; //A maiuculo = 65, por isso index começa em 0
    if(index >= 0 && index < 20){ //aceita 0 a 19 robots
        return index;
    }
    else{
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

void Game::botMode()
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
}