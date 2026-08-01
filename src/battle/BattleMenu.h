#pragma once
#include "raylib.h"
#include "../objects/NPC.h"
#include "../Constants.h"
#include "../objects/Player.h"
#include <vector>
#include <string>
#include "../core/Input.h"
#include "BattleMenuAction.h"

enum class MenuLevel{
    Main,
    Moves,
    Bag,
    Tag
};


class BattleMenu{
    public:
        BattleMenu(Rectangle rect, Player* player);
        void Update();
        void Draw();
        BattleCommand UpdateInput(InputState* inputState);
        BattleCommand Action();
        void MenuBack();
        void StartBattle();



    private:
        Player* m_Player = nullptr;

        Rectangle m_Rect={};
        NPC* m_NPC = nullptr;
        std::vector<std::string> m_MainOptions{"Fight", "Bag", "Tag", "Run"};
        std::vector<std::string> m_Options = m_MainOptions;
        std::vector<Rectangle> m_Rects;
        int m_selectedIndex = 0;
        MenuLevel m_MenuLevel = MenuLevel::Main;
        bool m_InBagMenu = false;
        bool m_InTagMenu = false;
        void LoadMoves();
        std::vector<Item> m_Items = {};
        void LoadItems();
        int m_FontSize = BLOCK_SIZE / 2;
        Rectangle m_BagRect{400, 400, 400, 400};
        Rectangle m_TagRect{400, 400, 400, 400};

};
