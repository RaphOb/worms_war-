//
// Created by geoff on 13/02/2020.
//

#include <iostream>
#include "Platform.hh"

Platform::Platform(sf::Vector2f size, sf::Vector2f pos, bool isSpawner) {
    tm.Start();
    tm.SetFrequenceHit(1000);
    body.setSize(size);
    body.setPosition(pos);
    body.setOrigin(size / 2.0f);
    m_countDownToSpawner = 30;
    m_spawner = Spawner();
    m_spawner.setPosition(pos);
    m_spawner.setDifficulty(1);
    m_spawner.setNameMonster("GroundMonster");
    if (isSpawner)
        body.setFillColor(sf::Color::Black);
}

void Platform::draw(sf::RenderWindow &window) {
    window.draw(body);
}

Collider Platform::getCollider() {
    return {&body};
}

void Platform::update(sf::Time frameTime) {
    if (m_isSpawner) {
        m_spawner.update(frameTime);
    } else {
        if (tm.FrequenceHit()) {
            m_countDownToSpawner -= 1;

            if (m_countDownToSpawner<=0) {
                m_isSpawner = true;
                body.setFillColor(sf::Color::Black);
            } else if (m_countDownToSpawner<=15) {
                body.setFillColor(sf::Color::Red);
            } else {
                body.setFillColor(sf::Color::Yellow);
            }
        }
    }

}

void Platform::setSpawnerDifficulty(int difficulty) {
    m_spawner.setDifficulty(difficulty);
}

Spawner Platform::getSpawner() {
    return m_spawner;
}

std::string Platform::Serialize() {
    std::string str;
    return str;
}

void Platform::onCollision(sf::Vector2f direction) {
    
}