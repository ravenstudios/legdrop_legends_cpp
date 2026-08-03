#include "PauseUI.h"

PauseUI::PauseUI(Player* player)
    :m_Player(player),
    m_PauseRoster(player),
    m_PauseItems(player)
{

}


void PauseUI::Update(){
    switch (m_MenuLevel){
        case PauseMenu::MenuLevel::Main:
            DrawMain();
            break;
        case PauseMenu::MenuLevel::Settings:
            break;
        case PauseMenu::MenuLevel::Items:
            m_PauseItems.Update();
            break;
        case PauseMenu::MenuLevel::Roster:
            m_PauseRoster.Update();
            break;
        
        default:
            break;
        }
}

void PauseUI::Action(){
    switch (m_MenuLevel){
        case PauseMenu::MenuLevel::Main:
            switch (m_SelectionIndex){
                case 0:
                    m_MenuLevel = PauseMenu::MenuLevel::Settings;
                    break;
                case 1:
                    m_MenuLevel = PauseMenu::MenuLevel::Items;
                    break;
                case 2:
                    m_MenuLevel = PauseMenu::MenuLevel::Roster;
                    break;
                
                
                default:
                    break;
                }
            break;
        case PauseMenu::MenuLevel::Settings:
            /* code */
            break;
        case PauseMenu::MenuLevel::Items:
            /* code */
            break;
        case PauseMenu::MenuLevel::Roster:
            /* code */
            break;
        default:
            break;
        }
}


void PauseUI::Draw(){
    DrawRectangleRec(m_Rect, BLACK);
    switch (m_MenuLevel){
        case PauseMenu::MenuLevel::Main:
            DrawMain();
            break;
        case PauseMenu::MenuLevel::Settings:
            break;
        case PauseMenu::MenuLevel::Items:
            m_PauseItems.Draw();
            break;
        case PauseMenu::MenuLevel::Roster:
            m_PauseRoster.Draw();
            break;
        
        default:
            break;
        }
}


void PauseUI::DrawMain(){
    DrawRectangleRec(m_Rect, BLACK);
    for(int i = 0; i < m_MainOptions.size(); i++){
        DrawText(m_MainOptions[i].c_str(), m_Rect.x, m_Rect.y + m_FontSize * i, m_FontSize, WHITE);
    }
    // m_SelectionIndex
    DrawRectangleLines(m_Rect.x, m_Rect.y + m_FontSize * m_SelectionIndex, m_Rect.width, m_FontSize, WHITE);
}








void PauseUI::UpdateInput(InputState* inputState){
    if(inputState->cancel){
        MenuBack();
    }

    switch (m_MenuLevel){
        case PauseMenu::MenuLevel::Main:
            MainUpdateInput(inputState);
            break;
        case PauseMenu::MenuLevel::Settings:
            break;
        case PauseMenu::MenuLevel::Items:{
            MenuAction menuAction = m_PauseItems.UpdateInput(inputState);
            if(menuAction.menuLevel == PauseMenu::MenuLevel::Items){
                UseItem(menuAction.selectedIndex);
                break;
            }
        }
            break;
        case PauseMenu::MenuLevel::Roster:
            m_PauseRoster.UpdateInput(inputState);
            break;
        
        default:
            break;
        }
}


void PauseUI::MainUpdateInput(InputState* inputState){
    if(inputState->upPressed){
        if(m_SelectionIndex > 0) m_SelectionIndex--;
    }

    if(inputState->downPressed){
        if(m_SelectionIndex < m_MainOptions.size() - 1) m_SelectionIndex++;
    }

    if(inputState->action){
        Action();
    }

    
}


void PauseUI::MenuBack(){
    m_MenuLevel = PauseMenu::MenuLevel::Main;
    m_SelectionIndex = 0;
}


void PauseUI::UseItem(int index){
    m_Player->UseItem(index);

}