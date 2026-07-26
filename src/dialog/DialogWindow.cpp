#include "DialogWindow.h"
#include "../Constants.h"
#include <sstream>
#include <vector>


void DialogWindow::Update(){
    // Nothing needed here yet.
}


void DialogWindow::Draw(){
    if (!m_CanDraw){
        return;
    }

    

    DrawRectangleRec(m_Rect, m_Color);

    int textX = static_cast<int>(m_Rect.x) + padding;
    int currentY = static_cast<int>(m_Rect.y) + padding;

    int availableWidth = static_cast<int>(m_Rect.width) - padding * 2;

    std::vector<std::string> textLines =
        WrapText(
            m_CurrentText,
            availableWidth,
            fontSize
        );

    for (const std::string& line : textLines){
        DrawText(line.c_str(), textX, currentY, fontSize, BLACK);
        currentY += fontSize + lineSpacing;
    }

    currentY += 15;

    for (int i = 0; i < static_cast<int>(m_DialogOptions.size()); i++){
        const DialogueOption& option = m_DialogOptions[i];

        std::vector<std::string> optionLines =
            WrapText(
                option.text,
                availableWidth - 20,
                fontSize
            );

        int optionStartY = currentY;

        for (const std::string& line : optionLines){
            DrawText(line.c_str(), textX + 10, currentY, fontSize, BLACK);
            currentY += fontSize + lineSpacing;
        }

        if (i == m_SelectionIndex){
            Rectangle selectionRect = {
                static_cast<float>(textX),
                static_cast<float>(optionStartY - 3),
                static_cast<float>(availableWidth),
                static_cast<float>(
                    currentY - optionStartY + 6
                )
            };

            DrawRectangleLinesEx(selectionRect, 4.0f, BLACK);
        }
        currentY += optionSpacing;
    }
}


void DialogWindow::Input(InputState inputState){
    if (!m_CanDraw){
        return;
    }

    if (!m_DialogOptions.empty()){
        if (inputState.upPressed){
            m_SelectionIndex--;

            if (m_SelectionIndex < 0){
                m_SelectionIndex =
                    static_cast<int>(m_DialogOptions.size()) - 1;
            }
        }

        if (inputState.downPressed){
            m_SelectionIndex++;

            if (m_SelectionIndex >= static_cast<int>(m_DialogOptions.size())){
                m_SelectionIndex = 0;
            }
        }

        if (inputState.action){
            std::string nextNode = m_DialogOptions[m_SelectionIndex].next;
            LoadNode(nextNode);
        }

        return;
    }

    if (inputState.action){
        if (!m_Dialogue.contains(m_CurrentNode)){
            LOG("Current dialogue node does not exist");
            return;
        }

        const nlohmann::json& node = m_Dialogue.at(m_CurrentNode);

        if (node.contains("next")){
            std::string nextNode = node.at("next").get<std::string>();
            LoadNode(nextNode);
            return;
        }

        if (node.contains("action")){
            std::string action = node.at("action").get<std::string>();
            HandleNodeAction(action);
        }
    }
}


void DialogWindow::Start(Player* player, NPC* npc){
    if (player == nullptr){
        LOG("DialogWindow received null Player");
        return;
    }

    if (npc == nullptr){
        LOG("DialogWindow received null NPC");
        return;
    }

    m_CanDraw = true;
    m_CanExit = false;
    m_SelectionIndex = 0;

    // m_Rect.x = player->GetRect().x;
    // m_Rect.y = player->GetRect().y;

    LoadDialog(npc->GetDialog());
}


bool DialogWindow::GetCanExit() const{
    return m_CanExit;
}


void DialogWindow::LoadDialog(const nlohmann::json& dialogue){
    m_Dialogue = dialogue;

    m_CurrentNode.clear();
    m_CurrentText.clear();
    m_DialogOptions.clear();

    m_SelectionIndex = 0;
    m_NumOfOptions = 0;

    if (!m_Dialogue.contains("start")){
        LOG("Dialogue is missing a start node");
        m_CanDraw = false;
        return;
    }

    LoadNode("start");
}


void DialogWindow::LoadNode(const std::string& nodeName){
    if (!m_Dialogue.contains(nodeName)){
        LOG(("Dialogue node not found: " + nodeName).c_str());
        return;
    }

    m_CurrentNode = nodeName;
    m_CurrentText.clear();
    m_DialogOptions.clear();
    m_SelectionIndex = 0;

    const nlohmann::json& node = m_Dialogue.at(nodeName);

  
    if (node.contains("text")){
        m_CurrentText = node.at("text").get<std::string>();
    }


    if (node.contains("options")){
        const nlohmann::json& options = node.at("options");

        for(const auto& [id, option] : options.items()){
            DialogueOption newOption = {option.at("text").get<std::string>(), option.at("next").get<std::string>()};
            m_DialogOptions.emplace_back(newOption);
        }
    }

    m_NumOfOptions = static_cast<int>(m_DialogOptions.size());
}


void DialogWindow::HandleNodeAction(const std::string& action){
    if (action == "end_dialogue"){
        m_CanDraw = false;
        m_CanExit = true;
        return;
    }

    if (action == "start_battle"){
        LOG("Start battle");

        m_CanDraw = false;
        m_CanExit = true;

        /*
            Later, this should signal your StateManager
            or BattleState to begin combat.
        */

        return;
    }

    LOG(("Unknown dialogue action: " + action).c_str());
}

std::vector<std::string> DialogWindow::WrapText(const std::string& text,
    int maxWidth,
    int fontSize
)
{
    std::vector<std::string> lines;

    std::stringstream stream(text);
    std::string word;
    std::string currentLine;

    while (stream >> word)
    {
        std::string testLine;

        if (currentLine.empty())
        {
            testLine = word;
        }
        else
        {
            testLine = currentLine + " " + word;
        }

        if (MeasureText(testLine.c_str(), fontSize) <= maxWidth)
        {
            currentLine = testLine;
        }
        else
        {
            if (!currentLine.empty())
            {
                lines.push_back(currentLine);
            }

            currentLine = word;
        }
    }

    if (!currentLine.empty())
    {
        lines.push_back(currentLine);
    }

    return lines;
}