#pragma once
#include "MainEntity.h"

struct Directions{
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
};

class Player : public MainEntity{
    public:
        Player(float x, float y);
        void Update(Map* map) override;
        void Input();
        Vector2 GetPosition();
        
    private:
        Directions m_Directions;
        Vector2 m_LastPOS;
};