#pragma once
#include "raylib.h"
#include "../Constants.h"
#include "../objects/Player.h"
#include "../objects/NPC.h"
#include "../core/Timer.h"
#include "BattleHealthBar.h"
#include "BattleDialog.h"
#include "BattleMenu.h"


class BattleUI{
    public:
        BattleUI(Player* player);
        ~BattleUI();
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
        // *************HealthBar*********************
        static constexpr float hbW = BLOCK_SIZE * 6;
        static constexpr float hbH = BLOCK_SIZE;

        static constexpr float phbX = BLOCK_SIZE;
        static constexpr float phbY = BLOCK_SIZE;
        
        static constexpr float chbX = GAME_WIDTH - hbW - BLOCK_SIZE;
        static constexpr float chbY = BLOCK_SIZE * 2  + m_SpriteSize * 6;

        Rectangle m_PlayerHealthBarRect{phbX, phbY, hbW, hbH};
        Rectangle m_CpuHealthBarRect{chbX, chbY, hbW, hbH};
        BattleHealthBar m_PlayerHealthBar;
        BattleHealthBar m_CpuHealthBar;
        

        // *************Sprite************************
        
        
        static constexpr float ph = m_SpriteSize * 8;
        static constexpr float pw = m_SpriteSize * 8;
        static constexpr float px = BLOCK_SIZE * 2;
        static constexpr float py = phbY + hbH + BLOCK_SIZE * 2;

        static constexpr float ch = m_SpriteSize * 6;
        static constexpr float cw = m_SpriteSize * 6;
        static constexpr float cx = GAME_WIDTH - cw - BLOCK_SIZE * 2;
        static constexpr float cy = BLOCK_SIZE;
        
        Rectangle m_PlayerSpriteRect{px, py, pw, ph};
        Rectangle m_CPUSpriteRect{cx, cy, cw, ch};

         // *************Dialog************************
        static constexpr float dh = BLOCK_SIZE * 3.5;
        static constexpr float dw = GAME_WIDTH /2;
        static constexpr float dx = 0;
        static constexpr float dy = GAME_HEIGHT - dh;
        
        Rectangle m_DialogRect{dx, dy, dw, dh};
        BattleDialog m_BattleDialog;

         // *************Menu************************
        static constexpr float mh = BLOCK_SIZE * 3.5;
        static constexpr float mw = GAME_WIDTH / 2;
        static constexpr float mx = GAME_WIDTH / 2;
        static constexpr float my = GAME_HEIGHT - dh;
        
        Rectangle m_MenuRect{mx, my, mw, mh};
        BattleMenu m_BattleMenu;
};  