#include "BattleUI.h"
#include "../Constants.h"


BattleUI::BattleUI(Player* player)
    :m_Player(player),
    m_PlayerAnimationTimer(m_AnimationSpeed),
    m_CpuAnimationTimer(m_AnimationSpeed),
    m_PlayerHealthBar(m_PlayerHealthBarRect),
    m_CpuHealthBar(m_CpuHealthBarRect),
    m_BattleDialog(m_DialogRect, player),
    m_BattleMenu(m_MenuRect, player)
{
    m_PlayerTexture = LoadTexture(m_Player->GetCurrentWrestler()->GetBattleImagePath().c_str());
    m_PlayerMaxFrames = m_Player->GetCurrentWrestler()->GetBattleSpriteMaxFrames();
}


void BattleUI::SetPlayerTexture(NPC* currentWrestler){
    m_PlayerTexture = LoadTexture(currentWrestler->GetBattleImagePath().c_str());
    m_PlayerMaxFrames = currentWrestler->GetBattleSpriteMaxFrames();
}

void BattleUI::SetNPCTexture(NPC* npc){
    m_NPCTexture = LoadTexture(npc->GetBattleImagePath().c_str());
    m_CpuMaxFrames = npc->GetBattleSpriteMaxFrames();
}

BattleUI::~BattleUI(){
    UnloadTexture(m_PlayerTexture);
    if (m_NPCTexture.id != 0) {
        UnloadTexture(m_NPCTexture);
    }
}


void BattleUI::Update(){
    Animate();
    m_PlayerHealthBar.Update();
    m_CpuHealthBar.Update();
    m_BattleDialog.Update();
    m_BattleMenu.Update();
}


void BattleUI::Draw(){
    if(m_CanAnimateAttack){
        AnimateAttack();
    }

    if(m_CanAnimateHit){
        AnimateHit();
    }

    Rectangle source{m_SpriteSize * m_PlayerFrame, 0.0f, m_SpriteSize, m_SpriteSize};
    DrawTexturePro(m_PlayerTexture, source, m_PlayerSpriteRect, Vector2{0.0f, 0.0f}, 0.0f, WHITE);
    if(m_NPC){
        Rectangle source{m_SpriteSize * m_CpuFrame, 0.0f, m_SpriteSize, m_SpriteSize};
        DrawTexturePro(m_NPCTexture, source, m_CPUSpriteRect, Vector2{0.0f, 0.0f}, 0.0f, WHITE);
    }
    m_PlayerHealthBar.Draw();
    m_CpuHealthBar.Draw();
    m_BattleDialog.Draw();
    m_BattleMenu.Draw();
}

void BattleUI::AnimateAttack(){
    if(m_NPCToAnimateAttack == NPCToAnimate::Player){
        if(!m_ReverseAttackAnimation){
                m_PlayerSpriteRect.x += m_AttackAnimationSpeed;
                m_PlayerSpriteRect.y -= m_AttackAnimationSpeed;
            
            if(m_PlayerSpriteRect.x >= m_DestPlayerSpriteRect.x && m_PlayerSpriteRect.y <= m_DestPlayerSpriteRect.y ){
                m_ReverseAttackAnimation = true;
            }
        }
        else{
            m_PlayerSpriteRect.x -= m_AttackAnimationSpeed;
            m_PlayerSpriteRect.y += m_AttackAnimationSpeed;

            if(m_PlayerSpriteRect.x <= m_OriginalPlayerSpriteRect.x && m_PlayerSpriteRect.y >= m_OriginalPlayerSpriteRect.y ){
                m_ReverseAttackAnimation = false;
                m_CanAnimateAttack = false;
                m_NPCToAnimateHit = NPCToAnimate::Cpu;
                m_CanAnimateHit = true;
                m_PlayerSpriteRect = m_OriginalPlayerSpriteRect;
            }
        }
    }
    else{
        if(!m_ReverseAttackAnimation){
                m_CPUSpriteRect.x -= m_AttackAnimationSpeed;
                m_CPUSpriteRect.y += m_AttackAnimationSpeed;
            
            if(m_CPUSpriteRect.x <= m_DestCPUSpriteRect.x && m_CPUSpriteRect.y >= m_DestCPUSpriteRect.y ){
                m_ReverseAttackAnimation = true;
            }
        }
        else{
            m_CPUSpriteRect.x += m_AttackAnimationSpeed;
            m_CPUSpriteRect.y -= m_AttackAnimationSpeed;

            if(m_CPUSpriteRect.x >= m_OriginalCPUSpriteRect.x && m_CPUSpriteRect.y <= m_OriginalCPUSpriteRect.y ){
                m_ReverseAttackAnimation = false;
                m_CanAnimateAttack = false;
                m_NPCToAnimateHit = NPCToAnimate::Player;
                m_CanAnimateHit = true;
                m_CPUSpriteRect = m_OriginalCPUSpriteRect;
            }
        }
    }    
}


