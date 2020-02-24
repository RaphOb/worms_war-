//
// Created by geoff on 21/02/2020.
//

#include "Map.hh"
#include "Constant.hh"

void Map::initMap() {
    cout << "gydifurg" << endl;
    platforms.reserve(Constant::NB_PLATFORMS);
    platforms.emplace_back(new Platform(sf::Vector2f(1920.f, 50.f), sf::Vector2f(740.f, 900.f), false, true));
    platforms.emplace_back(new Platform(Constant::PLATFORM_SIZE, sf::Vector2f(Constant::HALF_SIZE_PLATFORM, 200.f), false, false));
    platforms.emplace_back(new Platform(Constant::PLATFORM_SIZE, sf::Vector2f(Constant::VIEW_WIDTH - Constant::HALF_SIZE_PLATFORM, 200.f), true, false));
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
