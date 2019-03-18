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
  int n_finalPos;
  vector<pair<int,int>> final_pos;
  

public:
  vector<Robot> robots;
  vector<vector<char>> getLayout() { return layout; }
  void setLayout(vector<vector<char>> l);
  void displayLayout();
  void printCell(char c);
  vector<vector<char>> createLayoutWithRobots();
  void displayWithRobots(vector<vector<char>> l);
};

void Map::setLayout(vector<vector<char>> l)
{
  layout = l;
}

void Map::displayLayout()
{
  for (unsigned int l = 0; l < layout.size(); l++)
  {
    for (unsigned int c = 0; c < layout[0].size(); c++)
    {
      printCell(layout[l][c]);
    }
    cout << '\n';
  }
}

void Map::printCell(char c)
{
  switch (c)
  {
  case '0':
    cout << ' ';
    break;
  case '1':
    cout << 'X';
    break;

  default:
    cout << c;
    break;
  }
}

vector<vector<char>> Map::createLayoutWithRobots(){
  vector<vector<char>> ret = layout;
  for(unsigned int i = 0; i < robots.size(); i++){
    Robot temp = robots[i];
    ret[temp.line_c][temp.col_c] = temp.icon;
  }
  return ret;
}

void Map::displayWithRobots(vector<vector<char>> v)
{
  for (unsigned int l = 0; l < v.size(); l++)
  {
    for (unsigned int c = 0; c < v[0].size(); c++)
    {
      cout << ' ';
      printCell(v[l][c]);
    }
    cout << '\n';
  }
}


#endif

