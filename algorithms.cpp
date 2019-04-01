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
#include <map>
#include "limits.h"

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
Node switchAlgorithm(int n, Node start, Map currMap, int heur)
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
        return alg_greedy(start, currMap, heur);
    case 6:
        return alg_Astar(start, currMap, heur);

    default:
        return start;
    }
}

Node alg_dfs(Node startN, Map currMap)
{
    Node ret;

    map<vector<pair<int, int>>, int> prevStates;
    pair<map<vector<pair<int, int>>, int>::iterator, bool> insertRet;

    // Using lambda to compare elements.
    auto cmp = [](Node left, Node right) {
        return (left.depth) < (right.depth);
    };

    priority_queue<Node, vector<Node>, decltype(cmp)> p_queue(cmp);

    p_queue.push(startN);
    prevStates.insert(pair<vector<pair<int, int>>, int>(robotToPositions(startN.robots), startN.depth));

    int n_expansions = 0;

    while (p_queue.size() > 0)
    {
        Node first = p_queue.top();
        p_queue.pop();

        //Para evitar percorrer infinitamente
        if (first.depth > MAX_DEPTH)
            continue;

        //TODO: Apenas no DFS, os robots e direções passar a random para mitigar ciclos & remover max_depth depois(?)

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
                        insertRet = prevStates.insert(pair<vector<pair<int, int>>, int>(robotToPositions(toInsert.robots), toInsert.depth));
                        if (!insertRet.second) //Já foi percorrido
                        {
                            if (toInsert.depth < insertRet.first->second) //Chegou com profundidade menor portanto vai para a p_queue
                            {
                                insertRet.first->second = toInsert.depth;
                                p_queue.push(toInsert);
                            }
                            else // Ignorar node porque já passou lá com profundidade menor
                            {
                                continue;
                            }
                        }
                        else //Ainda não vou percorrido
                            p_queue.push(toInsert);
                    }
                }
            }
        }
    }

    //Se chegar aqui, quer dizer que ficou sem nós por expandir, logo não há solução

    ret.depth = -1; // Depth = -1 quer dizer que não encontrou solução
    ret.expansions = n_expansions;
    return ret;
}

Node alg_bfs(Node startN, Map currMap)
{
    Node ret;

    set<vector<pair<int, int>>> prevStates;
    pair<set<vector<pair<int, int>>>::iterator, bool> insertRet;

    // Using lambda to compare elements.
    auto cmp = [](Node left, Node right) {
        if ((left.depth) == (right.depth))
            return true;
        else
            return (left.depth) > (right.depth);
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
    ret.expansions = n_expansions;
    return ret;
}

Node alg_Astar(Node startN, Map currMap, int heur)
{
    Node ret;
    ret.depth = -1; //In case there is no solution found
    //TODO: Geral, testar se o primeiro nó é solução

    map<vector<pair<int, int>>, int> prevStates;
    pair<map<vector<pair<int, int>>, int>::iterator, bool> insertRet;

    // Using lambda to compare elements.
    auto cmp = [](Node left, Node right) {
        return (left.heuristic + left.depth) > (right.heuristic + right.depth);
    };

    priority_queue<Node, vector<Node>, decltype(cmp)> p_queue(cmp);

    currMap.robots = startN.robots;
    currMap.createLayoutWithRobots();
    startN.heuristic = calcHeuristic(heur, startN.robots, currMap); //TODO: Do heuristic selector
    
    p_queue.push(startN);
    prevStates.insert(pair<vector<pair<int, int>>, int>(robotToPositions(startN.robots), startN.depth));

    int n_expansions = 0;
    int minDepth = INT_MAX;

    while (p_queue.size() > 0)
    {
        Node first = p_queue.top();
        p_queue.pop();

        //Para evitar percorrer infinitamente //TODO: Tirar e testar se continua a dar
        if (first.depth > MAX_DEPTH)
            continue;

        if (first.depth + first.heuristic > minDepth)
        { //Encontrou a melhor solução
            ret.expansions = n_expansions;
            return ret;
        }

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
                    //sleep(1);
                    n_expansions++;
                    Node toInsert;
                    toInsert.robots = currMap.robots;
                    toInsert.depth = first.depth + 1;
                    toInsert.heuristic = calcHeuristic(heur, currMap.robots, currMap);
                    toInsert.moveSeq = first.moveSeq;
                    toInsert.moveSeq.push_back(make_pair(r, d));

                    //Check if gameover
                    if (currMap.checkGameOver())
                    {
                        if (toInsert.depth < minDepth) //Nova melhor solução
                        {
                            //cout << "Found a solution!\n";
                            minDepth = toInsert.depth;
                            ret = toInsert;
                            //cout << "Line: " << ret.robots.at(0).line_c << "   Col: " << ret.robots.at(0).col_c << "   Depth: " << ret.depth << "\n";
                        }
                    }

                    //Push to queue
                    else
                    {
                        insertRet = prevStates.insert(pair<vector<pair<int, int>>, int>(robotToPositions(toInsert.robots), toInsert.depth));
                        if (!insertRet.second) //Já foi percorrido
                        {
                            if (toInsert.depth < insertRet.first->second) //Chegou com profundidade menor portanto vai para a p_queue
                            {
                                insertRet.first->second = toInsert.depth;
                                p_queue.push(toInsert);
                            }
                            else // Ignorar node porque já passou lá com profundidade menor
                            {
                                continue;
                            }
                        }
                        else //Ainda não foi percorrido
                            p_queue.push(toInsert);
                    }
                }
            }
        }
    }

    //Encontrou solução na ultima iteração
    if (ret.depth != -1)
    {
        ret.expansions = n_expansions;
        return ret;
    }

    //Se chegar aqui, quer dizer que ficou sem nós por expandir, logo não há solução
    ret.depth = -1; // Depth = -1 quer dizer que não encontrou solução
    ret.expansions = n_expansions;
    return ret;
}

