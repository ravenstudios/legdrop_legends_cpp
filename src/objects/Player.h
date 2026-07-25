#pragma once
#include "MainEntity.h"



class Map;

class Player : public MainEntity{
    public:
        Player(float x, float y);
        void Update(Map* map) override;
        void Draw() override;
        void Input();
        void Walk();
        void Talk();
        void CheckDoorCollision();
        Rectangle GetTalkHitBox();


    private:
        Vector2 m_LastPOS;
        bool m_IsTalking = false;
        bool m_InDialog = false;
        Rectangle m_TalkHitBox;
        Map* m_Map;

};
