#pragma once
#include "raylib.h"
#include "../Constants.h"
#include "State.h"
#include "../core/Input.h"
#include "../objects/Player.h"
#include "../store/Store.h"


class StateManager;

class StoreState : public State{
    public:
        StoreState(StateManager* stateManager);
        void Draw() override;
        void Update() override;
        void UpdateInput(InputState* inputState) override;
        

    private:
        StateManager* m_StateManagerPtr;
        Player* m_Player;
        Store m_Store;
};
