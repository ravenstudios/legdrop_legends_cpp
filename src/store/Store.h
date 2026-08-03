#pragma once
#include "raylib.h"
#include "../Constants.h"
#include "../core/Input.h"
#include "../objects/Player.h"
#include "StoreUI.h"

class Store{
    public:
        Store(Player* player);
        void Update();
        void Draw();
        StoreMenu::MenuAction UpdateInput(InputState* inputState);

    private:
       Player* m_Player;
       StoreUI m_StoreUI;
};  