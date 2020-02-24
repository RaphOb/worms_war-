//
// Created by geoff on 19/02/2020.
//

#include <iostream>
#include "Game.hh"
#include "Animation.hh"
#include "AnimatedSprite.hh"

Game::Game() {
    tm.Start();
    m_rectGameTime.setSize({100, 30});
    m_rectGameTime.setFillColor(sf::Color(200, 200, 200));
    m_rectGameTime.setOutlineColor(sf::Color::Black);
    m_rectGameTime.setOutlineThickness(2);

    if (!m_font.loadFromFile("../resources/fonts/arial.ttf"))
    {
        std::cout << "Failed to load game time font!" << std::endl;
    }
    m_textGameTime.setFont(m_font);
    m_textGameTime.setOutlineColor(sf::Color::Black);
    m_textGameTime.setOutlineThickness(2);
    m_textGameTime.setCharacterSize(20);
    shape = sf::RectangleShape();
    if (!initTextures())
        exit(-1);
    initWorm();
}

bool Game::initTextures() {
    if (!m_walkingTexture.loadFromFile("../resources/worms_character2.png")) {
        std::cout << "Failed to load worms spritesheet!" << std::endl;
        return false;
    }

    sf::Texture jumpingTexture;
    if (!m_jumpingTexture.loadFromFile("../resources/worms_jump.png")) {
        std::cout << "Failed to load worms jumps" << std::endl;
        return false;
    }

    return true;
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

    Animation walkingAnimationLeft = Animation(left, m_walkingTexture);
    Animation walkingAnimationRight = Animation(right, m_walkingTexture);
    Animation jumpingAnimationLeft = Animation(jumpLeft, m_jumpingTexture);
    Animation jumpingAnimationRight = Animation(jumpRight, m_jumpingTexture);


    return Worm({walkingAnimationRight, walkingAnimationLeft, jumpingAnimationLeft, jumpingAnimationRight});
}

void Game::update(sf::RenderWindow &window) {
    tm.Update();
    m_rectGameTime.setPosition({window.getView().getCenter().x-m_rectGameTime.getSize().x/2, window.getView().getCenter().y-window.getView().getSize().y/2});
    m_textGameTime.setString(getFormatGameTime());
    m_textGameTime.setPosition({m_rectGameTime.getPosition().x+19, m_rectGameTime.getPosition().y+5});
}

void Game::draw(sf::RenderWindow &window) {
    window.draw(m_rectGameTime);
    window.draw(m_textGameTime);
}

string Game::getFormatGameTime() {
    int seconds, hours, minutes;
    seconds = tm.GetStartedTime()/1000;
    minutes = seconds / 60;
    hours = minutes / 60;
    return (int(minutes%60)<10?"0":"") + to_string(int(minutes%60)) + " : " + (int(seconds%60)<10?"0":"") + to_string(int(seconds%60));
}