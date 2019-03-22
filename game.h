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

  vector<Map> maps;
  bool isGameOver = false;
  int level = 0;

  void soloMode();
  void botMode();
  

};


#endif