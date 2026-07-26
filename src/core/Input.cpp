#include "Input.h"

Input::Input(){

}


void Input::Update(){
    m_InputState.up = IsKeyDown(KEY_W);
    m_InputState.down = IsKeyDown(KEY_S);
    m_InputState.left = IsKeyDown(KEY_A);
    m_InputState.right = IsKeyDown(KEY_D);

    m_InputState.upPressed = IsKeyPressed(KEY_W);
    m_InputState.downPressed = IsKeyPressed(KEY_S);
    m_InputState.action = IsKeyPressed(KEY_SPACE);
    m_InputState.cancel = IsKeyPressed(KEY_Z);
}


InputState Input::GetInputState(){
    Update();
    return m_InputState;
}

