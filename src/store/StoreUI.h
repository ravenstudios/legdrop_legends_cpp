#pragma once
#include "raylib.h"
#include "../Constants.h"
#include "../core/Input.h"
#include "../objects/Player.h"
#include <vector>
#include <string>
#include "MenuAction.h"

class StoreUI{
    public:
        StoreUI(Player* player);
        void Update();
        void Draw();
        StoreMenu::MenuAction UpdateInput(InputState* inputState);

    private:
        Player* m_Player;
        int m_SelectionIndex = 0;
        int m_BuySelectionIndex = 0;
        int m_SellSelectionIndex = 0;
        std::vector<std::string> m_MainOptions{"Buy", "Sell", "Exit"};
        static constexpr float m_SpriteSize = BLOCK_SIZE / 4;
        static constexpr int m_FontSize = 20;
        static constexpr float m_w = GAME_WIDTH / 2;
        static constexpr float m_h = GAME_HEIGHT / 2;
        Rectangle m_Rect = {GAME_WIDTH / 2 - m_w / 2, GAME_HEIGHT / 2 - m_h / 2, m_w, m_h};
        StoreMenu::MenuLevel m_MenuLevel = StoreMenu::MenuLevel::Main;
        StoreMenu::MenuAction Action();
        void DrawMain();
        void MenuBack();
        void DrawBuy();
        void DrawSell();
};  