Node alg_greedy(Node startN, Map currMap, int heur)
{
    Node ret;
    ret.depth = -1; //In case there is no solution found

    map<vector<pair<int, int>>, int> prevStates;
    pair<map<vector<pair<int, int>>, int>::iterator, bool> insertRet;

    // Using lambda to compare elements.
    auto cmp = [](Node left, Node right) {
        return left.heuristic > right.heuristic;
    };

    priority_queue<Node, vector<Node>, decltype(cmp)> p_queue(cmp);

    currMap.robots = startN.robots;
    currMap.createLayoutWithRobots();
    startN.heuristic = calcHeuristic(heur, startN.robots, currMap); //TODO: Do heuristic selector
    
    p_queue.push(startN);
    prevStates.insert(pair<vector<pair<int, int>>, int>(robotToPositions(startN.robots), startN.depth));

    int n_expansions = 0;

    while (p_queue.size() > 0)
    {
        Node first = p_queue.top();
        p_queue.pop();

        //Para evitar percorrer infinitamente //TODO: Tirar e testar se continua a dar
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
                    toInsert.heuristic = calcHeuristic(heur, currMap.robots, currMap);
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
                        insertRet = prevStates.insert(pair<vector<pair<int, int>>, int>(robotToPositions(toInsert.robots), toInsert.depth));
                        if (!insertRet.second) //Já foi percorrido
                        {
                            if (toInsert.depth < insertRet.first->second) //Chegou com profundidade menor portanto vai para a p_queue
                            {
                                insertRet.first->second = toInsert.depth;
                                p_queue.push(toInsert);
                            }
                            else // Ignorar node porque já passou lá com profundidade menor
                            {
                                continue;
                            }
                        }
                        else //Ainda não foi percorrido
                            p_queue.push(toInsert);
                    }
                }
            }
        }
    }

    //Se chegar aqui, quer dizer que ficou sem nós por expandir, logo não há solução
    ret.depth = -1; // Depth = -1 quer dizer que não encontrou solução
    ret.expansions = n_expansions;
    return ret;
}

Node alg_progDeep(Node startN, Map currMap)
{
    Node ret;
    int tempMaxDepth = 0;
    int n_expansions = 0;

    map<vector<pair<int, int>>, int> prevStates;
    pair<map<vector<pair<int, int>>, int>::iterator, bool> insertRet;

    // Using lambda to compare elements.
    auto cmp = [](Node left, Node right) {
        return (left.depth) < (right.depth);
    };

    priority_queue<Node, vector<Node>, decltype(cmp)> p_queue(cmp);

    p_queue.push(startN);
    prevStates.insert(pair<vector<pair<int, int>>, int>(robotToPositions(startN.robots), startN.depth));

    while (p_queue.size() > 0)
    {

        Node first = p_queue.top();

        if (first.depth == tempMaxDepth - 1)
        {

            tempMaxDepth++;
            prevStates = map<vector<pair<int, int>>, int>();

            while (!p_queue.empty())
            {
                p_queue.pop();
            }

            p_queue.push(startN);
            first = p_queue.top();
        }

        p_queue.pop();

        //Para evitar percorrer infinitamente
        if (first.depth > MAX_DEPTH)
            continue;

        //TODO: Apenas no DFS, os robots e direções passar a random para mitigar ciclos & remover max_depth depois(?)

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
                        insertRet = prevStates.insert(pair<vector<pair<int, int>>, int>(robotToPositions(toInsert.robots), toInsert.depth));

                        if (!insertRet.second) //Já foi percorrido
                        {
                            if (toInsert.depth < insertRet.first->second) //Chegou com profundidade menor portanto vai para a p_queue
                            {
                                insertRet.first->second = toInsert.depth;
                                p_queue.push(toInsert);
                            }
                            else
                                continue; // Ignorar node porque já passou lá com profundidade menor
                        }
                        else
                            p_queue.push(toInsert); //Ainda não vou percorrido
                    }
                }
            }
        }
    }

    //Se chegar aqui, quer dizer que ficou sem nós por expandir, logo não há solução
    ret.depth = -1; // Depth = -1 quer dizer que não encontrou solução
    ret.expansions = n_expansions;
    return ret;
}

