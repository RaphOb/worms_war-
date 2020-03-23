//
// Created by geoff on 21/02/2020.
//

#include <cmath>
#include "Map.hh"
#include "Constant.hh"

void Map::initMap() {
    platforms.reserve(Constant::NB_PLATFORMS);
    // Floor
    platforms.emplace_back(new Platform(sf::Vector2f(Constant::VIEW_WIDTH, 30.f), sf::Vector2f(Constant::VIEW_WIDTH / 2.f, 885.f), nullptr, true));
    // Roof
    platforms.emplace_back(new Platform(sf::Vector2f(Constant::VIEW_WIDTH, 30.f), sf::Vector2f(Constant::VIEW_WIDTH / 2.f, 15.f), nullptr, true));


    // Platforms
    //platforms.emplace_back(new Platform(Constant::PLATFORM_SIZE, sf::Vector2f(Constant::HALF_SIZE_PLATFORM, 200.f), nullptr, false));
    //platforms.emplace_back(new Platform(Constant::PLATFORM_SIZE, sf::Vector2f(Constant::VIEW_WIDTH - Constant::HALF_SIZE_PLATFORM, 200.f), &m_monsterFactory, false));
    //platforms.emplace_back(new Platform(Constant::PLATFORM_SIZE, sf::Vector2f(450.f, 300.f), nullptr, false));
    //platforms.emplace_back(new Platform(Constant::PLATFORM_SIZE, sf::Vector2f(Constant::VIEW_WIDTH - 450.f, 300.f), nullptr, false));
    //platforms.emplace_back(new Platform(Constant::PLATFORM_SIZE, sf::Vector2f(Constant::HALF_SIZE_PLATFORM,  400.f), nullptr, false));
    //platforms.emplace_back(new Platform(Constant::PLATFORM_SIZE, sf::Vector2f(Constant::VIEW_WIDTH - Constant::HALF_SIZE_PLATFORM, 400.f), nullptr, false));
    platforms.emplace_back(new Platform(Constant::PLATFORM_SIZE, sf::Vector2f(Constant::VIEW_WIDTH / 2, 500.f), nullptr,false));
    //platforms.emplace_back(new Platform(Constant::PLATFORM_SIZE, sf::Vector2f(Constant::HALF_SIZE_PLATFORM, 600.f), nullptr, false));
    //platforms.emplace_back(new Platform(Constant::PLATFORM_SIZE, sf::Vector2f(Constant::VIEW_WIDTH - Constant::HALF_SIZE_PLATFORM, 600.f), nullptr, false));
    //platforms.emplace_back(new Platform(Constant::PLATFORM_SIZE, sf::Vector2f(450.f, 700.f), nullptr, false));
    //platforms.emplace_back(new Platform(Constant::PLATFORM_SIZE, sf::Vector2f(Constant::VIEW_WIDTH - 450.f, 700.f), nullptr, false));
    //platforms.emplace_back(new Platform(Constant::PLATFORM_SIZE, sf::Vector2f(Constant::HALF_SIZE_PLATFORM, 800.f), nullptr, false));
    //platforms.emplace_back(new Platform(Constant::PLATFORM_SIZE, sf::Vector2f(Constant::VIEW_WIDTH - Constant::HALF_SIZE_PLATFORM, 800.f), nullptr, false));

    // Wall
    platforms.emplace_back(new Platform(sf::Vector2f(Constant::BLOCK_SIZE, Constant::VIEW_HEIGHT + 400.f), sf::Vector2f(15.f, Constant::VIEW_HEIGHT / 2.f), nullptr, true));
    platforms.emplace_back(new Platform(sf::Vector2f(Constant::BLOCK_SIZE, Constant::VIEW_HEIGHT + 400.f), sf::Vector2f(1605, Constant::VIEW_HEIGHT / 2.f), nullptr, true));

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

void Map::setPathfinding(Pathfinding *pathfinding) {
    m_monsterFactory.setPathfinding(pathfinding);
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
            m_nodeGrid.emplace_back(Node(y, x));
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
            if (h<m_rows && h>=0) {
                targetY.push_back(h);
            }
        }

        // Determination pour les y (la hauteur)
        for (int l=(int)floor(posToTest.x) ; l<(int)ceil(posToTest.x + ceil(platform->getSize().x/Constant::BLOCK_SIZE)) ; l++) {
            if (l<m_cols && l>=0) {
                targetX.push_back(l);
            }
        }

        // On place les murs sur les x et y target plus tot
        for (int y : targetY) {
            for (int x : targetX) {
                m_grid[y][x] = 1;
                getNodeByPos(y, x)->setStatus(1);
            }
        }
    }
}

Node* Map::getNodeByPos(int y, int x) {
    if (y>=0 && y<m_rows && x>=0 && x<m_cols) {
        return &m_nodeGrid.at(x+y*m_cols);
    } else {
        return nullptr;
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
            //cout << m_grid[y][x];
            cout << getNodeByPos(y, x)->getStatus();
        }
        cout << endl;
    }
}

void Map::drawGrid(sf::RenderWindow &window) {
    //cout << m_rows << endl;
    for (int y=0 ; y<m_rows ; y++) {
        for (int x=0 ; x<m_cols ; x++) {
            getNodeByPos(y, x)->draw(window);
            //cout << "test" << endl;
        }
    }
}

MonsterFactory *Map::getMonsterFactory() {
    return &m_monsterFactory;
}

std::vector<Node> *Map::getNodeGrid() {
    return &m_nodeGrid;
}

int Map::getRows() {
    return m_rows;
}

int Map::getCols() {
    return m_cols;
}

