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
#include <set>

using namespace std;

// Template Print
template <typename T>
void print_queue(T q)
{
    while (!q.empty())
    {
        cout << q.top().depth << " ";
        q.pop();
    }
    cout << '\n';
}

// Selects the Algorithm and returns the Node
Node switchAlgorithm(int n, Node start, Map currMap)
{
    switch (n)
    {
    case 1:
        return alg_dfs(start, currMap);
    case 2:
        return alg_bfs(start, currMap);
    case 3:
        return alg_progDeep(start, currMap);
    case 4:
        return alg_uniCost(start, currMap);
    case 5:
        return alg_greedy(start, currMap);
    case 6:
        return alg_Astar(start, currMap);

    default:
        return start;
    }
}

Node alg_dfs(Node startN, Map currMap)
{
    Node ret;

    set<vector<pair<int, int>>> prevStates;
    pair<set<vector<pair<int, int>>>::iterator, bool> insertRet;

    // Using lambda to compare elements.
    auto cmp = [](Node left, Node right) {
        return (left.depth) < (right.depth);
    };

    priority_queue<Node, vector<Node>, decltype(cmp)> p_queue(cmp);

    p_queue.push(startN);
    prevStates.insert(robotToPositions(startN.robots));

    int n_expansions = 0;

    while (p_queue.size() > 0)
    {
        Node first = p_queue.top();
        p_queue.pop();

        //Para evitar percorrer infinitamente
        if (first.depth > MAX_DEPTH)
            continue;

        //itera pelos robots
        for (u_int r = 0; r < currMap.robots.size(); r++)
        {
            //itera pelas direções
            for (u_int d = 0; d < 4; d++)
            {
                currMap.robots = first.robots;
                currMap.createLayoutWithRobots();
                //Only expand useful moves
                if (currMap.moveRobot(r, d) != -1)
                {
                    n_expansions++;
                    Node toInsert;
                    toInsert.robots = currMap.robots;
                    toInsert.depth = first.depth + 1;
                    toInsert.moveSeq = first.moveSeq;
                    toInsert.moveSeq.push_back(make_pair(r, d));

                    //Check if gameover
                    if (currMap.checkGameOver())
                    {
                        toInsert.expansions = n_expansions;
                        return toInsert;
                    }

                    //Push to queue
                    else
                    {
                        insertRet = prevStates.insert(robotToPositions(toInsert.robots));
                        if (!insertRet.second) //Não foi inserido
                            continue;
                        else
                            p_queue.push(toInsert);
                    }
                }
            }
        }
    }

    //Se chegar aqui, quer dizer que ficou sem nós por expandir, logo não há solução

    ret.depth = -1; // Depth = -1 quer dizer que não encontrou solução

    return ret;
}

Node alg_bfs(Node startN, Map currMap)
{
    Node ret;

    set<vector<pair<int, int>>> prevStates;
    pair<set<vector<pair<int, int>>>::iterator, bool> insertRet;

    // Using lambda to compare elements.
    auto cmp = [](Node left, Node right) {
        if((left.depth) == (right.depth))
            return true;
        else return (left.depth) > (right.depth);
    };

    priority_queue<Node, vector<Node>, decltype(cmp)> p_queue(cmp);

    p_queue.push(startN);
    prevStates.insert(robotToPositions(startN.robots));

    int n_expansions = 0;

    while (p_queue.size() > 0)
    {
        Node first = p_queue.top();
        p_queue.pop();

        //Para evitar percorrer infinitamente
        if (first.depth > MAX_DEPTH)
            continue;

        //itera pelos robots
        for (u_int r = 0; r < currMap.robots.size(); r++)
        {
            //itera pelas direções
            for (u_int d = 0; d < 4; d++)
            {
                currMap.robots = first.robots;
                currMap.createLayoutWithRobots();
                //Only expand useful moves
                if (currMap.moveRobot(r, d) != -1)
                {
                    n_expansions++;
                    Node toInsert;
                    toInsert.robots = currMap.robots;
                    toInsert.depth = first.depth + 1;
                    toInsert.moveSeq = first.moveSeq;
                    toInsert.moveSeq.push_back(make_pair(r, d));

                    //Check if gameover
                    if (currMap.checkGameOver())
                    {
                        toInsert.expansions = n_expansions;
                        return toInsert;
                    }

                        //Push to queue
                    else
                    {
                        insertRet = prevStates.insert(robotToPositions(toInsert.robots));
                        if (!insertRet.second) //Não foi inserido
                            continue;
                        else
                            p_queue.push(toInsert);
                    }
                }
            }
        }
    }

    //Se chegar aqui, quer dizer que ficou sem nós por expandir, logo não há solução

    ret.depth = -1; // Depth = -1 quer dizer que não encontrou solução

    return ret;
}

