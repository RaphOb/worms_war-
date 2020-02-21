//
// Created by lafay on 09/02/2020.
//
#include "TimeManager.hh"
#include <iostream>
#include <chrono>
#include <ctime>
#include <cstring>
using namespace std;

TimeManager::TimeManager() {}
TimeManager::~TimeManager() {}

TimeManager& TimeManager::GetInstance() {
    static TimeManager instance;
    return instance;
}

void TimeManager::Start() {
    start = std::chrono::system_clock::now();
    update1 = std::chrono::system_clock::now();
    update2 = std::chrono::system_clock::now();
    lastFrenquenceHit = std::chrono::system_clock::now();
}

void TimeManager::Update() {
    update1 = update2;
    update2 = std::chrono::system_clock::now();
}

bool TimeManager::FrequenceHit() {
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-lastFrenquenceHit).count() >= m_frequence) {
        lastFrenquenceHit = std::chrono::system_clock::now();
        return true;
    }
    return false;
}

void TimeManager::SetFrequenceHit(unsigned int f) {
    m_frequence = f;
}

unsigned int TimeManager::GetElapsedTime() const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(update2-update1).count();
}

unsigned int TimeManager::GetStartedTime() const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(update2-start).count();
}
