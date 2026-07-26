#pragma once
#include "State.h"
#include "../objects/Player.h"
#include "../Map.h"
#include "../dialog/DialogWindow.h"
#include "../core/Input.h"


enum class InputMode{
    World,
    Dialog,
    Battle
};


class MainState : public State{
    public:
        MainState();
        void Update() override;
        void Draw() override;
        void UpdateInput();
        
    private:
        Player m_Player;
        Map m_Map;
        Camera2D m_Camera;
        DialogWindow m_DialogWindow;
        InputMode m_CurrentInputMode = InputMode::World;
        void Camera();
        InputState m_InputState;
        Input m_Input;
        void WorldInput();
        void DialogInput();
        void BattleInput();
        void MenuInput();
        
};

