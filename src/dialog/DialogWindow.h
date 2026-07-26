#pragma once
#include "../Constants.h"
#include "raylib.h"
#include "../objects/Player.h"
#include "../objects/NPC.h"
#include "../core/Input.h"

class DialogWindow{
    public:
        void Update();
        void Draw();
        void Show();
        void Hide();
        void Start(Player* player, NPC* npc);
        void Input(InputState inputState);
        bool GetCanExit() const;

    private:
        float m_W  = GAME_WIDTH / 2;
        float m_H = GAME_HEIGHT / 2;
        float m_X = GAME_WIDTH / 2 - m_W / 2;
        float m_Y = 0;
        Rectangle m_Rect = {m_X, m_Y, m_W, m_H};
        Color m_Color = { 112, 31, 126, 200 };
        bool m_CanDraw = false;
        InputState m_InputState;
        int m_SelectionIndex = 0;
        int m_NumOfOptions = 3;
        bool m_CanExit = false;

};