#include "PauseUI.h"

PauseUI::PauseUI(Player* player)
    :m_Player(player),
    m_PauseRoster(player)
{

}


void PauseUI::Update(){
    m_PauseRoster.Update();
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
    switch (m_MenuLevel){
        case PauseMenu::MenuLevel::Main:
            DrawMain();
            break;
        case PauseMenu::MenuLevel::Settings:
            DrawSettings();
            break;
        case PauseMenu::MenuLevel::Items:
            DrawItems();
            break;
        case PauseMenu::MenuLevel::Roster:
            DrawRoster();
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


void PauseUI::DrawSettings(){

}


void PauseUI::DrawItems(){

}


void PauseUI::DrawRoster(){
    m_PauseRoster.Draw();
}





void PauseUI::UpdateInput(InputState* inputState){
    if(inputState->upPressed){
        if(m_SelectionIndex > 0) m_SelectionIndex--;
    }

    if(inputState->downPressed){
        if(m_SelectionIndex < m_MainOptions.size() - 1) m_SelectionIndex++;
    }

    if(inputState->action){
        Action();
    }

    if(inputState->cancel){
        MenuBack();
    }
}

void PauseUI::MenuBack(){
    m_MenuLevel = PauseMenu::MenuLevel::Main;
    m_SelectionIndex = 0;
}