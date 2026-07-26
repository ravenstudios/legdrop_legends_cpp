#pragma once
#include "raylib.h"
#include "../Constants.h"
#include "State.h"
#include "../core/Input.h"

class StateManager;


class BattleState : public State{
    public:
        BattleState(StateManager* stateManager);
        void Draw() override;
        void Update() override;
        void UpdateInput(InputState* inputState) override;

    private:
        StateManager* m_StateManagerPtr;
        
};