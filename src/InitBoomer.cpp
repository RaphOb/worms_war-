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
                sf::IntRect(0, 0, 320, 232),
                sf::IntRect(320, 0, 320, 232),
                sf::IntRect(640, 0, 320, 232),
                sf::IntRect(960, 0, 320, 232),
                sf::IntRect(1280, 0, 320, 232),
                sf::IntRect(0, 232, 320, 232),
                sf::IntRect(320, 232, 320, 232),
                sf::IntRect(640, 232, 320, 232),
                sf::IntRect(960, 232, 320, 232),
                sf::IntRect(1280, 232, 320, 232),
                sf::IntRect(0, 465, 320, 232),
                sf::IntRect(320, 465, 320, 232),
                sf::IntRect(640, 465, 320, 232),
                sf::IntRect(960, 465, 320, 232),
                sf::IntRect(1280, 465, 320, 232),
                sf::IntRect(0, 698, 320, 232),
                sf::IntRect(320, 698, 320, 232),
                sf::IntRect(640, 698, 320, 232),
                sf::IntRect(960, 698, 320, 232),
                sf::IntRect(1280, 698, 320, 232),
                sf::IntRect(0, 930, 320, 232),
                sf::IntRect(320, 930, 320, 232),
                sf::IntRect(640, 930, 320, 232),
                sf::IntRect(960, 930, 320, 232),
                sf::IntRect(1280, 930, 320, 232),
                sf::IntRect(0, 1163, 320, 232),
                sf::IntRect(320, 1163, 320, 232),
                sf::IntRect(640, 1163, 320, 232),
                sf::IntRect(960, 1163, 320, 232),
                sf::IntRect(1280, 1163, 320, 232),
        };
        std::cout << "ça passe bien ici" << std::endl;
        m_currentAnimation = new Animation(boomExplosion, texture);
        animations.reserve(1);
        animations.emplace_back(*m_currentAnimation);

    }

}

Boom InitBoomer::createBoom(sf::Vector2f pos) {
    return Boom(animations, pos, AnimatedSprite(sf::seconds(0.05), true, false));
}
