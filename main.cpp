#include "includes.h"
#include "menus.h"
#include "map.h"

int main() 
{
    
    mainMenu();




    //TESTING
    vector<vector<int>> v = {{0,1},{2,3}};

    for(int i = 0; i < v[0].size(); i++){
        cout << v[0][i] << '\n';
    }

    Map m;
    m.setLayout(v);

    vector<vector<int>> v2 = m.getLayout();

    for(int i = 0; i < v2[0].size(); i++){
        cout << v2[0][i] << '\n';
    }

    return 0;
}