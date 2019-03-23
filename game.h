#ifndef GAME_H
#define GAME_H

#include "includes.h"
#include "menus.h"
#include "map.h"
#include "robot.h"
#include <vector>
using namespace std;

class Game
{

 
public:
  Game(){};
  Game(int gamemode);

  bool isGameOver = false;
  int level = 0;

  void readDataFromFiles();

  void soloMode();
  void botMode();

  int interpretInputRobot(char robot); //devolve o Index do robot no array
  int interpretInputDir(char dir); //devolve a dir a mover
  

};


#endif