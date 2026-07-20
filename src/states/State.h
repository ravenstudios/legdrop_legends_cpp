#pragma once
#include "raylib.h"


class State{
    public:
        virtual ~State() = default;
        virtual void Draw() = 0;
        virtual void Update() = 0;
    private:
};