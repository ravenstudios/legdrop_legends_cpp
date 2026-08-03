#pragma once
#include "raylib.h"
#include "../Constants.h"
#include "../core/Input.h"
#include "../objects/Player.h"
#include <string>
#include <vector>
#include "../objects/NPC.h"
#include "../core/Timer.h"


class PauseRoster{
    public:
        PauseRoster(Player* player);
        void Update();
        void Draw();
        void UpdateInput(InputState* inputState);
        

    private:
        Player* m_Player;
        
        void DrawAvatar(const NPC& npc, float x, float y);
        void Animate();
        int m_Frame = 0;
        static constexpr float m_SpriteSize = BLOCK_SIZE / 4;
        static constexpr int m_FontSize = 20;
        static constexpr float m_w = GAME_WIDTH / 2;
        static constexpr float m_h = GAME_HEIGHT / 2;
        Rectangle m_Rect = {GAME_WIDTH / 2 - m_w / 2, GAME_HEIGHT / 2 - m_h / 2, m_w, m_h};
        float m_AnimationSpeed = 0.15;
        Timer m_AnimationTimer;
        int m_MaxFrames = 4;
   
};