#pragma once
#include "raylib.h"
#include "../Constants.h"
#include "State.h"
#include "../core/Input.h"
#include "../battle/Battle.h"
#include "../objects/Player.h"
#include "../objects/NPC.h"

class StateManager;



class BattleState : public State{
    public:
        BattleState(StateManager* stateManager);
        void Draw() override;
        void Update() override;
        void UpdateInput(InputState* inputState) override;
        void StartBattle(NPC* npc);

    private:
        StateManager* m_StateManagerPtr;
        Player* m_Player;
        Battle m_Battle;
        

};
