//
// Created by geoff on 04/03/2020.
//

#ifndef LITTLEBIGGAME_AUDIOMANAGER_HH
#define LITTLEBIGGAME_AUDIOMANAGER_HH


#include <vector>
#include <SFML/Audio/Sound.hpp>
#include <deque>
#include "AudioLoader.hh"
#include "SoundWrapper.hh"

class AudioManager {
private:
    AudioManager() = default;
    std::deque<SoundWrapper> m_sounds;

public:
    static AudioManager& getInstance() {
        static AudioManager singleton;
        return singleton;
    }
    void playSounds();
    void addSound(BufferName bufferName, float volume = 100.f);
    void clear();

private:
    AudioManager(const AudioManager &old);
    AudioManager &operator=(const AudioManager &old);

};

#endif //LITTLEBIGGAME_AUDIOMANAGER_HH
