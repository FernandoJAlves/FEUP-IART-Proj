#include <vector>
using namespace std;

class Map
{
  int n_cols, n_lines;
  vector<vector<int>> layout;

public:
  vector<vector<int>> getLayout() { return layout; }
  void setLayout(vector<vector<int>> l);
  void displayLayout();
  void translateInt(int);
};

void Map::setLayout(vector<vector<int>> l)
{
  layout = l;
}

void Map::displayLayout()
{
  for (unsigned int l = 0; l < layout.size(); l++)
  {
    for (unsigned int c = 0; c < layout[0].size(); c++)
    {
      translateInt(layout[l][c]);
    }
    cout << '\n';
  }
}

void Map::translateInt(int n)
{
  switch (n)
  {
  case 0:
    cout << ' ';
    break;

  case 1:
    cout << 'X';
    break;

  default:
    cout << n;
    break;
  }
}