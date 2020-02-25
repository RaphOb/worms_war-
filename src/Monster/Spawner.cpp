//
// Created by lafay on 21/02/2020.
//

#include <iostream>
#include "Spawner.hh"

Spawner::Spawner() {
    tm.Start();
    tm.SetFrequenceHit(3000);
}

void Spawner::initMonster() {
    Monster *newMonster = m_monsterFactory.Create(m_nameMonster, m_position);
    if (newMonster== nullptr) {
        std::cout << "Ce monstre n'existe pas. Création impossible" << std::endl;
    } else {
        m_listMonster.push_back(newMonster);
    }
}

std::vector<Monster*> Spawner::getListMonsters() {
    return m_listMonster;
}

void Spawner::setPosition(sf::Vector2f p) {
    m_position = p;
}

void Spawner::setDifficulty(int difficulty) {
    m_difficulty = difficulty;
}

void Spawner::setNameMonster(const string &s) {
    m_nameMonster = s;
}

void Spawner::update(sf::Time frameTime) {
    for (Monster *m: m_listMonster) {
        m->update(frameTime);
    }
    if (tm.FrequenceHit()) {
        initMonster(); // Creation d'un monstre
    }
}

void Spawner::draw(sf::RenderWindow &window) {
    for (Monster *m: m_listMonster) {
        m->draw(window);
    }
}