#pragma once

class Timer{
    public:
        Timer(float duration);
        void Update(float deltaTime);
        bool Finished();
        void Reset();
    private:
        float m_Duration = 0;
        float m_TimeRemaining = 0;

};