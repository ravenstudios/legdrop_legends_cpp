#pragma once
#include "MainEntity.h"
#include "NPC.h"
#include "../core/Input.h"
#include "Items.h"
class NPC;
class Map;

class Map;

class Player : public MainEntity{
    public:
        Player();
        void Update(Map* map) override;
        void Draw() override;
        void Input(InputState* inputState);
        bool GetInDialog() const;
        void Talk();
        void ClearInput();
        void UseItem(int index);
       
        Rectangle GetTalkHitBox();
        NPC* GetCurrentNPC();
        NPC* GetCurrentWrestler();
        std::vector<std::unique_ptr<NPC>>& GetRoster();
        void SetCurrentWrestler(int index);
        const std::vector<InventoryItem>& GetItems() const;
        void AdjustItemQty(int index, int qty);
        const int GetMoney() const;
        void AdjustMoney(int money);
        void AddItem(const ItemData* item, int qty);
        bool GetMapChanged();


    private:
        void Walk();
        void CheckDoorCollision();
        Vector2 m_LastPOS;
        bool m_IsTalking = false;
        bool m_InDialog = false;
        Rectangle m_TalkHitBox;
        Map* m_Map;
        NPC* m_CurrentNPC = nullptr;
        
        int m_RosterIndex = 0;
        std::vector<std::unique_ptr<NPC>> m_Roster;
        std::unique_ptr<NPC> m_CurrentWrestler;
        std::vector<InventoryItem> m_Items{
            {&bandaid, 3},
            {&beer, 2}
        };
        int m_Money = 100;
        bool m_MapChanged = false;




};
