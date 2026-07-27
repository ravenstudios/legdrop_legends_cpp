#pragma once
#include "raylib.h"

struct InputState{
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool action = false;
    bool cancel = false;
    bool upPressed = false;
    bool downPressed = false;
    bool leftPressed = false;
    bool rightPressed = false;
};


class Input{
    public:
        Input();
        InputState GetInputState();
        void Update();

    private:
        InputState m_InputState;
};