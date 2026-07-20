#include "Player.h"
#include "../Map.h"

Player::Player(float x, float y)
    : MainEntity("player", x, y)
{

}



void Player::Update(Map* map){
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
    for (const Door& door : map->GetDoors()){
        if (CheckCollisionRecs(m_Rect, door.rect)){
            // LOG(door.path);
            std::string path = std::string("src/assets/maps/") + door.path;
            if(door.isEntrance){
                m_LastPOS = {m_Rect.x, m_Rect.y + BLOCK_SIZE};
                map->LoadMap(path.c_str());
                SetSpawnPoint(map->GetPlayerSpawnPoint());
            }
            if(door.isExit){
                map->LoadMap(path.c_str());
                SetSpawnPoint(m_LastPOS);
            }
        }
    }
}


void Player::Input(){
    m_Directions.up = IsKeyDown(KEY_W);
    m_Directions.down = IsKeyDown(KEY_S);
    m_Directions.left = IsKeyDown(KEY_A);
    m_Directions.right = IsKeyDown(KEY_D);
    if (m_Directions.up){
        m_Direction = 1;
        Move(0, -m_Speed);
        m_AnimationTimer.SetPause(false);
    }
    if (m_Directions.right){
        m_Direction = 2;
        Move(m_Speed, 0);
        m_AnimationTimer.SetPause(false);
    }
    if (m_Directions.down){
        m_Direction = 0;
        Move(0, m_Speed);
        m_AnimationTimer.SetPause(false);
    }
    if (m_Directions.left){
        m_Direction = 3;
        Move(-m_Speed, 0);
        m_AnimationTimer.SetPause(false);
    }
    
}

