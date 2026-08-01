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
    DrawText(m_message.c_str(), m_Rect.x, m_Rect.y, fontSize, BLACK);
}


void BattleDialog::SetMessage(std::string msg){
  m_message = msg;
  Draw();
}
