#include "includes.h"
#include "game.h"
#include "menus.h"
#include "map.h"
#include "robot.h"
#include <vector>
using namespace std;



Game::Game(int gamemode){
    
    //Ler aqui dos ficheiros
    
    vector<vector<char>> v = {{'1', '1', '1', '1', '1', '1', '1'},
                              {'1', '0', '1', '0', '0', '0', '1'},    
                              {'1', '0', '1', '0', '1', '0', '1'}, 
                              {'1', '0', '1', '0', '1', '0', '1'},
                              {'1', '0', '1', '0', '1', '0', '1'},
                              {'1', '0', '0', '0', '1', 'A', '1'}, 
                              {'1', '1', '1', '1', '1', '1', '1'}};

    Map m;
    m.setLayout(v);
    Robot r;
    r.line_c = 1;
    r.col_c = 1;
    r.final_line = 5;
    r.final_col = 5;
    r.icon = 'a';
    m.robots.push_back(r);

    maps.push_back(m);
    
    
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

void Game::soloMode(){
    /*
        SINGLEPLAYER
        
        1- Mostrar tabuleiro atual;
        2- Check if jogo acabou; -> Se acabou não pede/calcula jogada e dá uma mensagem de vitoria
        3- Pedir jogada (SP) // Calcular jogada (Quando pede ajuda);
        4- Mover Robot pedido;
    */
    
    while(!isGameOver){

        //maps.at(level).createLayoutWithRobots();
        //maps.at(level).displayWithRobots(maps.at(level).layoutWithRobots);
        cout << "Move: ";
        char robot, dir;
        cin >> robot >> dir;


    }


}

void Game::botMode(){

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