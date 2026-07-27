#include "BattleMenu.h"


BattleMenu::BattleMenu(Rectangle rect, Player* player)
    :m_Player(player)
{
    m_Rect = rect;
}


void BattleMenu::Update(){

}


void BattleMenu::Draw(){
    int fontSize = BLOCK_SIZE / 4;
    int pad = BLOCK_SIZE / 6;
    DrawRectangleRec(m_Rect, PURPLE);
    
    Rectangle r0{m_Rect.x + pad, m_Rect.y + pad, m_Rect.width / 2 - pad * 2, m_Rect.height / 2 - pad * 2};
    // Rectangle r1{m_Rect.x + pad};
    // Rectangle r2{m_Rect.x + m_Rect.width / 2 + pad, m_Rect.y + pad};
    // Rectangle r3{m_Rect.x + m_Rect.width / 2 + pad};
    DrawRectangleRec(r0, BLUE);
}

