//
// Created by oraph on 22/02/2020.
//

#include <vector>
#include <iostream>
#include <SFML/Graphics/Rect.hpp>
#include "InitBoomer.hh"

InitBoomer::InitBoomer() {
    if (!texture.loadFromFile("../resources/boom.png")) {
        std::cout << " texture not load " << std::endl;
    } else {
        std::vector<sf::IntRect> boomExplosion = {
                sf::IntRect(0, 0, 1600, 1100),
                sf::IntRect(320, 0, 320, 232),
                sf::IntRect(640, 0, 320, 232),
                sf::IntRect(960, 0, 320, 232),
                sf::IntRect(1280, 0, 320, 232),
                sf::IntRect(0, 220, 1600, 1100),
                sf::IntRect(320, 440, 320, 232),
                sf::IntRect(640, 660, 320, 232),
                sf::IntRect(960, 880, 320, 232),
                sf::IntRect(1280, 1100, 320, 232),
        };
        std::cout << "ça passe bien ici" << std::endl;
        m_currentAnimation = new Animation(boomExplosion, texture);
        animations.reserve(1);
        animations.emplace_back(*m_currentAnimation);

    }

}

Boom InitBoomer::createBoom(sf::Vector2f pos) {
    return Boom(animations, pos);
}
