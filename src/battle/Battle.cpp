#include "Battle.h"
#include "../Constants.h"


Battle::Battle(Player* player)
    :m_Player(player),
    m_PlayerAnimationTimer(m_AnimationSpeed),
    m_CpuAnimationTimer(m_AnimationSpeed)
{
    m_PlayerTexture = LoadTexture(m_Player->GetCurrentWrestler()->GetBattleImagePath().c_str());
    m_PlayerMaxFrames = m_Player->GetCurrentWrestler()->GetBattleSpriteMaxFrames();
}



Battle::~Battle(){
    UnloadTexture(m_PlayerTexture);
    if (m_NPCTexture.id != 0) {
        UnloadTexture(m_NPCTexture);
    }   
}


void Battle::Update(){
    Animate();
}


void Battle::Draw(){
    Rectangle source{m_SpriteSize * m_PlayerFrame, 0.0f, m_SpriteSize, m_SpriteSize};
    DrawTexturePro(m_PlayerTexture, source, m_PlayerSpriteRect, Vector2{0.0f, 0.0f}, 0.0f, WHITE);
    if(m_NPC){
        Rectangle source{m_SpriteSize * m_CpuFrame, 0.0f, m_SpriteSize, m_SpriteSize};
        DrawTexturePro(m_NPCTexture, source, m_CPUSpriteRect, Vector2{0.0f, 0.0f}, 0.0f, WHITE);
    }
}


void Battle::Animate(){
    m_PlayerAnimationTimer.Update(GetFrameTime());
    m_CpuAnimationTimer.Update(GetFrameTime());

    if(m_PlayerAnimationTimer.Finished()){
        m_PlayerAnimationTimer.Reset();
        m_PlayerFrame++;
        m_PlayerFrame %= m_PlayerMaxFrames;
    }

    if(!m_NPC) return;

    if(m_CpuAnimationTimer.Finished()){
        m_CpuAnimationTimer.Reset();
        m_CpuFrame++;
        m_CpuFrame %= m_CpuMaxFrames;
    }
}

void Battle::StartBattle(NPC* npc){
    if(!npc) return;

    if(m_NPCTexture.id != 0){
        UnloadTexture(m_NPCTexture);
        m_NPCTexture = {};
    }

    m_NPC = npc;
    m_NPCTexture = LoadTexture(m_NPC->GetBattleImagePath().c_str());
    m_CpuMaxFrames =  m_NPC->GetBattleSpriteMaxFrames();
    m_CpuFrame = 0;
    m_CpuAnimationTimer.Reset();
}