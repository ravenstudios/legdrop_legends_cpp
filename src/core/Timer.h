#pragma once

class Timer{
    public:
        Timer(float duration);
        void Update(float deltaTime);
        bool Finished();
        void Reset();
        void SetPause(bool p);
        void SetDuration(float duration);
        float GetmTimeRemaining();
    private:
        float m_Duration = 0;
        float m_TimeRemaining = 0;
        bool m_IsPaused = false;

};