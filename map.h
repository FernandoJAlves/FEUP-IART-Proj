#include <vector>
using namespace std;

class Map {
    int n_cols, n_lines;
    vector<vector<int>> layout;
  public:
    vector<vector<int>> getLayout(){return layout;}
    void setLayout(vector<vector<int>> l);
};

void Map::setLayout(vector<vector<int>> l){
    layout = l;
}


