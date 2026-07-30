#pragma once
#include "raylib.h"
#include "../objects/NPC.h"
#include "../Constants.h"
#include "../objects/Player.h"
#include <string>

class BattleDialog{
    public:
        BattleDialog(Rectangle rect, Player* player);
        void Update();
        void Draw();
        void SetMessage(std::string msg);

    private:
        Player* m_Player = nullptr;
        Rectangle m_Rect={};
        std::string m_message= "Test";


};
