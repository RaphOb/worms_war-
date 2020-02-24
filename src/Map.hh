//
// Created by geoff on 21/02/2020.
//

#ifndef LITTLEBIGGAME_MAP_HH
#define LITTLEBIGGAME_MAP_HH


#include <vector>
#include "Platform.hh"

class Map {
public:
    Map();
    void initMap();
    void addPlatform(Platform*  p);
    std::vector<Platform*> getPlatforms();
private:
    std::vector<Platform*> platforms;
};


#endif //LITTLEBIGGAME_MAP_HH
