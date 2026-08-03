#pragma once
#include "raylib.h"
#include "../Constants.h"
#include "../core/Input.h"
#include "../objects/Player.h"
#include "PauseUI.h"

class Pause{
    public:
        Pause(Player* player);
        void Update();
        void Draw();
        void UpdateInput(InputState* inputState);

    private:
       Player* m_Player;
       PauseUI m_PauseUI;
};  