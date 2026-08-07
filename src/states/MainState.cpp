#include "../Constants.h"
#include "MainState.h"
#include "raymath.h"
#include "../dialog/DialogWindow.h"
#include "../core/Input.h"
#include "../StateManager.h"


MainState::MainState(StateManager* stateManager)
    : m_Player(stateManager->GetPlayer()),
    m_Map("src/assets/maps/town1.tmx", m_Player),
    m_DialogWindow(),
    m_StageManagerPtr(stateManager)
    
{
    m_Player->SetSpawnPoint(m_Map.GetPlayerSpawnPoint());

    m_Camera.target = m_Player->GetPosition();
    m_Camera.offset = {GAME_WIDTH / 2.0f, GAME_HEIGHT / 2.0f};
    m_Camera.rotation = 0.0f;
    m_Camera.zoom = 1.0f;

    LoadMusic();
}


void MainState::Update(){
    m_Map.Update();
    m_Player->Update(&m_Map);
    Camera();

    if (m_Player->GetMapChanged()){
        LoadMusic();
    }
}


void MainState::BackFromOtherState(){
    LoadMusic();
}


void MainState::LoadMusic(){
    SoundManager& soundManager =
            m_StageManagerPtr->GetSoundManager();

        soundManager.LoadFile(m_Map.GetSongFile());
        soundManager.Play();
}


void MainState::Draw(){
    
    BeginMode2D(m_Camera);
    m_Map.Draw();
    m_Player->Draw();
   
    EndMode2D();
    m_DialogWindow.Draw();
    
}


void MainState::Camera(){
    Vector2 target = m_Player->GetPosition();

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


void MainState::UpdateInput(InputState* inputState){
    switch (m_CurrentInputMode){
        case InputMode::World:
            WorldInput(inputState);

        case InputMode::Battle:
            break;
        
        case InputMode::Dialog:
           DialogInput(inputState);
        
        default:
            break;
    }
}


void MainState::WorldInput(InputState* inputState){
    m_Player->Input(inputState);

    if (inputState->action){
        
        m_Player->Talk();
        NPC* npc = m_Player->GetCurrentNPC();
        

        if(npc){
            npc->SetInDialog(true);
            m_Player->ClearInput();
            m_DialogWindow.Start(m_Player, m_Player->GetCurrentNPC());
            m_CurrentInputMode = InputMode::Dialog;
        }
    }
}

void MainState::DialogInput(InputState* inputState){
    DialogAction dialogAction = m_DialogWindow.Input(inputState);

    if(dialogAction == DialogAction::Exit){
        m_CurrentInputMode = InputMode::World;
        NPC* npc = m_Player->GetCurrentNPC();
        if(npc)npc->SetInDialog(false);
    }
    
    if(dialogAction == DialogAction::Battle){
        m_DialogWindow.ClearAction();
        m_CurrentInputMode = InputMode::World;
        m_StageManagerPtr->SwitchToBattleState();
    }
    if(dialogAction == DialogAction::Heal){
        LOG("heal action");
        NPC* wrestler = m_Player->GetCurrentWrestler();
        Data data = wrestler->GetData();
        wrestler->AdjustHP(data.maxHp);
        wrestler->AdjustMP(data.maxMp);

        const auto& roster = m_Player->GetRoster();
    
        for (int i = 0; i < roster.size(); i++){
            NPC& npc = *roster[i];
            npc.AdjustHP(data.maxHp);
            npc.AdjustMP(data.maxMp);
        }
    }
    if(dialogAction == DialogAction::Store){
        m_StageManagerPtr->SwitchToStoreState();
    }

}