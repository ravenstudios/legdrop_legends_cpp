#pragma once
#include "State.h"
#include "../objects/Player.h"
#include "../Map.h"
#include "../dialog/DialogWindow.h"
#include "../core/Input.h"


class StateManager;


enum class InputMode{
    World,
    Dialog,
    Battle
};


class MainState : public State{
    public:
        MainState(StateManager* stateManager);
        void Update() override;
        void Draw() override;
        void UpdateInput(InputState* inputState) override;
        
    private:
        StateManager* m_StageManagerPtr;
        Player m_Player;
        Map m_Map;
        Camera2D m_Camera;
        DialogWindow m_DialogWindow;
        InputMode m_CurrentInputMode = InputMode::World;
        void Camera();
        
        void GetAction();
        void WorldInput(InputState* inputState);
        void DialogInput(InputState* inputState);
        void BattleInput(InputState* inputState);
        void MenuInput(InputState* inputState);
        
};

