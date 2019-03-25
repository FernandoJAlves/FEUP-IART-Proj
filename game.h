#ifndef GAME_H
#define GAME_H

#include "includes.h"
#include "menus.h"
#include "map.h"
#include "robot.h"
#include <vector>
using namespace std;

class Game {
 
    public:
        typedef struct {
            vector<Robot> robots;
            int depth;
        } Node;

        Game(){};
        Game(int gamemode, int searchMethod);

        bool isGameOver = false;
        int level = 0;

        void readDataFromFiles();

        void soloMode();
        void botMode(int searchMethod);

        int interpretInputRobot(char robot); //devolve o Index do robot no array
        int interpretInputDir(char dir); //devolve a dir a mover
  

};


#endif