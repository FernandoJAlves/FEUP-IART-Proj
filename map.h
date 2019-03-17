#include <vector>
using namespace std;

class Map
{
  int n_cols, n_lines;
  vector<vector<char>> layout;

public:
  vector<vector<char>> getLayout() { return layout; }
  void setLayout(vector<vector<char>> l);
  void displayLayout();
  void printCell(char c);
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
      //check if any robot is in that cell, else do printCell
      printCell(layout[l][c]);
    }
    cout << '\n';
  }
}

void Map::printCell(char c)
{
  switch (c)
  {
  case 0:
    cout << ' ';
    break;

  default:
    cout << c;
    break;
  }
}