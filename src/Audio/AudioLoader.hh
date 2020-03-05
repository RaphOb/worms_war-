//
// Created by geoff on 03/03/2020.
//

#ifndef LITTLEBIGGAME_AUDIOLOADER_HH
#define LITTLEBIGGAME_AUDIOLOADER_HH


#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

enum BufferName {
    WORM_WALKING_BUFFER,
    EXPLOSION_BUFFER
};

class AudioLoader {
private:
    AudioLoader();

    sf::Music m_backgroundMusic;
    std::vector<sf::SoundBuffer> m_buffers;
public:
    static AudioLoader& getInstance() {
        static AudioLoader singleton;
        return singleton;
    }

    bool loadAudio();
    sf::Music& getMusic();
    sf::SoundBuffer& getBuffer(BufferName bufferName);

private:
    AudioLoader(const AudioLoader &old);
    AudioLoader &operator=(const AudioLoader &old);

    bool loadMusic();
    bool loadSounds();
    bool loadWormSound();
    bool loadWeaponSound();
};


#endif //LITTLEBIGGAME_AUDIOLOADER_HH
