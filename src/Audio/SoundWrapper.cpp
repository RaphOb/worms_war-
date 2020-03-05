//
// Created by geoff on 05/03/2020.
//

#include "SoundWrapper.hh"

bool SoundWrapper::isStopped() {
    return m_sound.getStatus() == sf::SoundSource::Stopped;
}

void SoundWrapper::play() {
    m_sound.setVolume(m_volume);
    m_sound.play();
    m_beenPlayed = true;
}

bool SoundWrapper::hasBeenPlayed() {
    return m_beenPlayed;
}
