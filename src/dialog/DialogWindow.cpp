#include "DialogWindow.h"


void DialogWindow::Update(){
    
}


void DialogWindow::Draw(){
    if(!m_CanDraw)return;
    int fs = 50;
    DrawRectangleRec(m_Rect, m_Color);
    DrawText("Option 1", m_Rect.x, m_Rect.y + (fs * 0), 50, BLACK);
    DrawText("Option 2", m_Rect.x, m_Rect.y + (fs * 1), fs, BLACK);
    DrawText("Option 3", m_Rect.x, m_Rect.y + (fs * 2), fs, BLACK);
    DrawText("Exit", m_Rect.x, m_Rect.y + (fs * 3), fs, BLACK);
    Rectangle selectionRect = {m_Rect.x, m_Rect.y + (fs * m_SelectionIndex), m_Rect.width, static_cast<float>(fs)};
    DrawRectangleLinesEx(selectionRect, 5,  BLACK);
    
}

void DialogWindow::Input(InputState inputState){
    if(inputState.upPressed){
        m_SelectionIndex--;
        if(m_SelectionIndex < 0) m_SelectionIndex = m_NumOfOptions;
    }

    if(inputState.downPressed){
        m_SelectionIndex++;
        if(m_SelectionIndex > m_NumOfOptions)m_SelectionIndex = 0;
    }

    if(inputState.action && m_SelectionIndex == m_NumOfOptions){
        m_CanExit = true;
        m_CanDraw = false;
    }

    
}


void DialogWindow::Show(){
    m_CanDraw = true;
}


void DialogWindow::Hide(){
    m_CanDraw = false;
}

void DialogWindow::Start(Player* player, NPC* npc){
    m_CanDraw = true;
    m_CanExit = false;
    m_SelectionIndex = 0;
    m_Rect.y = player->GetRect().y;
    m_Rect.x = player->GetRect().x;

}

bool DialogWindow::GetCanExit() const{
    return m_CanExit;
}