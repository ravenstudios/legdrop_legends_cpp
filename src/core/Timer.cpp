#include "Timer.h"
#include "../Constants.h"

Timer::Timer(float duration){
    m_Duration = duration;
    m_TimeRemaining = duration;
}


void Timer::Update(float deltaTime){
    if(m_IsPaused)return;
    m_TimeRemaining -= deltaTime;
}


bool Timer::Finished(){
    return m_TimeRemaining <= 0;
}

void Timer::Reset(){
    m_TimeRemaining = m_Duration;
}

void Timer::SetPause(bool p){
    m_IsPaused = p;
}
