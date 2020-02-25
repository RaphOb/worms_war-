//
// Created by oraph on 25/02/2020.
//

#ifndef LITTLEBIGGAME_SCENES_HH
#define LITTLEBIGGAME_SCENES_HH


#include "AbstractEntity.hh"
#include <vector>

class Scenes {
public:
    Scenes();
    void add(std::unique_ptr<AbstractEntity>);
    void update(sf::Time);
    void collide();
    void draw(sf::RenderWindow& window);
    void clean();
    void clear();

private:
    std::vector<std::unique_ptr<AbstractEntity>> elements;
    sf::Clock chrono{};
    sf::Time time;

};


#endif //LITTLEBIGGAME_SCENES_HH