void BattleUI::AnimateHit(){
    if(m_NPCToAnimateHit == NPCToAnimate::Player){
        if(m_CurrentShakeFrame < m_MaxShakeFrames){
        
            m_PlayerSpriteRect.x += GetRandomValue(-m_ShakeIntensity, m_ShakeIntensity);
            m_PlayerSpriteRect.y += GetRandomValue(-m_ShakeIntensity, m_ShakeIntensity);
            m_CurrentShakeFrame++;
        }
        else{
            m_PlayerSpriteRect = m_OriginalPlayerSpriteRect;
            m_CanAnimateHit = false;
            m_CurrentShakeFrame = 0;
        }
    }
    else{
        if(m_CurrentShakeFrame < m_MaxShakeFrames){
        
            m_CPUSpriteRect.x += GetRandomValue(-m_ShakeIntensity, m_ShakeIntensity);
            m_CPUSpriteRect.y += GetRandomValue(-m_ShakeIntensity, m_ShakeIntensity);
            m_CurrentShakeFrame++;
        }
        else{
            m_CPUSpriteRect = m_OriginalCPUSpriteRect;
            m_CanAnimateHit = false;
            m_CurrentShakeFrame = 0;
        }
    }
} 



void BattleUI::Animate(){
    m_PlayerAnimationTimer.Update(GetFrameTime());
    m_CpuAnimationTimer.Update(GetFrameTime());

    if(m_PlayerAnimationTimer.Finished()){
        m_PlayerAnimationTimer.Reset();
        m_PlayerFrame++;
        m_PlayerFrame %= m_PlayerMaxFrames;
    }

    if(!m_NPC) return;

    if(m_CpuAnimationTimer.Finished()){
        m_CpuAnimationTimer.Reset();
        m_CpuFrame++;
        m_CpuFrame %= m_CpuMaxFrames;
    }
}

void BattleUI::StartBattle(NPC* npc){
    LOG("Battle UI Start");
    if(!npc){
         LOG("NPC not loaded");
        return;
    }
    LOG("NPC loaded");
    if(m_NPCTexture.id != 0){
        UnloadTexture(m_NPCTexture);
        m_NPCTexture = {};
    }

    m_PlayerHealthBar.SetNPC(m_Player->GetCurrentWrestler());
    m_CpuHealthBar.SetNPC(npc);
    m_NPC = npc;
    m_NPCTexture = LoadTexture(m_NPC->GetBattleImagePath().c_str());
    m_CpuMaxFrames =  m_NPC->GetBattleSpriteMaxFrames();
    m_CpuFrame = 0;
    m_CpuAnimationTimer.Reset();
    m_BattleDialog.SetMessage("");
    m_BattleMenu.StartBattle();
}


BattleCommand BattleUI::UpdateInput(InputState* inputState){
    return m_BattleMenu.UpdateInput(inputState);
}

void BattleUI::SetMessage(std::string msg){
  m_BattleDialog.SetMessage(msg);
}


void BattleUI::StartAttackAnimation(NPCToAnimate npc){
    m_NPCToAnimateAttack = npc;
    m_CanAnimateAttack = true;   
}


