#pragma once
#include "MainEntity.h"

class Player : public MainEntity{
    public:
        Player(float x, float y);
        void Update() override;
        void Input();
    private:
        
};