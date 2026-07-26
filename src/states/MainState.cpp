#include "MainState.h"
#include "../Constants.h"
#include "raymath.h"
#include "../dialog/DialogWindow.h"
#include "../core/Input.h"


MainState::MainState()
    : m_Map("src/assets/maps/town1.tmx"),
      m_Player(0, 0),
      m_DialogWindow(),
      m_Input()
{
    m_Player.SetSpawnPoint(m_Map.GetPlayerSpawnPoint());

    m_Camera.target = m_Player.GetPosition();
    m_Camera.offset = {GAME_WIDTH / 2.0f, GAME_HEIGHT / 2.0f};
    m_Camera.rotation = 0.0f;
    m_Camera.zoom = 1.0f;
}


void MainState::Update(){
    m_Map.Update();
    m_Player.Update(&m_Map);
    Camera();
    UpdateInput();
}


void MainState::Draw(){
    BeginMode2D(m_Camera);
    m_Map.Draw();
    m_Player.Draw();
    m_DialogWindow.Draw();
    EndMode2D();
}


void MainState::Camera(){
    Vector2 target = m_Player.GetPosition();

    float halfScreenWidth = GAME_WIDTH / 2.0f;
    float halfScreenHeight = GAME_HEIGHT / 2.0f;

    float mapPixelWidth = m_Map.GetMapSize().w * BLOCK_SIZE;
    float mapPixelHeight = m_Map.GetMapSize().h * BLOCK_SIZE;

    if (mapPixelWidth <= GAME_WIDTH){
        target.x = mapPixelWidth / 2.0f;
    }
    else{
        target.x = Clamp(
            target.x,
            halfScreenWidth,
            mapPixelWidth - halfScreenWidth
        );
    }

    if (mapPixelHeight <= GAME_HEIGHT){
        target.y = mapPixelHeight / 2.0f;
    }
    else{
        target.y = Clamp(
            target.y,
            halfScreenHeight,
            mapPixelHeight - halfScreenHeight
        );
    }

    m_Camera.target = target;
}


void MainState::UpdateInput(){
    m_InputState = m_Input.GetInputState();

    switch (m_CurrentInputMode){
        case InputMode::World:
            WorldInput();

        case InputMode::Battle:
            break;
        
        case InputMode::Dialog:
           DialogInput();
        
        default:
            break;
    }
}


void MainState::WorldInput(){
    m_Player.Input(m_InputState);

    if (m_InputState.action){
        
        m_Player.Talk();
        NPC* npc = m_Player.GetCurrentNPC();

        if(npc){
            m_Player.ClearInput();
            m_DialogWindow.Start(&m_Player, m_Player.GetCurrentNPC());
            m_CurrentInputMode = InputMode::Dialog;
        }
    }
}

void MainState::DialogInput(){
    m_DialogWindow.Input(m_InputState);

    if(m_DialogWindow.GetCanExit())m_CurrentInputMode = InputMode::World;
}