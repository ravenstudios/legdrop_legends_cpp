#include "MainEntity.h"
#include "../Constants.h"
#include "../Map.h"

#include <string>
#include <unordered_map>



std::string GetNPCImagePath(const std::string& npcName){
    static const std::unordered_map<std::string, std::string> npcImages = {
        {"player", "manager-Sheet.png"},
        {"crawdaddy", "cradaddy2_16x16-Sheet.png"},
        {"brother", "Brother16x16-Sheet.png"},
        {"clown", "clown_16x16-Sheet.png"},
        {"angel", "Angel16x16-Sheet.png"},
        {"mr_murica", "Mr Murica-Sheet.png"},
        {"jukebox", "jukebox.png"},
        {"bad_jim", "bad jim-Sheet.png"},
        {"nurse", "Nurse-Sheet.png"},
        {"clerk", "clerk-Sheet.png"},
        {"punching_bag", "16x16_blank.png"}


    };

    auto found = npcImages.find(npcName);

    if (found == npcImages.end())
    {
        return "src/assets/images/16x16_blank.png";
    }
    std::string path = "src/assets/images/" + found->second;
    return path;
}


MainEntity::MainEntity(const char* npcType, float x, float y)
    : m_AnimationTimer(m_AnimationSpeed)
{
    LOG(npcType);
    std::string imagePath = GetNPCImagePath(npcType);
    m_Texture = LoadTexture(imagePath.c_str());
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

void MainEntity::SetSpawnPoint(Vector2 spawnPoint){
    LOG(spawnPoint.x);
    m_Rect.x = spawnPoint.x;
    m_Rect.y = spawnPoint.y;
}


Vector2 MainEntity::GetPosition(){
    return {m_Rect.x, m_Rect.y};
}

void MainEntity::SetMaxFrames(int maxFrames){
    m_MaxFrames = maxFrames;
}