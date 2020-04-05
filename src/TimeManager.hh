//
// Created by lafay on 09/02/2020.
//

#ifndef IDV_CPP4___PROGRAMMATION_EN_C___TIMEMANAGER_HH
#define IDV_CPP4___PROGRAMMATION_EN_C___TIMEMANAGER_HH

#include <iostream>
#include <chrono>
#include <ctime>

class TimeManager {
protected:
private:
    //static TimeManager instance;
    std::chrono::time_point<std::chrono::system_clock> start;
    std::chrono::time_point<std::chrono::system_clock> update1;
    std::chrono::time_point<std::chrono::system_clock> update2;
    std::chrono::time_point<std::chrono::system_clock> testNull;
    std::chrono::time_point<std::chrono::system_clock> lastFrenquenceHit;
    unsigned int m_frequence;

public:
    TimeManager();
    static TimeManager& GetInstance();
    void Start();
    void Update();
    unsigned int GetElapsedTime() const;
    unsigned int GetStartedTime() const;
    bool FrequenceHit();
    void SetFrequenceHit(unsigned int);
    ~TimeManager();

};

#endif //IDV_CPP4___PROGRAMMATION_EN_C___TIMEMANAGER_HH
