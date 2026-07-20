#pragma once
#include "raylib.h"
#include "../core/Timer.h"
#include "../Map.h"



class MainEntity{
    public:
        MainEntity(const char* path, float x, float y);
        ~MainEntity();
        virtual void Update(Map* map) = 0;
        void Draw();
        Rectangle GetRect();
        void SetCanAnimate(bool b);
        void Input();
        void Move(float dx, float dy);
        void SetSpawnPoint(Vector2 spawnPoint);
        
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
        

};