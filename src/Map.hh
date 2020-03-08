//
// Created by geoff on 21/02/2020.
//

#ifndef LITTLEBIGGAME_MAP_HH
#define LITTLEBIGGAME_MAP_HH


#include <vector>
#include "Constant.hh"
#include "Platform.hh"
#include "PathFinding/Node.hh"
#include "PathFinding/Pathfinding.hh"
#include "Monster/MonsterFactory.hh"

class Map {
public:
    Map();
    void initMap();
    void addPlatform(Platform* p);
    std::vector<Platform*> getPlatforms();
    void initGrid();
    void displayGrid();
    Node& getNodeByPos(int y, int x);
    void setPathfinding(Pathfinding *);

private:
    std::vector<Platform*> platforms;
    int** m_grid;
    std::vector<Node> m_nodeGrid;
    int m_rows;
    int m_cols;
    MonsterFactory m_monsterFactory;
};


#endif //LITTLEBIGGAME_MAP_HH
