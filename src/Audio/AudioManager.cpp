//
// Created by geoff on 04/03/2020.
//

#include <iostream>
#include "AudioManager.hh"

void AudioManager::playSounds() {

    std::cout << "size: " << m_sounds.size() << std::endl;
    for (SoundWrapper &s: m_sounds) {
        if (s.isStopped() && !s.hasBeenPlayed()) {
            s.play();
        }
    }
    clear();
}

void AudioManager::addSound(BufferName bufferName, float volume) {
    sf::Sound s;
    s.setBuffer(AudioLoader::getInstance().getBuffer(bufferName));
    SoundWrapper soundWrapper(s, volume);
    m_sounds.push_back(soundWrapper);
}

void AudioManager::clear() {
    if (!m_sounds.empty() && m_sounds.front().isStopped()) {
        m_sounds.pop_front();
    }
}
