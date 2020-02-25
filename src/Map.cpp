//
// Created by geoff on 21/02/2020.
//

#include <cmath>
#include "Map.hh"
#include "Constant.hh"

void Map::initMap() {
    platforms.reserve(Constant::NB_PLATFORMS);
    platforms.emplace_back(new Platform(sf::Vector2f(Constant::VIEW_WIDTH, 50.f), sf::Vector2f(Constant::VIEW_WIDTH/2, 900.f), false, true));
    platforms.emplace_back(new Platform(Constant::PLATFORM_SIZE, sf::Vector2f(Constant::HALF_SIZE_PLATFORM, 225.f), false, false));
    /*platforms.emplace_back(new Platform(Constant::PLATFORM_SIZE, sf::Vector2f(Constant::VIEW_WIDTH - Constant::HALF_SIZE_PLATFORM, 200.f), true, false));
    platforms.emplace_back(new Platform(Constant::PLATFORM_SIZE, sf::Vector2f(450.f, 300.f), false, false));
    platforms.emplace_back(new Platform(Constant::PLATFORM_SIZE, sf::Vector2f(Constant::VIEW_WIDTH - 450.f, 300.f), false, false));
    platforms.emplace_back(new Platform(Constant::PLATFORM_SIZE, sf::Vector2f(Constant::HALF_SIZE_PLATFORM,  400.f), true, false));
    platforms.emplace_back(new Platform(Constant::PLATFORM_SIZE, sf::Vector2f(Constant::VIEW_WIDTH - Constant::HALF_SIZE_PLATFORM, 400.f), false, false));

    platforms.emplace_back(new Platform(Constant::PLATFORM_SIZE, sf::Vector2f(Constant::VIEW_WIDTH / 2, 500.f), true,false));

    platforms.emplace_back(new Platform(Constant::PLATFORM_SIZE, sf::Vector2f(Constant::HALF_SIZE_PLATFORM, 600.f), false, false));
    platforms.emplace_back(new Platform(Constant::PLATFORM_SIZE, sf::Vector2f(Constant::VIEW_WIDTH - Constant::HALF_SIZE_PLATFORM, 600.f), false, false));
    platforms.emplace_back(new Platform(Constant::PLATFORM_SIZE, sf::Vector2f(450.f, 700.f), true, false));
    platforms.emplace_back(new Platform(Constant::PLATFORM_SIZE, sf::Vector2f(Constant::VIEW_WIDTH - 450.f, 700.f), false, false));
    platforms.emplace_back(new Platform(Constant::PLATFORM_SIZE, sf::Vector2f(Constant::HALF_SIZE_PLATFORM, 800.f), true, false));
    platforms.emplace_back(new Platform(Constant::PLATFORM_SIZE, sf::Vector2f(Constant::VIEW_WIDTH - Constant::HALF_SIZE_PLATFORM, 800.f), false, false));
*/
    initGrid();
    displayGrid();
}

void Map::addPlatform(Platform* p) {
    if (p) {
        platforms.push_back(p);
    }
}

std::vector<Platform*> Map::getPlatforms() {
    return platforms;
}

Map::Map() {
}

void Map::initGrid() {

    sf::Vector2f size = Constant::SCREEN_DIMENSIONS/Constant::BLOCK_SIZE;
    m_rows = (int)size.y;
    m_cols = (int)size.x;

    // Init du tableau de la grid
    m_grid = new int*[m_rows];
    for(int i = 0; i < m_rows; ++i) {
        m_grid[i] = new int[m_cols];
    }

    // On init toutes les cases de la grid à 0 (à contrario de 1 si c'est un mur)
    for (int y=0 ; y<m_rows ; y++) {
        for (int x=0 ; x<m_cols ; x++) {
            m_grid[y][x] = 0;
        }
    }

    // On determine pour chaque plateformes les cases correspondantes sur la grid qui doivent être considérées comme des murs
    for (Platform* platform : platforms) {
        std::vector<int> targetY;
        std::vector<int> targetX;
        sf::Vector2f posToTest = platform->getPos();
        posToTest.x -= platform->getSize().x/2;
        posToTest.y -= platform->getSize().y/2;
        posToTest /= Constant::BLOCK_SIZE;

        // Determination pour les x (la largeur)
        for (int h=(int)floor(posToTest.y) ; h<(int)ceil(posToTest.y + ceil(platform->getSize().y/Constant::BLOCK_SIZE)) ; h++) {
            if (h<m_rows) {
                targetY.push_back(h);
            }
        }

        // Determination pour les y (la hauteur)
        for (int l=(int)floor(posToTest.x) ; l<(int)ceil(posToTest.x + ceil(platform->getSize().x/Constant::BLOCK_SIZE)) ; l++) {
            if (l<m_cols) {
                targetX.push_back(l);
            }
        }

        // On place les murs sur les x et y target plus tot
        for (int y : targetY) {
            for (int x : targetX) {
                m_grid[y][x] = 1;
            }
        }
    }
}

/**
 * Display perfect pos : pos who fit with the grid (this is because of the setOrigin in Platform)
 * example : x:0 in setOrigin will become x:x+platform.getSize().x/2
 * Fitting with the grid will help the pathfinding
 *
 * Display grid with plateform representation
 */
void Map::displayGrid() {
    cout << "perfect pos are :" << endl;
    for (int y=0 ; y<m_rows ; y++) {
        cout << "y=>" << ((int)Constant::BLOCK_SIZE/2)+(int)Constant::BLOCK_SIZE*y << " / ";
    }
    cout << endl;
    for (int x=0 ; x<m_cols ; x++) {
        cout << " x=>" << ((int)Constant::BLOCK_SIZE/2)+(int)Constant::BLOCK_SIZE*x << " / ";
    }
    cout << endl;

    for (int y=0 ; y<m_rows ; y++) {
        for (int x=0 ; x<m_cols ; x++) {
            cout << m_grid[y][x];
        }
        cout << endl;
    }
}