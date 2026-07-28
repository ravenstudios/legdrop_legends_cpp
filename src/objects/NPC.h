#pragma once
#include "MainEntity.h"
#include <string>
#include <nlohmann/json.hpp>
#include <vector>

class Map;

struct Stats{
    int level;
    int exp;
    int speed;
    int power;
    int defense;
    int technique;
    int charisma;
    int luck;
    int powder_rate;
    int exp_to_give;
};

struct Attack{
    std::string name;
    int power;
    int cost;
    std::string type;
};


struct Item{
    std::string name;
    int hp;
    int mp;
    std::string type;
    std::string message;
    int qty;
};

struct Data{
    std::string name;
    std::string type;
    int hp = 50;
    int mp = 25;
    int maxHp = 100;
    int maxMp = 50;
    Stats stats; 
    std::vector<Attack> attacks; 
    std::vector<Item> items;
};


class NPC : public MainEntity{
    public:
        NPC(float x, float y, std::string path, bool canWalk);
        void Update(Map* map) override;
        nlohmann::json GetDialog() const;
        int GetBattleSpriteMaxFrames() const;
        const Data& GetData() const;
        
    private:
        
        float m_WalkDuration = 0.75f;
        float m_WaitDuration = 1.5f;
        Timer m_WalkTimer;
        Timer m_WaitTimer;

        Vector2 m_MoveDirection{0.0f, 0.0f};

        
        float m_Speed = 2;
        float RandomWalkDuration();
        float RandomWaitDuration();
        bool m_IsWalking = false;
        bool m_CanWalk = true;
        void ChooseRandomMovement();
        void StopMoving();
        void LoadNPC(std::string& npcType);
        std::string GetNPC(const std::string& npcName);
        nlohmann::json m_Dialogue;
        // std::string m_Name;
        // std::string m_Class;
        // std::string m_BattleSprite;

        int m_BattleSpriteMaxFrames;
         
        int m_HP;
        int m_MP;
        Data m_Data;

};      

