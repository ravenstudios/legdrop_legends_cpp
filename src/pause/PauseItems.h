#pragma once
#include "raylib.h"
#include "../Constants.h"
#include "../core/Input.h"
#include "../objects/Player.h"
#include <string>
#include <vector>
#include "../objects/Items.h"
#include "MenuAction.h"


class PauseItems{
    public:
        PauseItems(Player* player);
        void Update();
        void Draw();
        MenuAction UpdateInput(InputState* inputState);
        

    private:
        Player* m_Player;
        static constexpr float m_SpriteSize = BLOCK_SIZE / 4;
        static constexpr int m_FontSize = 20;
        static constexpr float m_w = GAME_WIDTH / 2;
        static constexpr float m_h = GAME_HEIGHT / 2;
        Rectangle m_Rect = {GAME_WIDTH / 2 - m_w / 2, GAME_HEIGHT / 2 - m_h / 2, m_w, m_h};
        int m_SelectionIndex = 0;
        
   
};