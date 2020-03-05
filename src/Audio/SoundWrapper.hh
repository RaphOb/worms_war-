//
// Created by geoff on 05/03/2020.
//

#ifndef LITTLEBIGGAME_SOUNDWRAPPER_HH
#define LITTLEBIGGAME_SOUNDWRAPPER_HH


#include <SFML/Audio/Sound.hpp>

class SoundWrapper {
private:
    sf::Sound m_sound;
    bool m_beenPlayed;
    float m_volume;
public:
    explicit SoundWrapper(sf::Sound _sound, float _volume): m_sound(_sound), m_beenPlayed(false), m_volume(_volume) {}

    bool isStopped();
    bool hasBeenPlayed();
    void play();
};


#endif //LITTLEBIGGAME_SOUNDWRAPPER_HH
