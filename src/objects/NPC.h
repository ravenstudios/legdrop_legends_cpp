#pragma once
#include "MainEntity.h"

class Map;

class NPC : public MainEntity{
    public:
        NPC(float x, float y, const char* path, bool canWalk);
        void Update(Map* map) override;

    private:
        
        float m_WalkDuration = 0.75f;
        float m_WaitDuration = 1.5f;
        Timer m_WalkTimer;
        Timer m_WaitTimer;

        Vector2 m_MoveDirection{0.0f, 0.0f};

        
        float m_Speed = 2;
        float RandomWalkDuration();
        float RandomWaitDuration();
        bool m_IsWalking = false;
        bool m_CanWalk = true;
        void ChooseRandomMovement();
        void StopMoving();
};      

