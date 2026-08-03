#pragma once

#include "../Constants.h"
#include "../core/Input.h"
#include "../objects/NPC.h"
#include "../objects/Player.h"

#include <nlohmann/json.hpp>
#include <raylib.h>

#include <string>
#include <vector>


struct DialogueOption{
    std::string text;
    std::string next;
};

enum class DialogAction{
    None,
    Battle,
    Exit,
    Heal,
    Store
};

class DialogWindow{
    public:
        void Update();
        void Draw();
        DialogAction Input(InputState* inputState);
        void Start(Player* player, NPC* npc);
        bool GetCanExit() const;
        std::string GetAction() const;
        void ClearAction();

    private:
        const int fontSize = 35;
        const int padding = 20;
        const int lineSpacing = 8;
        const int optionSpacing = 15;

        float m_W = GAME_WIDTH ;
        float m_H = fontSize * 8;
        float m_X = 0.0f;
        float m_Y = 0.0f;

        Rectangle m_Rect = {m_X, m_Y, m_W, m_H};

        Color m_Color = {200, 200, 200, 200};
        bool m_CanDraw = false;
        bool m_CanExit = false;

        int m_SelectionIndex = 0;
        int m_NumOfOptions = 0;

        nlohmann::json m_Dialogue;

        std::string m_CurrentNode;
        std::string m_CurrentText;

        std::vector<DialogueOption> m_DialogOptions;

        void LoadDialog(const nlohmann::json& dialogue);
        void LoadNode(const std::string& nodeName);
        DialogAction HandleNodeAction(const std::string& action);
        std::vector<std::string> WrapText(const std::string& text, int maxWidth, int fontSize);
        std::string m_Action;
};