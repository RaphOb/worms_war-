//
// Created by lafay on 08/03/2020.
//

#ifndef LITTLEBIGGAME_PATHFINDING_HH
#define LITTLEBIGGAME_PATHFINDING_HH

class Map;
class Character;

class Pathfinding {
private:
    Map *m_map;
    Character *m_target;
public:
    Pathfinding(Map *context, Character *target);
};

#endif //LITTLEBIGGAME_PATHFINDING_HH
