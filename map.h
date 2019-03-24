#ifndef MAP_H
#define MAP_H


#include <vector>
#include "robot.h"
using namespace std;

class Map
{
  int n_cols, n_lines;
  vector<vector<char>> layout;
  vector<pair<int,int>> init_pos;
  int n_finalPos = 0;
  vector<pair<int,int>> final_pos;
  

public:
  vector<vector<char>> layoutWithRobots;
  vector<Robot> robots;
  int getCols() const { return n_cols;}
  int getLines() const { return n_lines;}
  void setColsLines(int c,int l);
  void addInitPos(int c,int l);
  void addFinalPos(int c,int l);
  void clearPosVectors();
  vector<vector<char>> getLayout() const { return layout; }
  void setLayout(vector<vector<char>> l);
  void displayLayout();
  void printCell(char c);
  void createLayoutWithRobots();
  void displayWithRobots(vector<vector<char>> l);
  void moveRobot(int robot, int dir);
  bool checkGameOver();
};




#endif

