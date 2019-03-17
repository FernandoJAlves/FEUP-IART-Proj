#include <iostream>
#include <vector>
using namespace std;

int f_function(vector<vector<int>> state, int d);
int h_function(vector<vector<int>> state);


int main() 
{
    vector<vector<int>> v = initialState();

    f_function(v, 0);

    return 0;
}

vector<vector<int>> initialState(){
    vector<vector<int>> v = {{1,2,3},{4,5,6},{7,8,0}};
    return v;
}

int f_function(vector<vector<int>> state, int d){
    int h = h_function(state);
    int ret = d + h;
    return ret;
}

int h_function(vector<vector<int>> state){
    return 0;
}
