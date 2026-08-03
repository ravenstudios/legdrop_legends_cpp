#pragma once
#include "raylib.h"
#include "../objects/NPC.h"
#include "../Constants.h"
#include "../objects/Player.h"
#include <vector>
#include <string>
#include "../core/Input.h"
#include "BattleMenuAction.h"
#include "../objects/Items.h"

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
        
        std::vector<std::string> m_Options{"Attack", "Bag", "Tag", "Run"};
        
        int m_selectedIndex = 0;
        int m_ItemIndex = 0;
        int m_TagIndex = 0;
        MenuLevel m_MenuLevel = MenuLevel::Main;
        std::vector<InventoryItem> m_Items = {};

        int m_FontSize = BLOCK_SIZE / 2;
        
        void DrawMain();
        void DrawItems();
        void DrawTag();
        void DrawMoves();


        static constexpr int pad = BLOCK_SIZE / 6;

        Rectangle m_R0{};
        Rectangle m_R1{};
        Rectangle m_R2{};
        Rectangle m_R3{};
        std::vector<Rectangle> m_Rects;

};
