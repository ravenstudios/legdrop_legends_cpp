#pragma once
#include "MainEntity.h"
#include "NPC.h"
#include "../core/Input.h"



class Map;

class Player : public MainEntity{
    public:
        Player(float x, float y);
        void Update(Map* map) override;
        void Draw() override;
        void Input(InputState inputState);
        bool GetInDialog() const;
        void Talk();
        void ClearInput();
       
        Rectangle GetTalkHitBox();
        NPC* GetCurrentNPC();

    private:
        void Walk();
        void CheckDoorCollision();
        Vector2 m_LastPOS;
        bool m_IsTalking = false;
        bool m_InDialog = false;
        Rectangle m_TalkHitBox;
        Map* m_Map;
        NPC* m_CurrentNPC;



};
