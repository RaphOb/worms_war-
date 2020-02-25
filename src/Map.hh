//
// Created by geoff on 21/02/2020.
//

#ifndef LITTLEBIGGAME_MAP_HH
#define LITTLEBIGGAME_MAP_HH


#include <vector>
#include "Platform.hh"
#include "Constant.hh"

class Map {
public:
    Map();
    void initMap();
    void addPlatform(Platform*  p);
    std::vector<Platform*> getPlatforms();
    void initGrid();
    void displayGrid();

private:
    std::vector<Platform*> platforms;
    int** m_grid;
    int m_rows;
    int m_cols;
};


#endif //LITTLEBIGGAME_MAP_HH
