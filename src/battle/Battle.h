#pragma once
#include "../objects/Player.h"
#include "../objects/NPC.h"
#include "BattleUI.h"
#include "../core/Input.h"
#include "BattleMenuAction.h"


enum class BattleResult {
    Ongoing,
    Escaped,
    PlayerWon,
    PlayerLost
};


class Battle{
    public:
        Battle(Player* player);
        void Update();
        void Draw();
        void StartBattle(NPC* npc);
        void UpdateInput(InputState* inputState);
        BattleResult GetBattleResult();



    private:
        Player* m_Player;
        NPC* m_NPC = nullptr;
        BattleUI m_BattleUI;
        void Run();
        void Bag(int index);
        void Attack(int index);
        void Tag(int index);
        BattleResult m_BattleResult = BattleResult::Ongoing;

};
