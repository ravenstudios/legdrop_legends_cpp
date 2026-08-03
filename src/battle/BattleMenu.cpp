#include "BattleMenu.h"
#include <vector>


BattleMenu::BattleMenu(Rectangle rect, Player* player)
    :m_Player(player),
    m_Rect(rect)
{
    m_R0 = {m_Rect.x + pad, m_Rect.y + pad, m_Rect.width / 2 - pad * 2, m_Rect.height / 2 - pad * 2};
    m_R1 = {m_Rect.x + m_Rect.width / 2 + pad, m_Rect.y + pad, m_Rect.width / 2 - pad * 2, m_Rect.height / 2 - pad * 2};
    m_R2 = {m_Rect.x + pad, m_Rect.y + m_Rect.height / 2 + pad, m_Rect.width / 2 - pad * 2, m_Rect.height / 2 - pad * 2};
    m_R3 = {m_Rect.x + m_Rect.width / 2 + pad, m_Rect.y + m_Rect.height / 2 + pad, m_Rect.width / 2 - pad * 2, m_Rect.height / 2 - pad * 2};
    m_Rects = {m_R0, m_R1, m_R2, m_R3};
}


void BattleMenu::Update(){

}

// returns to UpdateInput.
BattleCommand BattleMenu::Action(){
    switch (m_MenuLevel){
        case MenuLevel::Main:
            switch (m_selectedIndex){
                case 0:
                    m_MenuLevel = MenuLevel::Moves;
                    m_selectedIndex = 0;
                    break;

                case 1:
                    m_MenuLevel = MenuLevel::Bag;
                    m_selectedIndex = 0;
        
                    break;

                case 2:
                    m_MenuLevel = MenuLevel::Tag;
                    m_selectedIndex = 0;
                    break;

                case 3:
                    MenuBack();
                    return BattleCommand {
                        .type = BattleMenuAction::Run,
                        .selectionIndex = 0
                    };
            }
            break;

        case MenuLevel::Moves:
            MenuBack();
            if(!m_Player->GetCurrentWrestler()->CanAttack()){
                return BattleCommand {
                    .type = BattleMenuAction::Powder,
                    .selectionIndex = 0
                };
            }
            return BattleCommand {
                .type = BattleMenuAction::Attack,
                .selectionIndex = m_selectedIndex
            };
                
        case MenuLevel::Bag:{
            BattleCommand command{
                    .type = BattleMenuAction::Item,
                    .selectionIndex = m_ItemIndex
                };
            MenuBack();
            return command;
        }

        case MenuLevel::Tag:{
            BattleCommand command{
                .type = BattleMenuAction::Tag,
                .selectionIndex = m_TagIndex
            };
            MenuBack();
            return command;
        }
    }
    return BattleCommand {
        .type = BattleMenuAction::None,
        .selectionIndex = 0
    };
 
}


void BattleMenu::MenuBack(){
    m_MenuLevel = MenuLevel::Main;
    m_ItemIndex = 0;
    m_TagIndex = 0;
    m_selectedIndex = 0;
}

// returns to Battle::UpdateInput
BattleCommand BattleMenu::UpdateInput(InputState* inputState){
    if(inputState->upPressed){
        if(m_MenuLevel == MenuLevel::Bag){
            if(m_ItemIndex >0) m_ItemIndex--;
        }
        if(m_MenuLevel == MenuLevel::Tag){
            if(m_TagIndex >0) m_TagIndex--;
        }
        else{
            if(m_selectedIndex == 2 || m_selectedIndex == 3) m_selectedIndex -= 2;
        }
    }

    if(inputState->downPressed){
        if(m_MenuLevel == MenuLevel::Bag){
            if(m_ItemIndex < m_Player->GetItems().size() - 1) m_ItemIndex++;
        }
        if(m_MenuLevel == MenuLevel::Tag){
            if(m_TagIndex < m_Player->GetRoster().size() - 1) m_TagIndex++;
        }
        else{
            if(m_selectedIndex == 0 || m_selectedIndex == 1)m_selectedIndex += 2;
        }
    }

    
    
    if(inputState->leftPressed && (m_selectedIndex == 1 || m_selectedIndex == 3))m_selectedIndex--;
    if(inputState->rightPressed && (m_selectedIndex == 0 || m_selectedIndex == 2))m_selectedIndex++;
    if(inputState->action){
        return Action();
    }

    if(inputState->cancel)MenuBack();

    return BattleCommand {
        .type = BattleMenuAction::None,
        .selectionIndex = 3
    };
}

