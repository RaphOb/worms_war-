//
// Created by oraph on 22/02/2020.
//

#ifndef LITTLEBIGGAME_INITBOOMER_HH
#define LITTLEBIGGAME_INITBOOMER_HH


#include <SFML/Graphics/Texture.hpp>
#include "Animation.hh"
#include "Boom.hh"

class InitBoomer {
private:
    sf::Texture texture;
    Animation* m_currentAnimation;
    std::vector<Animation> animations;
public:
    InitBoomer();
    Boom createBoom(sf::Vector2f pos);

};


#endif //LITTLEBIGGAME_INITBOOMER_HH
