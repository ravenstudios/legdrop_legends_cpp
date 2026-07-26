#pragma once
#include "states/State.h"
#include "states/MainState.h"
#include "states/BattleState.h"
#include "core/Input.h"


class StateManager{
    public:
        StateManager();
        void Draw();
        void Update();
        void StoreParrentState(State* state);
        void SwitchToBattleState();
        void SwitchToMainState();
        void SwitchToPauseState();
        void UpdateInput();
        


    private:
        InputState m_InputState;
        Input m_Input;
        MainState m_MainState;
        State* m_CurrentState = nullptr;
        State* m_ParrentState = nullptr;
        BattleState m_BattleState;


};

