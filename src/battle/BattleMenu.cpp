#include "BattleMenu.h"
#include <vector>


BattleMenu::BattleMenu(Rectangle rect, Player* player)
    :m_Player(player)
{
    m_Rect = rect;
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
                    LoadMoves();
                    m_selectedIndex = 0;
                    break;

                case 1:
                    m_MenuLevel = MenuLevel::Bag;
                    m_selectedIndex = 0;
                    m_InBagMenu = true;
                    LOG("items");
                    LoadItems();
                    break;

                case 2:
                    m_MenuLevel = MenuLevel::Tag;
                    m_selectedIndex = 0;
                    m_InTagMenu = true;
                    break;

                case 3:
                    LOG("Run");
                    return BattleCommand {
                        .type = BattleMenuAction::Run,
                        .selectionIndex = 0
                    };
                    break;
            }
            break;

        case MenuLevel::Moves:
            return BattleCommand {
                .type = BattleMenuAction::Attack,
                .selectionIndex = m_selectedIndex
            };
            break;

                
        case MenuLevel::Bag:
            return BattleCommand {
                        .type = BattleMenuAction::Item,
                        .selectionIndex = m_ItemIndex
                    };

        case MenuLevel::Tag:
          return BattleCommand {
              .type = BattleMenuAction::Tag,
              .selectionIndex = 3
          };
            break;
    }
    return BattleCommand {
        .type = BattleMenuAction::None,
        .selectionIndex = 3
    };
}


void BattleMenu::MenuBack(){
    if(m_MenuLevel != MenuLevel::Main){
        m_MenuLevel = MenuLevel::Main;
        m_InTagMenu = false;
        m_InBagMenu = false;
        m_Options = m_MainOptions;
    }

}

// returns to Battle::UpdateInput
BattleCommand BattleMenu::UpdateInput(InputState* inputState){
    if(inputState->upPressed){
        if(m_InBagMenu){
            if(m_ItemIndex >0)m_ItemIndex--;
        }
        else{
            if(m_selectedIndex == 2 || m_selectedIndex == 3) m_selectedIndex -= 2;
        }
    }

    if(inputState->downPressed){
        if(m_InBagMenu){
            if(m_ItemIndex < m_Player->GetCurrentWrestler()->GetData().items.size() - 1) m_ItemIndex++;
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
    if(m_InBagMenu){
       DrawItems();
       return;
    }

    if(m_InTagMenu){
        DrawTag();
        return;
    }

    DrawMoves();
    
}


void BattleMenu::DrawItems(){
    m_InTagMenu = false;
    DrawRectangleRec(m_Rect, MAGENTA);
    for (int i = 0; i < m_Items.size(); i ++){
        std::string s = m_Items[i].name + "   QTY:" + std::to_string(m_Items[i].qty);
        DrawText(s.c_str(), m_Rect.x, m_Rect.y + m_FontSize * i, m_FontSize, BLACK);
    }
    DrawRectangleLines(m_Rect.x, m_Rect.y + m_FontSize * m_ItemIndex, m_Rect.width,  m_FontSize, BLACK);
}


void BattleMenu::DrawTag(){
    m_InBagMenu = false;
        DrawRectangleRec(m_Rect, SKYBLUE);

}


void BattleMenu::DrawMoves(){
    int pad = BLOCK_SIZE / 6;
    DrawRectangleRec(m_Rect, PURPLE);

    Rectangle r0{m_Rect.x + pad, m_Rect.y + pad, m_Rect.width / 2 - pad * 2, m_Rect.height / 2 - pad * 2};
    Rectangle r1{m_Rect.x + m_Rect.width / 2 + pad, m_Rect.y + pad, m_Rect.width / 2 - pad * 2, m_Rect.height / 2 - pad * 2};
    Rectangle r2{m_Rect.x + pad, m_Rect.y + m_Rect.height / 2 + pad, m_Rect.width / 2 - pad * 2, m_Rect.height / 2 - pad * 2};
    Rectangle r3{m_Rect.x + m_Rect.width / 2 + pad, m_Rect.y + m_Rect.height / 2 + pad, m_Rect.width / 2 - pad * 2, m_Rect.height / 2 - pad * 2};

    m_Rects = {r0, r1, r2, r3};

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




void BattleMenu::LoadMoves(){
    m_Options = {"", "", "", ""};

    std::vector<Attack> attacks = m_Player->GetCurrentWrestler()->GetData().attacks;

    for (size_t i = 0; i < attacks.size() && i < m_Options.size(); i++) {
        m_Options[i] = attacks[i].name;
    }

}


void BattleMenu::LoadItems(){
    LOG("load items");
    std::vector<Item> items = m_Player->GetCurrentWrestler()->GetData().items;
    for (size_t i = 0; i < items.size() && i < items.size(); i++) {
        m_Items.emplace_back(items[i]);
    }

}


void BattleMenu::StartBattle(){
    LOG("START BATTLE MENU");
    MenuBack();
}