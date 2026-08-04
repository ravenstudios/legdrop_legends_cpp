#include "StoreUI.h"

StoreUI::StoreUI(Player* player)
    :m_Player(player)
{

}


void StoreUI::Update(){
    switch (m_MenuLevel){
        case StoreMenu::MenuLevel::Main:
            DrawMain();
            break;
        case StoreMenu::MenuLevel::Buy:
            break;
        case StoreMenu::MenuLevel::Sell:
    
            break;
        case StoreMenu::MenuLevel::Exit:
            
            break;
        
        default:
            break;
        }
}

StoreMenu::MenuAction StoreUI::Action(){
    switch (m_MenuLevel){
        case StoreMenu::MenuLevel::Main:
            switch (m_SelectionIndex){
                case 0:
                    LOG("buy");
                    m_MenuLevel = StoreMenu::MenuLevel::Buy;
                    break;
                case 1:
                    m_MenuLevel = StoreMenu::MenuLevel::Sell;
                    break;
                case 2:
                    m_MenuLevel = StoreMenu::MenuLevel::Exit;
                    break;
                
                
                default:
                    break;
                }
            break;
        case StoreMenu::MenuLevel::Buy:
            /* code */
            break;
        case StoreMenu::MenuLevel::Sell:
            /* code */
            break;
        case StoreMenu::MenuLevel::Exit:
            LOG("Exit");
            return {StoreMenu::MenuLevel::Exit, 0};
            break;
        default:
            break;
        }
        return {StoreMenu::MenuLevel::None, 0};
}


void StoreUI::Draw(){
    DrawRectangleRec(m_Rect, BLACK);
    switch (m_MenuLevel){
        case StoreMenu::MenuLevel::Main:
            DrawMain();
            break;
        case StoreMenu::MenuLevel::Buy:
            DrawBuy();
            break;
        case StoreMenu::MenuLevel::Sell:
            DrawSell();
            break;
        case StoreMenu::MenuLevel::Exit:
            
            break;
        
        default:
            break;
        }
}


void StoreUI::DrawBuy(){
    const auto& items = m_Player->GetCurrentNPC()->GetItems();
    for (size_t i = 0; i < items.size(); i++){
        const InventoryItem& inventoryItem = items[i];
        ItemData data = *inventoryItem.item;
        std::string s = data.name + "   "   + std::to_string(inventoryItem.price) + "   " + data.discerption;
        DrawText(s.c_str(), m_Rect.x, m_Rect.y + m_FontSize * i, m_FontSize, WHITE);
        
    }
    DrawRectangleLines(m_Rect.x, m_Rect.y + m_FontSize * m_BuySelectionIndex, m_Rect.width, m_FontSize, WHITE);

    
}

void StoreUI::DrawSell(){}

void StoreUI::DrawMain(){
    DrawRectangleRec(m_Rect, BLACK);
    for(int i = 0; i < m_MainOptions.size(); i++){
        DrawText(m_MainOptions[i].c_str(), m_Rect.x, m_Rect.y + m_FontSize * i, m_FontSize, WHITE);
    }
    // m_SelectionIndex
    DrawRectangleLines(m_Rect.x, m_Rect.y + m_FontSize * m_SelectionIndex, m_Rect.width, m_FontSize, WHITE);
}

StoreMenu::MenuAction StoreUI::UpdateInput(InputState* inputState){
    if(inputState->cancel){
        MenuBack();
    }
    switch (m_MenuLevel){
        case StoreMenu::MenuLevel::Main:
            if(inputState->upPressed){
                if(m_SelectionIndex > 0) m_SelectionIndex--;
            }
            if(inputState->downPressed){
                if(m_SelectionIndex < m_MainOptions.size() - 1) m_SelectionIndex++;
            }
            if(inputState->action){
                Action();
            }
            break;

        case StoreMenu::MenuLevel::Buy:{
            const auto& items = m_Player->GetCurrentNPC()->GetItems();

            if(inputState->upPressed){
                if(m_BuySelectionIndex > 0) m_BuySelectionIndex--;
            }
            if(inputState->downPressed){
                if(m_BuySelectionIndex < items.size() - 1) m_BuySelectionIndex++;
            }
            if(inputState->action){
                return {StoreMenu::MenuLevel::Buy, m_BuySelectionIndex};
            }
            break;
        }
        case StoreMenu::MenuLevel::Sell:
                break;

        
            break;
        case StoreMenu::MenuLevel::Exit:
            if(inputState->action){
                return {StoreMenu::MenuLevel::Exit, 0};
            }
            break;
        
        default:
            break;
        }
        return {StoreMenu::MenuLevel::None, 0};
}


// void StoreUI::MainUpdateInput(InputState* inputState){
//     if(inputState->upPressed){
//         if(m_SelectionIndex > 0) m_SelectionIndex--;
//     }

//     if(inputState->downPressed){
//         if(m_SelectionIndex < m_MainOptions.size() - 1) m_SelectionIndex++;
//     }

//     if(inputState->action){
//         Action();
//     }

    
// }


void StoreUI::MenuBack(){
    m_MenuLevel = StoreMenu::MenuLevel::Main;
    m_SelectionIndex = 0;
}

