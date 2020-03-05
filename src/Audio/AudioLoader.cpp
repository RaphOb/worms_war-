//
// Created by geoff on 03/03/2020.
//

#include <iostream>
#include "AudioLoader.hh"



bool AudioLoader::loadAudio() {
    return loadSounds()
        && loadMusic();
}

bool AudioLoader::loadSounds() {
    return loadWormSound()
        && loadWeaponSound();
}

bool AudioLoader::loadMusic() {
    return m_backgroundMusic.openFromFile("../resources/sound/Waterflame - Glorious morning.wav");
}

bool AudioLoader::loadWeaponSound() {
    sf::SoundBuffer b;
    if (!b.loadFromFile("../resources/sound/Explosion1.wav")) {
        std::cout << "Error while loading the explosion sound" << std::endl;
        return false;
    }
    m_buffers.emplace_back(b);
    return true;
}



bool AudioLoader::loadWormSound() {
    sf::SoundBuffer b;
    if (!b.loadFromFile("../resources/sound/Walk-Expand.wav")) {
        std::cout << "Error while loading the walk sound" << std::endl;
        return false;
    }
    m_buffers.emplace_back(b);
    return true;
}

sf::Music &AudioLoader::getMusic() {
    return m_backgroundMusic;
}

AudioLoader::AudioLoader() {
    m_buffers.reserve(2);
}

sf::SoundBuffer &AudioLoader::getBuffer(BufferName bufferName) {
    return m_buffers[bufferName];
}
