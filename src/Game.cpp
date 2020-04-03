//
// Created by geoff on 19/02/2020.
//

#include <iostream>
#include "Game.hh"
#include "Animation.hh"
#include "AnimatedSprite.hh"
#include "Loader/ResourceLoader.hh"

Game::Game() {
    m_map.initMap();
    tm.Start();
    m_rectGameTime.setSize({100, 30});
    m_rectGameTime.setFillColor(sf::Color(200, 200, 200));
    m_rectGameTime.setOutlineColor(sf::Color::Black);
    m_rectGameTime.setOutlineThickness(2);

    m_textGameTime.setFont(ResourceLoader::getInstance().getFont());
    m_textGameTime.setOutlineColor(sf::Color::Black);
    m_textGameTime.setOutlineThickness(2);
    m_textGameTime.setCharacterSize(20);

    m_textFPS.setFont(ResourceLoader::getInstance().getFont());
    m_textFPS.setOutlineColor(sf::Color::Black);
    m_textFPS.setOutlineThickness(2);
    m_textFPS.setCharacterSize(30);
    m_textFPS.setPosition(5.f, 0.f);

    m_textLife.setFont(ResourceLoader::getInstance().getFont());
    m_textLife.setOutlineColor(sf::Color::Black);
    m_textLife.setOutlineThickness(2);
    m_textLife.setCharacterSize(30);
    m_textLife.setPosition(200.f, 0.f);
    initWorm();
}

Worm Game::initWorm() {
    std::vector<sf::IntRect> left = {
            sf::IntRect(0, 0, 32, 34),
            sf::IntRect(32, 0, 32, 34),
            sf::IntRect(64, 0, 32, 34)
    };

    std::vector<sf::IntRect> right = {
            sf::IntRect(0, 34, 32, 34),
            sf::IntRect(32, 34, 32, 34),
            sf::IntRect(64, 34, 32, 34)
    };

    std::vector<sf::IntRect> jumpLeft = {
            sf::IntRect(0, 0, 28, 52),
            sf::IntRect(28, 0, 28, 52),
            sf::IntRect(56, 0, 28, 52),
            sf::IntRect(84, 0, 28, 52)
    };

    std::vector<sf::IntRect> jumpRight = {
            sf::IntRect(0, 52, 28, 52),
            sf::IntRect(28, 52, 28, 52),
            sf::IntRect(56, 52, 28, 52),
            sf::IntRect(84, 52, 28, 52)
    };

    Animation walkingAnimationLeft = Animation(left, ResourceLoader::getInstance().getTexture(WORM_WALKING_TEXTURE));
    Animation walkingAnimationRight = Animation(right, ResourceLoader::getInstance().getTexture(WORM_WALKING_TEXTURE));
    Animation jumpingAnimationLeft = Animation(jumpLeft,
                                               ResourceLoader::getInstance().getTexture(WORM_JUMPING_TEXTURE));
    Animation jumpingAnimationRight = Animation(jumpRight,
                                                ResourceLoader::getInstance().getTexture(WORM_JUMPING_TEXTURE));


    return Worm({walkingAnimationRight, walkingAnimationLeft, jumpingAnimationLeft, jumpingAnimationRight});
}

void Game::update(sf::RenderWindow &window) {
    tm.Update();
    m_rectGameTime.setPosition({window.getView().getCenter().x - m_rectGameTime.getSize().x / 2,
                                window.getView().getCenter().y - window.getView().getSize().y / 2});
    m_textGameTime.setString(getFormatGameTime());
    m_textGameTime.setPosition({m_rectGameTime.getPosition().x + 19, m_rectGameTime.getPosition().y + 5});

}

void Game::draw(sf::RenderWindow &window) {
    window.draw(m_rectGameTime);
    window.draw(m_textGameTime);
    window.draw(m_textFPS);
    window.draw(m_textLife);
}


string Game::getFormatGameTime() {
    int seconds, hours, minutes;
    seconds = tm.GetStartedTime() / 1000;
    minutes = seconds / 60;
    hours = minutes / 60;
    return (int(minutes % 60) < 10 ? "0" : "") + to_string(int(minutes % 60)) + " : " +
           (int(seconds % 60) < 10 ? "0" : "") + to_string(int(seconds % 60));
}

Map Game::getMap() {
    return m_map;
}

void Game::setFPS(int fps) {
    m_textFPS.setString(std::to_string(fps));
}

void Game::setLife(int life) {
    m_textLife.setString("Life: " + std::to_string(life));
}

void Game::drawGameOver(sf::RenderWindow &window) {
    sf::Sprite gameOver;
    float centerX = float(ResourceLoader::getInstance().getTexture(GAME_OVER_TEXTURE).getSize().x) / 2.f;
    float centerY = float(ResourceLoader::getInstance().getTexture(GAME_OVER_TEXTURE).getSize().y) / 2.f;
    gameOver.setTexture(ResourceLoader::getInstance().getTexture(GAME_OVER_TEXTURE));
    gameOver.setOrigin(centerX, centerY);
    gameOver.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    window.draw(gameOver);
}

void Game::setWorm(Worm *worm) {
    m_worm = worm;
}

void Game::initPathfinding() {
    m_pathfinding.setMap(&m_map);
    m_pathfinding.setTarget(m_worm);
    m_map.setPathfinding(&m_pathfinding);
}
