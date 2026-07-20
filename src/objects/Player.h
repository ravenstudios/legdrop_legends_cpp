#pragma once
#include "MainEntity.h"



class Player : public MainEntity{
    public:
        Player(float x, float y);
        void Update(Map* map) override;
        void Input();
        
        
    private:
        Vector2 m_LastPOS;
};