#include "includes.h"
#include "map.h"
#include "robot.h"


void Map::setColsLines(int c,int l)
{
  n_cols = c;
  n_lines = l;
}

void Map::addInitPos(int c,int l)
{
  pair<int,int> p = make_pair(c,l);
  init_pos.push_back(p);
}

void Map::addFinalPos(int c,int l)
{
  pair<int,int> p = make_pair(c,l);
  final_pos.push_back(p);
  n_finalPos++;
}

void Map::clearPosVectors()
{
  init_pos.clear();
  final_pos.clear();
  n_finalPos = 0;
}

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

void Map::createLayoutWithRobots()
{
  vector<vector<char>> ret = layout;
  for (unsigned int i = 0; i < robots.size(); i++)
  {
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

void Map::moveRobot(int robot, int dir)
{

  Robot r = robots.at(robot);
  char c;
  int i = 0;

  switch (dir)
  {
  case 0:
  {
    //up
    do
    {
      i--;
      c = layoutWithRobots[r.line_c + i][r.col_c];
    } while (!(c >= 'a' && c <= 'z') && c != '1');
    robots.at(robot).line_c += (i + 1);
    break;
  }
  case 1:
  {
    //right
    do
    {
      i++;
      c = layoutWithRobots[r.line_c][r.col_c + i];
    } while (!(c >= 'a' && c <= 'z') && c != '1');
    robots.at(robot).col_c += (i - 1);
    break;
  }
  case 2:
  {
    //down
    do
    {
      i++;
      c = layoutWithRobots[r.line_c + i][r.col_c];
    } while (!(c >= 'a' && c <= 'z') && c != '1');
    robots.at(robot).line_c += (i - 1);
    break;
  }
  case 3:
  {
    //right
    do
    {
      i--;
      c = layoutWithRobots[r.line_c][r.col_c + i];
    } while (!(c >= 'a' && c <= 'z') && c != '1');
    robots.at(robot).col_c += (i + 1);
    break;
  }
  default:
    cout << "Error moving robot\n";
    break;
  }
}

bool Map::checkGameOver()
{
  bool gameover = true;
  for (u_int i = 0; i < robots.size(); i++)
  {
    Robot r = robots.at(i);
    if (!r.is_helper)
    {
      if (r.line_c != r.final_line)
        gameover = false;
      if (r.col_c != r.final_col)
        gameover = false;
    }
  }
  return gameover;
}
