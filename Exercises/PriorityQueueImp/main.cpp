#include <functional>
#include <queue>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <utility> 
#include <iostream>
#include <unistd.h>
 
template<typename T> void print_queue(T q) {
    while(!q.empty()) {
        std::cout << q.top() << " ";
        q.pop();
    }
    std::cout << '\n';
}
 
int main() {
 
 /*
    // Using lambda to compare elements.
    auto cmp = [](int left, int right) { 
        return (left) < (right);
        };

    std::priority_queue<int, std::vector<int>, decltype(cmp)> q3(cmp);
 
    for(int n : {0,1,2,3,4,5,6,7,8,9})
        q3.push(n);

    std::priority_queue<int> q1;
 
    for(int n : {0,1,2,3,4,5,6,7,8,9})
        q1.push(n);
 
    sleep(1);

    print_queue(q3);
    print_queue(q1);
    */

   std::vector<std::pair<int, int>> v1 = {{1,2},{3,4},{5,6}};

   std::vector<std::pair<int, int>> v2 = v1;

   std::cout << v1.size() << "\n\n" << v2.size() << '\n';

   for(unsigned int i = 0; i < v1.size(); i++){
       std::cout << v1[i].first << "   " << v1[i].second << '\n';
   }
   std::cout << '\n';
    for(unsigned int i = 0; i < v2.size(); i++){
       std::cout << v2[i].first << "   " << v2[i].second << '\n';
   }
 
}