#pragma once
#include "states/State.h"
#include "states/MainState.h"
#include "states/BattleState.h"
#include "core/Input.h"
#include "objects/Player.h"

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
        Player* GetPlayer();
        


    private:
        InputState m_InputState;
        Input m_Input;
        Player m_player;
        MainState m_MainState;
        State* m_CurrentState = nullptr;
        State* m_ParrentState = nullptr;
        BattleState m_BattleState;
       


};

