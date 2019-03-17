#include "includes.h"
#include "menus.h"
#include "map.h"

int main() 
{
    
    //mainMenu();




    //TESTING
    vector<vector<int>> v = {{1,1,1},{1,0,1},{1,1,1}};

    Map m;
    m.setLayout(v);
    m.displayLayout();

    return 0;
}