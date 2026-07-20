#pragma once
#include "State.h"
#include "../objects/Player.h"

class MainState : public State{
    public:
        MainState();
        void Update() override;
        void Draw() override;
    private:
        Player m_Player;
        
};

