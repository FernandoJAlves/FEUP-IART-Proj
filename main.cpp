#include "includes.h"
#include "menus.h"
#include "map.h"
#include "robot.h"

vector<Map> maps;
int global_c = 123;

int main()
{

    //read maps from file

    //mainMenu();


    //ciclo de jogo

    /*
        SINGLEPLAYER
        
        1- Mostrar tabuleiro atual;
        2- Check if jogo acabou; -> Se acabou não pede/calcula jogada e dá uma mensagem de vitoria
        3- Pedir jogada (SP) // Calcular jogada (Quando pede ajuda);
        4- Mover Robot pedido;

        MULTIPLAYER

        1- Calcular melhor conjunto de jogadas
        2- Mostrar estado inicial (sleep(1))
        3- While houver jogadas:
            1- dar pop da 1ª jogada
            2- executar a jogada
            3- mostrar estado atual (sleep(1))

    */

    //TESTING
    vector<vector<char>> v = {{'1', '1', '1', '1', '1'},
                              {'1', '0', '1', 'A', '1'},    
                              {'1', '0', '1', '0', '1'}, 
                              {'1', '0', '0', '0', '1'}, 
                              {'1', '1', '1', '1', '1'}};

    Map m;
    m.setLayout(v);
    Robot r;
    r.line_c = 1;
    r.col_c = 1;
    r.icon = 'a';
    m.robots.push_back(r);

    maps.push_back(m);

    
    maps.at(0).displayWithRobots(maps.at(0).createLayoutWithRobots());


    return 0;
}