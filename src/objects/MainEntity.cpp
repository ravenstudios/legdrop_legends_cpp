#include "MainEntity.h"
#include "../Constants.h"
#include "../Map.h"
#include <string>
#include "Player.h"



MainEntity::MainEntity(const char* imagePath, float x, float y)
    : m_AnimationTimer(m_AnimationSpeed)
{
    m_Texture = LoadTexture(imagePath);
    m_Rect.x = x;
    m_Rect.y = y;
    m_Rect.width = BLOCK_SIZE;
    m_Rect.height = BLOCK_SIZE;

}

MainEntity::MainEntity(const char* imagePath)
    : m_AnimationTimer(m_AnimationSpeed)
{
    m_Texture = LoadTexture(imagePath);
    m_Rect.width = BLOCK_SIZE;
    m_Rect.height = BLOCK_SIZE;

}


MainEntity::~MainEntity(){
    UnloadTexture(m_Texture);
}


void MainEntity::Update(Map* map){
    m_Map = map;

    if(m_IsWalking){
        m_CanAnimate = true;
        if(m_Rect.x < m_NextX){
            m_Rect.x += m_Speed;

            if(m_Rect.x >= m_NextX){
                m_Rect.x = m_NextX;
                m_IsWalking = false;
                m_CanAnimate = false;
            }
        }
        else if(m_Rect.x > m_NextX){
            m_Rect.x -= m_Speed;

            if(m_Rect.x <= m_NextX){
                m_Rect.x = m_NextX;
                m_IsWalking = false;
                m_CanAnimate = false;
            }
        }
        else if(m_Rect.y < m_NextY){
            m_Rect.y += m_Speed;

            if(m_Rect.y >= m_NextY){
                m_Rect.y = m_NextY;
                m_IsWalking = false;
                m_CanAnimate = false;
            }
        }
        else if(m_Rect.y > m_NextY){
            m_Rect.y -= m_Speed;

            if(m_Rect.y <= m_NextY){
                m_Rect.y = m_NextY;
                m_IsWalking = false;
                m_CanAnimate = false;
            }
        }
        else{
            // m_IsWalking = false;
            m_CanAnimate = false;
        }
    }

    Animate();
}


void MainEntity::Move(float dx, float dy){
    if(m_InDialog) return;
    if(m_IsWalking) return;
    // m_CanAnimate = true;

    float nextX = m_Rect.x + (dx * BLOCK_SIZE);
    float nextY = m_Rect.y + (dy * BLOCK_SIZE);

    Rectangle nextRect = m_Rect;
    nextRect.x = nextX;
    nextRect.y = nextY;

    // Don't walk into blocking tiles
    for(const Rectangle& block : m_Map->GetBlockingRects()){
        if(CheckCollisionRecs(nextRect, block)){
            return;
        }
    }

    // Don't walk into NPCs
    for(const auto& npc : m_Map->GetNPCs()){
        if(npc.get() == this) continue;

        if(CheckCollisionRecs(nextRect, npc->GetRect())){
            return;
        }
    }

    const Player* player = m_Map->GetPlayer();
    if(player != nullptr && player != this){
        if(CheckCollisionRecs(nextRect, player->GetRect())){
            return;
        }
    }
    // Movement is valid

    if(nextX >= 0 && nextX <= (m_Map->GetMapSize().w * BLOCK_SIZE) - BLOCK_SIZE) m_NextX = nextX;
    if(nextY >= 0 && nextY <= (m_Map->GetMapSize().h * BLOCK_SIZE) - BLOCK_SIZE) m_NextY = nextY;
    
    m_IsWalking = true;
}

void MainEntity::Draw(){
    constexpr float SPRITE_SIZE = BLOCK_SIZE / 4;

    Rectangle source{
        m_Frame * SPRITE_SIZE,
        m_Direction * SPRITE_SIZE,
        SPRITE_SIZE,
        SPRITE_SIZE
    };

    DrawTexturePro(
        m_Texture,
        source,
        m_Rect,
        Vector2{0.0f, 0.0f},
        0.0f,
        WHITE
    );
}


Rectangle MainEntity::GetRect() const {
    return m_Rect;
}


void MainEntity::Animate(){
    m_AnimationTimer.Update(GetFrameTime());
    if(!m_CanAnimate) return;
    if(m_AnimationTimer.Finished()){
        m_AnimationTimer.Reset();
        m_Frame++;
        m_Frame %= m_MaxFrames;
    }
}


void MainEntity::SetCanAnimate(bool b){
    // m_CanAnimate = b;
}

void MainEntity::SetSpawnPoint(Vector2 spawnPoint){
    m_Rect.x = spawnPoint.x;
    m_Rect.y = spawnPoint.y;
    m_NextX = m_Rect.x;
    m_NextY = m_Rect.y;
    m_IsWalking = false;

}


Vector2 MainEntity::GetPosition(){
    return {m_Rect.x, m_Rect.y};
}


void MainEntity::SetMaxFrames(int maxFrames){
    m_MaxFrames = maxFrames;
}


void MainEntity::SetInDialog(bool b){
    m_InDialog = b;
}

std::string MainEntity::GetBattleImagePath() const{
    return m_BattleImagePath;

}

Texture2D MainEntity::GetTexture() const{
    return m_Texture;
}