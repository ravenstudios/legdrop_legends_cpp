#pragma once
#include "raylib.h"
#include "../core/Timer.h"
#include <string>


class Map;

struct Directions{
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
};

class MainEntity{
    public:
        MainEntity(const char* npcType, float x, float y);
        MainEntity(const char* npcType);
        ~MainEntity();
        
        virtual void Update(Map* map) = 0;
        virtual void Draw();
        Rectangle GetRect();
        void SetCanAnimate(bool b);
        // void Input();
        void Move(float dx, float dy);
        void SetSpawnPoint(Vector2 spawnPoint);
        Vector2 GetPosition();
        void SetMaxFrames(int maxFrames);
        void SetInDialog(bool b);
        std::string GetBattleImagePath() const;
        Texture2D GetTexture() const;

    private:

    protected:
        Rectangle m_Rect;
        Texture2D m_Texture;
        void Animate();
        float m_Direction = 2;
        float m_AnimationSpeed = 0.15;
        int m_Frame = 0;
        bool m_CanAnimate = true;
        Timer m_AnimationTimer;
        int m_MaxFrames = 4;
        float m_Speed = 5;
        Map* m_Map;
        Directions m_Directions;
        bool m_InDialog = false;
        std::string m_BattleImagePath;


};
