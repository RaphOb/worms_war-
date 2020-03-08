//
// Created by geoff on 13/02/2020.
//

#include <iostream>
#include "Platform.hh"
#include "Loader/ResourceLoader.hh"
#include "Constant.hh"

Platform::Platform(sf::Vector2f size, sf::Vector2f pos, MonsterFactory *monsterFactory, bool isWall) : m_isWall(isWall) {
    m_isSpawner = monsterFactory != nullptr;
    if (m_isWall) m_isSpawner = false; // prevent illogical issue
    if (m_isSpawner) m_isWall = false; // prevent illogical issue
    initTextureRect(size);
    tm.Start();
    tm.SetFrequenceHit(1000); // Get every 1s
    m_body->setTexture(&ResourceLoader::getInstance().getTexture(PLATFORM_DEFAULT_TEXTURE));
    m_body->setSize(size);
    m_body->setPosition(pos);
    m_body->setOrigin(size / 2.0f);
    m_spawner = Spawner();

    if (!m_isWall) {
        initText(pos);
        m_initialCountDownToSpawner = rand() % 60 + 30;
        m_countDownToSpawner = m_initialCountDownToSpawner;
        m_spawner.setPosition(pos);
        m_spawner.setDifficulty(1);
        m_spawner.setNameMonster("GroundMonster");

        if (m_isSpawner) {
            m_spawner.setMonsterFactory(monsterFactory);
            m_body->setTexture(&ResourceLoader::getInstance().getTexture(PLATFORM_SPAWNER_TEXTURE));
        }
    }
}

void Platform::initText(sf::Vector2f pos) {
    if (!m_isWall) {
        sf::Vector2f percentPos = pos;
        percentPos.x -= 15;
        percentPos.y -= 10;
        m_text = new sf::Text();
        m_text->setPosition(percentPos);
        m_text->setFont(ResourceLoader::getInstance().getFont());
        m_text->setCharacterSize(20);
        m_text->setFillColor(sf::Color(255, 255, 255));
        m_text->setOutlineColor(sf::Color(0, 0, 0));
        m_text->setOutlineThickness(3);
    }
}

void Platform::initTextureRect(sf::Vector2f size) {
    if (size.x != Constant::BLOCK_SIZE && size.y == Constant::BLOCK_SIZE) {
        m_body->setTextureRect(sf::IntRect(0, 0, size.x, Constant::BLOCK_SIZE));
    } else if (size.y != Constant::BLOCK_SIZE && size.x == Constant::BLOCK_SIZE) {
        m_body->setTextureRect(sf::IntRect(0, 0, Constant::BLOCK_SIZE, size.y));
    } else {
        m_body->setTextureRect(sf::IntRect(0, 0, size.x, size.y));
    }
}

void Platform::draw(sf::RenderWindow &window) {
    window.draw(*m_body);
    if (!m_isWall)
        window.draw(*m_text);
}

Collider Platform::getCollider() {
    return Collider(m_body);
}

void Platform::update(sf::Time frameTime) {
    if (!m_isWall) {
        if (m_isSpawner) {
            m_spawner.update(frameTime);
        } else {
            if (tm.FrequenceHit()) {
                m_countDownToSpawner -= 1;
                m_text->setString(to_string(getPercentCurse()) + "%");
                m_text->setFillColor(sf::Color(255, 255, 255));
                if (m_countDownToSpawner <= 0) {
                    m_isSpawner = true;
                    m_body->setTexture(&ResourceLoader::getInstance().getTexture(PLATFORM_SPAWNER_TEXTURE));
                } else if (getPercentCurse() >= 50) {
                    m_body->setTexture(&ResourceLoader::getInstance().getTexture(PLATFORM_CURSED_TEXTURE));
                } else {
                    m_body->setTexture(&ResourceLoader::getInstance().getTexture(PLATFORM_DEFAULT_TEXTURE));
                }
            }
        }
    }
}

void Platform::setSpawnerDifficulty(int difficulty) {
    // TODO reset   m_initialCountDownToSpawner = rand() % 60 + 30;
    //              m_countDownToSpawner = m_initialCountDownToSpawner;
    //              with less rand()
    //              +
    //              increase spawner difficulty
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
    if (!m_isWall && direction.y < 0.0f) {
        resetOnWalk();
    }
}

void Platform::onCollision(sf::Vector2f direction, bool isWorm) {
    if (isWorm && !m_isWall && direction.y < 0.0f) {
        resetOnWalk();
    }
}

unsigned int Platform::getPercentCurse() {
    unsigned int percent = m_countDownToSpawner * 100 / m_initialCountDownToSpawner;
    return 100 - percent;
}

void Platform::resetOnWalk() {
    if (!m_isSpawner) {
        m_countDownToSpawner = m_initialCountDownToSpawner;
        m_text->setFillColor(sf::Color(0, 255, 0));
        m_body->setTexture(&ResourceLoader::getInstance().getTexture(PLATFORM_DEFAULT_TEXTURE));
    }
}

sf::Vector2f Platform::getPos() {
    return m_body->getPosition();
}

sf::Vector2f Platform::getSize() {
    return m_body->getSize();
}
