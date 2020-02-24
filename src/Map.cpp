//
// Created by geoff on 21/02/2020.
//

#include "Map.hh"
#include "Constant.hh"

void Map::initMap() {
    platforms.reserve(10);
    platforms.emplace_back(new Platform(nullptr, sf::Vector2f(1920.f, 300.f), sf::Vector2f(740.f, 1100.f)));
    platforms.emplace_back(new Platform(nullptr, Constant::PLATFORM_SIZE, sf::Vector2f(0.f, 200.f)));
    platforms.emplace_back(new Platform(nullptr, Constant::PLATFORM_SIZE, sf::Vector2f(Constant::VIEW_WIDTH, 200.f)));
    platforms.emplace_back(new Platform(nullptr, Constant::PLATFORM_SIZE, sf::Vector2f(450.f, 300.f)));
    platforms.emplace_back(new Platform(nullptr, Constant::PLATFORM_SIZE, sf::Vector2f(Constant::VIEW_WIDTH - 450.f, 300.f)));
    platforms.emplace_back(new Platform(nullptr, Constant::PLATFORM_SIZE, sf::Vector2f(0.f, 400.f)));
    platforms.emplace_back(new Platform(nullptr, Constant::PLATFORM_SIZE, sf::Vector2f(Constant::VIEW_WIDTH, 400.f)));

    platforms.emplace_back(new Platform(nullptr, Constant::PLATFORM_SIZE, sf::Vector2f(Constant::VIEW_WIDTH / 2, 500.f)));

    platforms.emplace_back(new Platform(nullptr, Constant::PLATFORM_SIZE, sf::Vector2f(0.f, 600.f)));
    platforms.emplace_back(new Platform(nullptr, Constant::PLATFORM_SIZE, sf::Vector2f(Constant::VIEW_WIDTH, 600.f)));
    platforms.emplace_back(new Platform(nullptr, Constant::PLATFORM_SIZE, sf::Vector2f(450.f, 700.f)));
    platforms.emplace_back(new Platform(nullptr, Constant::PLATFORM_SIZE, sf::Vector2f(Constant::VIEW_WIDTH - 450.f, 700.f)));
    platforms.emplace_back(new Platform(nullptr, Constant::PLATFORM_SIZE, sf::Vector2f(0.f, 800.f)));
    platforms.emplace_back(new Platform(nullptr, Constant::PLATFORM_SIZE, sf::Vector2f(Constant::VIEW_WIDTH, 800.f)));

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
