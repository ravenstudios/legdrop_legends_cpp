#include "Store.h"

Store::Store(Player* player)
    :m_Player(player),
    m_StoreUI(player)
{

}


void Store::Update(){
    m_StoreUI.Update();
}


void Store::Draw(){
    m_StoreUI.Draw();
}


StoreMenu::MenuAction Store::UpdateInput(InputState* inputState){
    return m_StoreUI.UpdateInput(inputState);
}