#include "MainState.h"
#include "../Constants.h"
#include "raymath.h"


MainState::MainState()

    : m_Map("src/assets/maps/town1.tmx"),
    m_Player(0, 0)
    
{  
//    GetPlayerSpawnPoint
    m_Player.SetSpawnPoint(m_Map.GetPlayerSpawnPoint());

    m_Camera.target = m_Player.GetPosition();
    m_Camera.offset = { GAME_WIDTH / 2.0f, GAME_HEIGHT / 2.0f };
    m_Camera.rotation = 0.0f;
    m_Camera.zoom = 1.0f;
}


void MainState::Update(){
    m_Player.Update(&m_Map);

    Vector2 target = m_Player.GetPosition();

    float halfScreenWidth = GAME_WIDTH / 2.0f;
    float halfScreenHeight = GAME_HEIGHT / 2.0f;
    float mapPixelWidth = m_Map.GetMapSize().w * BLOCK_SIZE;
    float mapPixelHeight = m_Map.GetMapSize().h * BLOCK_SIZE;
    target.x = Clamp(
        target.x,
        halfScreenWidth,
        mapPixelWidth - halfScreenWidth
    );

    target.y = Clamp(
        target.y,
        halfScreenHeight,
        mapPixelHeight - halfScreenHeight
    );

    m_Camera.target = target;
}


void MainState::Draw(){
    BeginMode2D(m_Camera);
    m_Map.Draw();
    m_Player.Draw();
    EndMode2D();
}

