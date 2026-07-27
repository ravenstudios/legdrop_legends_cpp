#include "BattleHealthBar.h"

BattleHealthBar::BattleHealthBar(Rectangle rect){
    m_Rect = rect;
    
}


BattleHealthBar::~BattleHealthBar(){

}


void BattleHealthBar::Update(){

}

void BattleHealthBar::SetNPC(NPC* npc){
    m_NPC = npc;
}


void BattleHealthBar::Draw(){
    float pad = BLOCK_SIZE / 8;
    float fontSize = BLOCK_SIZE / 3;
    std::string s;
    if(!m_NPC) return;
    const Data& data = m_NPC->GetData();
    DrawRectangleRec(m_Rect, LIGHTGRAY);
    s = data.name;
    DrawText(s.c_str(), m_Rect.x + pad, m_Rect.y + pad, fontSize, RED);
    s = "LVL: " + std::to_string(data.stats.level);
    int nameWidth = MeasureText(s.c_str(), fontSize);
    DrawText(s.c_str(), m_Rect.x + m_Rect.width - nameWidth - pad, m_Rect.y + pad, fontSize, RED);

    Rectangle maxHPRect{m_Rect.x + pad, m_Rect.y + fontSize + pad, m_Rect.width / 2 - pad * 2, m_Rect.height / 2};
    float hpPercent = static_cast<float>(data.hp) / data.maxHp;
    Rectangle currentHPRect{ maxHPRect.x, maxHPRect.y, maxHPRect.width * hpPercent, maxHPRect.height};
    s = "HP:" + std::to_string(data.hp) + "/" + std::to_string(data.maxHp);
    int textWidth = MeasureText(s.c_str(), fontSize);
    DrawRectangleRec(maxHPRect, GREEN);
    DrawRectangleRec(currentHPRect, BLUE);
    DrawText(s.c_str(), maxHPRect.x + maxHPRect.width / 2 - textWidth / 2, maxHPRect.y + maxHPRect.height / 2 - fontSize / 2, fontSize, RED);

    Rectangle maxMPRect{m_Rect.x + m_Rect.width / 2  + pad, m_Rect.y + fontSize + pad, m_Rect.width / 2 - pad * 2, m_Rect.height / 2};
    float mpPercent = static_cast<float>(data.mp) / data.maxMp;
    Rectangle currentMPRect{ maxMPRect.x, maxMPRect.y, maxMPRect.width * mpPercent, maxMPRect.height};
    s = "MP:" + std::to_string(data.mp) + "/" + std::to_string(data.maxMp);
    textWidth = MeasureText(s.c_str(), fontSize);
    DrawRectangleRec(maxMPRect, GREEN);
    DrawRectangleRec(currentMPRect, BLUE);
    DrawText(s.c_str(), maxMPRect.x + maxMPRect.width / 2 - textWidth / 2, maxMPRect.y + maxMPRect.height / 2 - fontSize / 2, fontSize, RED);


}

