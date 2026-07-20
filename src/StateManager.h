#pragma once
#include "states/State.h"
#include "states/MainState.h"


class StateManager{
    public:
        StateManager();
        void Draw();
        void Update();

    private:
        MainState m_MainState;
        State* m_CurrentState;
};

