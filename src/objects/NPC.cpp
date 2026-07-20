#include "NPC.h"


NPC::NPC(float x, float y, const char* path, bool canWalk)
    : MainEntity(path, x, y)
{
    m_CanWalk = canWalk;
}



void NPC::Update(Map* map){
    MainEntity::Update(map);
    Input();
    bool walking =
    m_Directions.up ||
    m_Directions.down ||
    m_Directions.left ||
    m_Directions.right;

    if (walking){
        m_CanAnimate = true;
    }
    else{
        m_CanAnimate = false;
    }
    
}

