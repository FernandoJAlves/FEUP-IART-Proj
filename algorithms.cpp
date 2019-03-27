#include "includes.h"
#include "game.h"
#include "menus.h"
#include "map.h"
#include "robot.h"
#include <vector>
#include <cctype>
#include <unistd.h>
#include <functional>
#include <queue>

using namespace std;


// Template Print
template<typename T> void print_queue(T q) {
    while(!q.empty()) {
        cout << q.top().depth << " ";
        q.pop();
    }
    cout << '\n';
}


// Selects the Algorithm and returns the Node
Node switchAlgorithm(int n, Node start, Map currMap){
    
    /*
        SEARCH METHODS:
        1- DFS
        2- BFS
        3- Aprofundamento Progressivo
        4- Custo Uniforme
        5- Gulosa
        6- A*
        */

    switch (n)
    {
        case 1:
            return alg_dfs(start, currMap);
            break;
    
        default:
            break;
    }
    return start;
}


Node alg_dfs(Node startN, Map currMap){
    Node ret;

    // Using lambda to compare elements.
    auto cmp = [](Node left, Node right) { 
        return (left.depth) < (right.depth);
        };

    priority_queue<Node, vector<Node>, decltype(cmp)> p_queue(cmp);

    p_queue.push(startN);

/* WIP
    while(true){
        for(int i = 0; i < 4; i++){

        }


    }
    */


    print_queue(p_queue);

    return ret;
}


Node alg_bfs(Node startN, Map currMap){
    Node ret;

    return ret;
}


Node alg_Astar(Node startN, Map currMap){
    Node ret;

    return ret;
}


Node alg_greedy(Node startN, Map currMap){
    Node ret;

    return ret;
}


Node alg_progDeep(Node startN, Map currMap){
    Node ret;

    return ret;
}


Node alg_uniCost(Node startN, Map currMap){
    Node ret;

    return ret;
}