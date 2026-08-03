#include "PauseItems.h"



PauseItems::PauseItems(Player* player)
    :m_Player(player)
{
    

}


void PauseItems::Update(){
}


void PauseItems::Draw(){
    DrawRectangleRec(m_Rect, BLACK);
    const auto& items = m_Player->GetItems();
    if(!items.size()) return;

    for(int i = 0; i < items.size(); i++){
        const InventoryItem& inventoryItem = items[i];
        ItemData data = *inventoryItem.item;

        std::string s = inventoryItem.item->name + 
            " Qty:" + std::to_string(inventoryItem.qty) +
            " " + data.discerption;
            
        DrawText(s.c_str(), m_Rect.x, m_Rect.y + m_FontSize * i, m_FontSize, WHITE);
    }
    DrawRectangleLines(m_Rect.x, m_Rect.y + m_SelectionIndex * m_FontSize, m_Rect.width, m_FontSize, WHITE);
}


MenuAction PauseItems::UpdateInput(InputState* inputState){
    const auto& items = m_Player->GetItems();
    if(inputState->upPressed){
        if(m_SelectionIndex > 0) m_SelectionIndex--;
    }

    if(inputState->downPressed){
        if(m_SelectionIndex > items.size() - 1) m_SelectionIndex++;
    }

    if(inputState->action){
        if(!items.size())return MenuAction{PauseMenu::MenuLevel::None, 0};
        return MenuAction{PauseMenu::MenuLevel::Items, m_SelectionIndex};
    };

    return MenuAction{PauseMenu::MenuLevel::None, 0};
}


