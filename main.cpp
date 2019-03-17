#include "includes.h"
#include "menus.h"
#include "map.h"

vector<vector<int>> maps;

int main() 
{
    
    //read maps from file

    //mainMenu();




    //TESTING
    vector<vector<char>> v = {{'1','1','1'},{'1','0','1'},{'1','1','1'}};

    Map m;
    m.setLayout(v);
    m.displayLayout();

    return 0;
}