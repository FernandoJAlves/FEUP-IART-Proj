#include <functional>
#include <queue>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include <iostream>
#include <unistd.h>
#include <set>
#include <map>

using namespace std;

template <typename T>
void print_queue(T q)
{
    while (!q.empty())
    {
        std::cout << q.top() << " ";
        q.pop();
    }
    std::cout << '\n';
}

int main()
{

    /*
    // Using lambda to compare elements.
    auto cmp = [](int left, int right) { 
        return (left) < (right);
        };

    std::priority_queue<int, std::vector<int>, decltype(cmp)> q3(cmp);
 
    for(int n : {0,-5,2,3,-2,5,6,7,8,9})
        q3.push(n);

    print_queue(q3);
    */
/*
    std::priority_queue<int> q1;
 
    for(int n : {0,1,2,3,4,5,6,7,8,9})
        q1.push(n);
 
    sleep(1);

    print_queue(q3);
    print_queue(q1);
    */

    /*
    set<vector<pair<int, int>>> conjunto;
    vector<pair<int, int>> v0 = {{1, 2}, {3, 4}, {5, 6}};
    cout << v0[0].first << endl;
    conjunto.insert(v0);

    v0 = {{10, 20}, {30, 40}, {50, 60}};
    cout << v0[0].first << endl;
    conjunto.insert(v0);

    v0 = {{1, 2}, {3, 4}, {5, 6}};
    cout << v0[0].first << endl;
    conjunto.insert(v0);

    set<vector<pair<int, int>>>::iterator it;
    cout << "\nsize = " << conjunto.size() << "\n\n";
    for (it = conjunto.begin(); it != conjunto.end(); it++)
    {
        const vector<pair<int, int>> &i = (*it); // HERE we get the vector
        cout << i[0].first << endl;              // NOW we output the first item.
    }

*/

    map<vector<pair<int, int>>, int> map1;

    vector<pair<int, int>> v0 = {{1, 2}, {3, 4}, {5, 6}};
    vector<pair<int, int>> v1 = {{10, 20}, {30, 40}, {50, 60}};
    vector<pair<int, int>> v2 = {{1, 2}, {3, 4}, {5, 6}};

    pair<map<vector<pair<int, int>>, int>::iterator,bool> ret;

    ret = map1.insert(pair<vector<pair<int, int>>, int>(v0, 20));
    cout << v0[0].first << endl;
    cout << ret.second << endl << endl;

    ret = map1.insert(pair<vector<pair<int, int>>, int>(v1, 5));
    cout << v1[0].first << endl;
    cout << ret.second << endl << endl;

    ret = map1.insert(pair<vector<pair<int, int>>, int>(v2, 10));
    cout << v2[0].first << endl;
    cout << ret.second << endl << endl;

    cout << map1.size() << endl;

}