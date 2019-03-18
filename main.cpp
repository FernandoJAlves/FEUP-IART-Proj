#include "includes.h"
#include "menus.h"
#include "map.h"
#include "robot.h"

vector<Map> maps;
int global_c = 123;

int main()
{

    //read maps from file

    //mainMenu();

    //TESTING
    vector<vector<char>> v = {{'1', '1', '1', '1', '1'},
                              {'1', '0', '1', 'A', '1'},    
                              {'1', '0', '1', '0', '1'}, 
                              {'1', '0', '0', '0', '1'}, 
                              {'1', '1', '1', '1', '1'}};

    Map m;
    m.setLayout(v);
    Robot r;
    r.line_c = 1;
    r.col_c = 1;
    r.icon = 'a';
    m.robots.push_back(r);

    maps.push_back(m);

    
    maps.at(0).displayWithRobots(maps.at(0).createLayoutWithRobots());


    return 0;
}