Node alg_uniCost(Node startN, Map currMap)
{
    /*Como a nossa funcao g(n)=Depth(n) prq o custo da solucao é == ao nr. de jogadas == depth do no final, entao
      Pesquisa de Custo Uniforme é igual a Pesquisa Primeiro em Largura */
    return alg_bfs(startN, currMap);
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

// HEURISTICS

int calcHeuristic(int option, vector<Robot> &r, Map &currMap)
{
    switch (option)
    {
    case 1: //default h() = 0
        return 0;
    case 2: // lines/cols alligned
        return heurLineCol(r, currMap);
    case 3:
        return heurLineCol2(r, currMap);
    case 4:
        return heurAreaDens(r, currMap);

    default:
        break;
    }

    return 0;
}

int heurLineCol(vector<Robot> &r, Map &currMap)
{
    int ret = 0;
    for (u_int i = 0; i < r.size(); i++)
    {
        if (!r.at(i).is_helper)
        {
            if (r.at(i).line_c != r.at(i).final_line)
                ret++;
            if (r.at(i).col_c != r.at(i).final_col)
                ret++;
        }
    }
    return ret;
}

int heurLineCol2(vector<Robot> &r, Map &currMap)
{
    //cout << "Size: " << currMap.layoutWithRobots.size() << '\n';
    int ret = 0;
    for (u_int i = 0; i < r.size(); i++)
    {
        if (!r.at(i).is_helper)
        {
            //cout << "\nLine_c: " << r.at(i).line_c << "\tFinal Line: " << r.at(i).final_line << '\n';
            //cout << "Col_c: " << r.at(i).col_c << "\tFinal Col: " << r.at(i).final_col << '\n';
            if (r.at(i).line_c != r.at(i).final_line) //Lines not aligned
            {
                //cout << "Col no aligned\n";
                ret++;
            }
            else //Lines aligned
            {
                int increment = 1;
                if (r.at(i).col_c > r.at(i).final_col) //Col is to the left
                    increment = -1;
                int auxLine = r.at(i).line_c;
                int auxCol = r.at(i).col_c;
                while (auxCol != r.at(i).final_col)
                {
                    auxCol += increment;
                    //cout << "Char: " << currMap.layoutWithRobots[auxLine][auxCol] << endl;
                    if (currMap.layoutWithRobots[auxLine][auxCol] == '1') //If it found an obstacle
                    {
                        ret += 3;
                        break;
                    }
                }
            }
            if (r.at(i).col_c != r.at(i).final_col) //Cols not aligned
                ret++;
            else //Cols aligned
            {
                int increment = 1;
                if (r.at(i).line_c > r.at(i).final_line) //Line is above
                    increment = -1;
                int auxLine = r.at(i).line_c;
                int auxCol = r.at(i).col_c;
                //cout << "AuxLine: " << auxLine << "\tAuxCol: " << auxCol << '\n';
                while (auxLine != r.at(i).final_line)
                {
                    auxLine += increment;
                    //cout << "Char: " << currMap.layoutWithRobots[auxLine][auxCol] << endl;
                    if (currMap.layoutWithRobots[auxLine][auxCol] == '1') //If it found an obstacle
                    {
                        ret += 3;
                        break;
                    }
                }
            }
        }
    }
    return ret;
}

int heurAreaDens(vector<Robot> &r, Map &currMap)
{
    int ret = 0;
    for (u_int i = 0; i < r.size(); i++)
    {
        if (!r.at(i).is_helper)
        {
            int minCol, maxCol, minLine, maxLine;
            if (r.at(i).col_c > r.at(i).final_col)
            {
                minCol = r.at(i).final_col;
                maxCol = r.at(i).col_c;
            }
            else
            {
                maxCol = r.at(i).final_col;
                minCol = r.at(i).col_c;
            }
            if (r.at(i).line_c > r.at(i).final_line)
            {
                minLine = r.at(i).final_line;
                maxLine = r.at(i).line_c;
            }
            else
            {
                maxLine = r.at(i).final_line;
                minLine = r.at(i).line_c;
            }

            int totalArea = (maxCol - minCol + 1) * (maxLine - minLine + 1); //total area to be analized
            int obsCount = 0;                                                //Obstacle count
            for (int lAux = minLine; lAux <= maxLine; lAux++)
            {
                for (int cAux = minCol; cAux <= maxCol; cAux++)
                {
                    if (currMap.layoutWithRobots[lAux][cAux] == '1') //Obstacle
                        obsCount++;
                }
            }

            double areaFilled = (double)obsCount / totalArea;
            if(areaFilled > 0.3)  //TODO: Change so it is no so pessimist
                ret += 10;
            else if(areaFilled > 0.1)
                ret += 1;
        }
    }
    return ret;
}