Node alg_Astar(Node startN, Map currMap)
{
    Node ret;

    set<vector<pair<int, int>>> prevStates;
    pair<set<vector<pair<int, int>>>::iterator, bool> insertRet;

    // Using lambda to compare elements.
    auto cmp = [](Node left, Node right) {
        return (left.heuristic) < (right.heuristic);
    };

    priority_queue<Node, vector<Node>, decltype(cmp)> p_queue(cmp);

    p_queue.push(startN);
    prevStates.insert(robotToPositions(startN.robots));

    while (p_queue.size() > 0)
    {
        Node first = p_queue.top();
        p_queue.pop();

        //Para evitar percorrer infinitamente
        if (first.depth > MAX_DEPTH)
            continue;

        //itera pelos robots
        for (u_int r = 0; r < currMap.robots.size(); r++)
        {
            //itera pelas direções
            for (u_int d = 0; d < 4; d++)
            {
                currMap.robots = first.robots;
                currMap.createLayoutWithRobots();
                //Only expand useful moves
                if (currMap.moveRobot(r, d) != -1)
                {
                    Node toInsert;
                    toInsert.robots = currMap.robots;
                    toInsert.depth = first.depth + 1;
                    toInsert.moveSeq = first.moveSeq;
                    toInsert.moveSeq.push_back(make_pair(r, d));

                    //Check if gameover
                    if (currMap.checkGameOver())
                    {
                        return toInsert;
                    }

                    //Push to queue
                    else
                    {
                        insertRet = prevStates.insert(robotToPositions(toInsert.robots));
                        if (!insertRet.second) //Não foi inserido
                            continue;
                        else
                            p_queue.push(toInsert);
                    }
                }
            }
        }
    }

    //Se chegar aqui, quer dizer que ficou sem nós por expandir, logo não há solução

    ret.depth = -1; // Depth = -1 quer dizer que não encontrou solução

    return ret;
}

Node alg_greedy(Node startN, Map currMap)
{
    Node ret;

    //Se chegar aqui, quer dizer que ficou sem nós por expandir, logo não há solução
    ret.depth = -1; // Depth = -1 quer dizer que não encontrou solução
    return ret;
}

Node alg_progDeep(Node startN, Map currMap)
{
    Node ret;

    //Se chegar aqui, quer dizer que ficou sem nós por expandir, logo não há solução
    ret.depth = -1; // Depth = -1 quer dizer que não encontrou solução
    return ret;
}

Node alg_uniCost(Node startN, Map currMap)
{
    Node ret;

    //Se chegar aqui, quer dizer que ficou sem nós por expandir, logo não há solução
    ret.depth = -1; // Depth = -1 quer dizer que não encontrou solução
    return ret;
}

vector<pair<int, int>> robotToPositions(vector<Robot> r)
{
    vector<pair<int, int>> ret;
    for (u_int i = 0; i < r.size(); i++)
    {
        ret.push_back(make_pair(r.at(i).line_c, r.at(i).col_c));
    }
    return ret;
}

int calcHeuristic(vector<Robot> r){
    return 0;
}
