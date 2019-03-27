#include <functional>
#include <queue>
#include <vector>
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
 
}