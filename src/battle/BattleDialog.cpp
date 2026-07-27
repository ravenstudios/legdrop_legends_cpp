#include "BattleDialog.h"


BattleDialog::BattleDialog(Rectangle rect, Player* player)
    :m_Player(player)
{
    m_Rect = rect;
}


void BattleDialog::Update(){

}


void BattleDialog::Draw(){
    int fontSize = 20;
    DrawRectangleRec(m_Rect, RED);
    DrawText("Dialog Box", m_Rect.x, m_Rect.y, fontSize, BLACK);
}

