#pragma once
#include "raylib.h"
#include "../Constants.h"
#include "../core/Input.h"
#include "../objects/Player.h"
#include <string>
#include <vector>
#include "PauseRoster.h"

namespace PauseMenu{
    enum class MenuLevel{
        Main,
        Settings,
        Items,
        Roster
    };
}


class PauseUI{
    public:
        PauseUI(Player* player);
        void Update();
        void Draw();
        void UpdateInput(InputState* inputState);
        

    private:
        Player* m_Player;
        std::vector<std::string> m_MainOptions{"Settings", "Items", "Roster"};
        static constexpr int m_FontSize = 20;
        static constexpr float m_w = GAME_WIDTH / 3;
        static constexpr float m_h = GAME_HEIGHT / 3;
        Rectangle m_Rect = {GAME_WIDTH / 2 - m_w / 2, GAME_HEIGHT / 2 - m_h / 2, m_w, m_h};
        int m_SelectionIndex = 0;
        PauseMenu::MenuLevel m_MenuLevel = PauseMenu::MenuLevel::Main;
        void Action();
        PauseRoster m_PauseRoster;
        void DrawMain();
        void DrawSettings();
        void DrawItems();
        void DrawRoster();
        void MenuBack();
};