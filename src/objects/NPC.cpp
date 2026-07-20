#include "NPC.h"
#include "../Map.h"


NPC::NPC(float x, float y, const char* npcType, bool canWalk)
    : MainEntity(npcType, x, y),
    m_WalkTimer(m_WalkDuration),
    m_WaitTimer(m_WaitDuration),
    m_CanWalk(canWalk)
{
    //  m_WaitTimer.Start();
    StopMoving();
    m_WaitTimer.SetDuration(RandomWalkDuration());
    m_WaitTimer.Reset();
}



void NPC::Update(Map* map){
    MainEntity::Update(map);
    if (!m_CanWalk){
        StopMoving();
        // Animate();
        
        return;
    }

    

    float deltaTime = GetFrameTime();
    
    m_WalkTimer.Update(deltaTime);
    m_WaitTimer.Update(deltaTime);

    if (m_IsWalking){
        m_CanAnimate = true;
        if (m_Directions.up){
            m_Direction = 1;
            Move(0, -m_Speed);
        }
        if (m_Directions.right){
            m_Direction = 2;
            Move(m_Speed, 0);
        }
        if (m_Directions.down){
            m_Direction = 0;
            Move(0, m_Speed);
        }
        if (m_Directions.left){
            m_Direction = 3;
            Move(-m_Speed, 0);
        }

        m_AnimationTimer.SetPause(false);

        if (m_WalkTimer.Finished()){
            m_IsWalking = false;
            StopMoving();
            m_WaitTimer.SetDuration(RandomWalkDuration());
            m_WaitTimer.Reset();
        }
    }
    else{
        if (m_WaitTimer.Finished()){
            ChooseRandomMovement();

            m_IsWalking = true;
            m_WalkTimer.SetDuration(RandomWalkDuration());
            m_WalkTimer.Reset();
        }
    }

    // Animate();
    
}


void NPC::ChooseRandomMovement(){
    int direction = GetRandomValue(0, 3);

    switch (direction){
        case 0:
            m_Directions.up = true;
            m_Directions.down = false;
            m_Directions.left = false;
            m_Directions.right = false;
            break;

        case 1:
            m_Directions.up = false;
            m_Directions.down = true;
            m_Directions.left = false;
            m_Directions.right = false;
            break;

        case 2:
            m_Directions.up = false;
            m_Directions.down = false;
            m_Directions.left = true;
            m_Directions.right = false;
            break;

        case 3:
            m_Directions.up = false;
            m_Directions.down = false;
            m_Directions.left = false;
            m_Directions.right = true;
            break;
    }
}

void NPC::StopMoving(){
    m_CanAnimate = false;
    m_Directions.up = false;
    m_Directions.down = false;
    m_Directions.left = false;
    m_Directions.right = false;
}


float NPC::RandomWalkDuration(){
    return static_cast<float>(GetRandomValue(100, 200)) / 100.0f;
}


float NPC::RandomWaitDuration(){
    return static_cast<float>(GetRandomValue(150, 300)) / 100.0f;
}