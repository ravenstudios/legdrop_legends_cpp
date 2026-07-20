#include "Player.h"


Player::Player(float x, float y)
    : MainEntity("src/assets/images/Brother16x16-Sheet.png", x, y)
{

}



void Player::Update(){
    MainEntity::Update();
    Input();
}


void Player::Input(){
    if (IsKeyDown(KEY_UP)){
        m_Direction = 1;
        Move(0, -m_Speed);
    }
    if (IsKeyDown(KEY_RIGHT)){
        m_Direction = 2;
        Move(m_Speed, 0);
    }
    if (IsKeyDown(KEY_DOWN)){
        m_Direction = 0;
        Move(0, m_Speed);
    }
    if (IsKeyDown(KEY_LEFT)){
        m_Direction = 3;
        Move(-m_Speed, 0);
    }
}

