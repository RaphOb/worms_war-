//
// Created by lafay on 08/03/2020.
//

#ifndef LITTLEBIGGAME_PATHFINDING_HH
#define LITTLEBIGGAME_PATHFINDING_HH

#include "../Direction.hh"
#include "Node.hh"
#include "../Worm.hh"

class Map;
class Character;

class Pathfinding {
private:
    Map* m_map;
    Worm *m_target;
public:
    Pathfinding();
    Pathfinding(Map *context, Worm *target);
    Map *getMap();
    void setMap(Map*);
    void setTarget(Worm*);
    std::vector<Direction> getDirection(Node *origin);
    int getNodeWithLowestFCost(std::vector<const Node*>);
    std::vector<Node*> getNeighbourNodes(Node*);
    int awayFromOrigin(Node *);
};

#endif //LITTLEBIGGAME_PATHFINDING_HH
