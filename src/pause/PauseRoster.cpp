#include "PauseRoster.h"



PauseRoster::PauseRoster(Player* player)
    :m_Player(player),
    m_AnimationTimer(m_AnimationSpeed)
    
    // m_Roster (m_Player->GetRoster())

{
    

}


void PauseRoster::Update(){
    Animate();
}

std::string getString(const NPC& npc){
    Data d = npc.GetData();
    std::string s =  d.name + 
    " | HP " + 
    std::to_string(d.hp) + 
    ":" +
    std::to_string(d.maxHp) + 
    " | MP " +
    std::to_string(d.mp) + 
    ":" +
    std::to_string(d.maxMp) + 
    " | LVL: " + 
    std::to_string(d.level); 

    return s;

}

void PauseRoster::Draw(){
    const auto& roster = m_Player->GetRoster();
    int gap = BLOCK_SIZE / 2;
    
    const NPC& currentWrestler = *m_Player->GetCurrentWrestler();
    DrawAvatar(currentWrestler, m_Rect.x, m_Rect.y + BLOCK_SIZE * 0 + gap * 0);
    
    DrawText(getString(currentWrestler).c_str(), m_Rect.x + BLOCK_SIZE * 1.5, m_Rect.y + BLOCK_SIZE * 0 + gap * 0 + BLOCK_SIZE / 2, m_FontSize, WHITE);


    for(int i = 1; i < roster.size() + 1; i++){
        const NPC& npc = *roster[i - 1];
        DrawAvatar(npc, m_Rect.x, m_Rect.y + BLOCK_SIZE * i + gap * i);
        DrawText(getString(npc).c_str(), m_Rect.x + BLOCK_SIZE * 1.5, m_Rect.y + BLOCK_SIZE * i + gap * i  + BLOCK_SIZE / 2, m_FontSize, WHITE);
    }
    
}


void PauseRoster::UpdateInput(InputState* inputState){

}


void PauseRoster::DrawAvatar(const NPC& npc, float x, float y){
    

    Rectangle source{
        m_Frame * m_SpriteSize,
        0.0f,
        m_SpriteSize,
        m_SpriteSize
    };

    Rectangle r{x, y, BLOCK_SIZE, BLOCK_SIZE};
    DrawTexturePro(
        npc.GetTexture(),
        source,
        r,
        Vector2{0.0f, 0.0f},
        0.0f,
        WHITE
    );
}


void PauseRoster::Animate(){
    m_AnimationTimer.Update(GetFrameTime());
    if(m_AnimationTimer.Finished()){
        m_AnimationTimer.Reset();
        m_Frame++;
        m_Frame %= m_MaxFrames;
    }
}