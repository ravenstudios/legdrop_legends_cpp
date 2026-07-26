#pragma once
#include "raylib.h"
#include "../Constants.h"
#include "../objects/Player.h"
#include "../objects/NPC.h"
#include "../core/Timer.h"

class Battle{
    public:
        Battle(Player* player);
        ~Battle();
        void Update();
        void Draw();
        void StartBattle(NPC* npc);


    private:
        Player* m_Player;
        NPC* m_NPC = nullptr;
        Texture2D m_PlayerTexture{};
        Texture2D m_NPCTexture{};

        static constexpr float m_AnimationSpeed = 0.15;
        int m_PlayerFrame = 0;
        int m_CpuFrame = 0;
        Timer m_PlayerAnimationTimer;
        Timer m_CpuAnimationTimer;
        int m_PlayerMaxFrames;
        int m_CpuMaxFrames;
        void Animate();

        static constexpr float m_SpriteSize = 32.0;
        
        static constexpr float ph = m_SpriteSize * 8;
        static constexpr float pw = m_SpriteSize * 8;
        static constexpr float py = GAME_HEIGHT - ph;
        Rectangle m_PlayerSpriteRect{0, py, pw, ph};
        static constexpr float ch = m_SpriteSize * 6;
        static constexpr float cw = m_SpriteSize * 6;
        Rectangle m_CPUSpriteRect{GAME_WIDTH - cw, 0, cw, ch};
        
};  