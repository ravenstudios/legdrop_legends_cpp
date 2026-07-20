#include "Timer.h"
#include "../Constants.h"

Timer::Timer(float duration){
    m_Duration = duration;
    m_TimeRemaining = duration;
}


void Timer::Update(float deltaTime){
    m_TimeRemaining -= deltaTime;
}


bool Timer::Finished(){
    return m_TimeRemaining <= 0;
}

void Timer::Reset(){
    m_TimeRemaining = m_Duration;
}

