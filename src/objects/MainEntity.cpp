#include "MainEntity.h"
#include "../Constants.h"
#include "../Map.h"


MainEntity::MainEntity(const char* path, float x, float y)
    : m_AnimationTimer(m_AnimationSpeed)
{
    LOG(path);
    m_Texture = LoadTexture(path);
    m_Rect.x = x;
    m_Rect.y = y;
    m_Rect.width = BLOCK_SIZE;
    m_Rect.height = BLOCK_SIZE;
    
}


MainEntity::~MainEntity(){
    UnloadTexture(m_Texture);
}


void MainEntity::Update(Map* map){
    m_Map = map;
    Animate();
}


void MainEntity::Move(float dx, float dy){
    float nextX = m_Rect.x + dx;
    float nextY = m_Rect.y + dy;
    MapSize mapSize = m_Map->GetMapSize();
    Rectangle nextRect = m_Rect;
    nextRect.x += dx;
    nextRect.y += dy;

    for (const Rectangle& block : m_Map->GetBlockingRects()){
        if (CheckCollisionRecs(nextRect, block)){
            return;
        }
    }

    if (nextX >= 0 &&
        nextX + m_Rect.width <= mapSize.w * BLOCK_SIZE){
        m_Rect.x = nextX;
    }

    if (nextY >= 0 &&
        nextY + m_Rect.height <= mapSize.h * BLOCK_SIZE){
        m_Rect.y = nextY;
    }
}

void MainEntity::Draw()
{
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


Rectangle MainEntity::GetRect(){
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
    m_CanAnimate = b;
}