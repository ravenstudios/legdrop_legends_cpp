#pragma once
#include "raylib.h"
#include "../Constants.h"
#include "State.h"
#include "../core/Input.h"
#include "../objects/Player.h"
#include "../pause/Pause.h"

class StateManager;



class PauseState : public State{
    public:
        PauseState(StateManager* stateManager);
        void Draw() override;
        void Update() override;
        void UpdateInput(InputState* inputState) override;
        

    private:
        StateManager* m_StateManagerPtr;
        Player* m_Player;
        Pause m_Pause;
        

};
