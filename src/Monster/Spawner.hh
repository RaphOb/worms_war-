//
// Created by lafay on 21/02/2020.
//

#ifndef LITTLEBIGGAME_SPAWNER_HH
#define LITTLEBIGGAME_SPAWNER_HH

#include <SFML/System.hpp>
#include "Monster.hh"
#include "MonsterFactory.hh"
#include "../TimeManager.hh"

using namespace std;

class Spawner {
public:
    Spawner();
    void initMonster();
    std::vector<Monster*> getListMonsters();
    void setPosition(sf::Vector2f);
    void setDifficulty(int);
    void setNameMonster(const string&);
    void update(sf::Time);
    void draw(sf::RenderWindow &);
    void cleanList();
    void clearMonster();
    void setMonsterFactory(MonsterFactory *);

private:
    MonsterFactory *m_monsterFactory;
    std::vector<Monster*> m_listMonster;
    sf::Vector2f m_position;
    int m_difficulty;
    string m_nameMonster;
    TimeManager tm;
};

#endif //LITTLEBIGGAME_SPAWNER_HH
