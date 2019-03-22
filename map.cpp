#include "includes.h"
#include "map.h"

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

void Map::createLayoutWithRobots(){
  vector<vector<char>> ret = layout;
  for(unsigned int i = 0; i < robots.size(); i++){
    Robot temp = robots[i];
    ret[temp.line_c][temp.col_c] = temp.icon;
  }
  layoutWithRobots = ret;
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

void Map::moveRobot(char robotChar, char dir){

}

