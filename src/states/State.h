#pragma once
#include "raylib.h"
#include "../core/Input.h"


class State{
    public:
        virtual ~State() = default;
        virtual void Draw() = 0;
        virtual void Update() = 0;
        virtual void UpdateInput(InputState* inputState) = 0;

    protected:
        InputState m_InputState;
        Input m_Input;
};