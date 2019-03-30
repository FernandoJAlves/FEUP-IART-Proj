#ifndef GAME_H
#define GAME_H

#include "includes.h"
#include "menus.h"
#include "map.h"
#include "robot.h"
#include <vector>
using namespace std;

typedef struct
{
    vector<Robot> robots;
    int depth = 0;
    int heuristic = 0;
    int expansions = 0;
    vector<pair<int, int>> moveSeq = {};
} Node;

class Game
{

  public:
    Game(){};
    Game(int gamemode, int searchMethod, int level);

    bool isGameOver = false;
    int level = 0;

    void readDataFromFiles();

    void soloMode();
    void botMode(int searchMethod);

    int interpretInputRobot(char robot); //devolve o Index do robot no array
    int interpretInputDir(char dir);     //devolve a dir a mover
    void setLevel(int level);
};

Node switchAlgorithm(int n, Node start, Map currMap);
Node alg_dfs(Node startN, Map currMap);
Node alg_bfs(Node startN, Map currMap);
Node alg_Astar(Node startN, Map currMap);
Node alg_greedy(Node startN, Map currMap);
Node alg_progDeep(Node startN, Map currMap);
Node alg_uniCost(Node startN, Map currMap);
vector<pair<int,int>> robotToPositions(vector<Robot> r);



#endif