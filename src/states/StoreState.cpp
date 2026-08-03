#include "StoreState.h"
#include "../StateManager.h"
#include "../store/MenuAction.h"


StoreState::StoreState(StateManager* stateManager)
    :m_StateManagerPtr(stateManager),
    m_Player(stateManager->GetPlayer()),
    m_Store(m_Player)
{

}


void StoreState::Draw(){

    m_Store.Draw();
}


void StoreState::Update(){
    m_Store.Update();
    
}

void StoreState::UpdateInput(InputState* inputState){
    StoreMenu::MenuAction action = m_Store.UpdateInput(inputState);
    if(action.menuLevel == StoreMenu::MenuLevel::Buy){
        const auto& items = m_Player->GetCurrentNPC()->GetItems();

        const InventoryItem& shopItem = items[action.selectedIndex];
        const ItemData* ItemData = shopItem.item;

        int cost = shopItem.price;
        if(m_Player->GetMoney() >= cost){
            m_Player->AddItem(ItemData, 1);
            m_Player->AdjustMoney(-cost);
        }
    }
    if(action.menuLevel == StoreMenu::MenuLevel::Exit){
        m_StateManagerPtr->SwitchToMainState();
    }

}