void BattleMenu::Draw(){
    DrawRectangleRec(m_Rect, PURPLE);

    if(m_MenuLevel == MenuLevel::Main){
       DrawMain();
       return;
    }

    if(m_MenuLevel == MenuLevel::Bag){
       DrawItems();
       return;
    }

    if(m_MenuLevel == MenuLevel::Tag){
        DrawTag();
        return;
    }

    if(m_MenuLevel == MenuLevel::Moves){
        DrawMoves();
        return;
    }
    
    
}


void BattleMenu::DrawMain(){
    std::string s;
    int textWidth;
    for (size_t i = 0; i < 4; i++){
        DrawRectangleRec(m_Rects[i], BLUE);
        s = m_Options[i];
        textWidth = MeasureText(s.c_str(), m_FontSize);
        Rectangle r = m_Rects[i];
        DrawText(s.c_str(), r.x + r.width / 2 - textWidth / 2, r.y + r.height / 2 - m_FontSize / 2, m_FontSize, BLACK);
    }
    DrawRectangleLinesEx(m_Rects[m_selectedIndex], 3, BLACK);
}



void BattleMenu::DrawItems(){
    DrawRectangleRec(m_Rect, MAGENTA);
    std::vector<InventoryItem> inventoryItems = m_Player->GetItems();
    for (int i = 0; i < inventoryItems.size(); i ++){
        std::string s = inventoryItems[i].item->name + "   QTY:" + std::to_string(inventoryItems[i].qty);
        DrawText(s.c_str(), m_Rect.x, m_Rect.y + m_FontSize * i, m_FontSize, BLACK);
    }
    if(!inventoryItems.empty()){
        DrawRectangleLines(m_Rect.x, m_Rect.y + m_FontSize * m_ItemIndex, m_Rect.width,  m_FontSize, BLACK);

    }
}


void BattleMenu::DrawTag(){
    DrawRectangleRec(m_Rect, SKYBLUE);
    // std::vector<NPC>& wrestlers = m_Player->GetRoster();
    const auto& roster = m_Player->GetRoster();

    for (int i = 0; i < roster.size(); i ++){
        DrawText(roster[i]->GetData().name.c_str(), m_Rect.x, m_Rect.y + m_FontSize * i, m_FontSize, BLACK);
    }
    DrawRectangleLines(m_Rect.x, m_Rect.y + m_FontSize * m_TagIndex, m_Rect.width,  m_FontSize, BLACK);
}


void BattleMenu::DrawMoves(){
    std::vector<Attack> attacks = m_Player->GetCurrentWrestler()->GetData().attacks;

    std::string s;
    int textWidth;

    if(m_Player->GetCurrentWrestler()->CanAttack()){
        for (size_t i = 0; i < attacks.size(); i++){
            DrawRectangleRec(m_Rects[i], BLUE);
            s = attacks[i].name;
            textWidth = MeasureText(s.c_str(), m_FontSize);
            Rectangle r = m_Rects[i];
            DrawText(s.c_str(), r.x + r.width / 2 - textWidth / 2, r.y + r.height / 2 - m_FontSize / 2, m_FontSize, BLACK);
        }
    }
    else{
        DrawRectangleRec(m_R0, BLUE);
        s = "Powder";
        textWidth = MeasureText(s.c_str(), m_FontSize);
        DrawText(s.c_str(), m_R0.x + m_R0.width / 2 - textWidth / 2, m_R0.y + m_R0.height / 2 - m_FontSize / 2, m_FontSize, BLACK);
    }
    
    DrawRectangleLinesEx(m_Rects[m_selectedIndex], 3, BLACK);
}


void BattleMenu::StartBattle(){
    LOG("START BATTLE MENU");
    MenuBack();
}

