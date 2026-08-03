#include "NPC.h"
#include "../Map.h"
#include <unordered_map>
#include <string>
#include <tinyxml2.h>
#include <fstream>


NPC::NPC(float x, float y, std::string npcType, bool canWalk)  
    : MainEntity("", x, y),
   
    m_WalkTimer(m_WalkDuration),
    m_WaitTimer(m_WaitDuration),
    m_CanWalk(canWalk)
{
    //  m_WaitTimer.Start();
    LoadNPC(npcType);
    StopMoving();
    m_WaitTimer.SetDuration(RandomWalkDuration());
    m_WaitTimer.Reset();
    
}


void NPC::Update(Map* map){
    MainEntity::Update(map);
    if(!m_CanWalk){
        StopMoving();

        return;
    }

    float deltaTime = GetFrameTime();
    m_WalkTimer.Update(deltaTime);
    m_WaitTimer.Update(deltaTime);

    if(m_IsWalking){
        m_CanAnimate = true;
        if(m_Directions.up){
            m_Direction = 1;
            Move(0, -m_Speed);
        }
        if(m_Directions.right){
            m_Direction = 2;
            Move(m_Speed, 0);
        }
        if(m_Directions.down){
            m_Direction = 0;
            Move(0, m_Speed);
        }
        if(m_Directions.left){
            m_Direction = 3;
            Move(-m_Speed, 0);
        }

        m_AnimationTimer.SetPause(false);

        if(m_WalkTimer.Finished()){
            m_IsWalking = false;
            StopMoving();
            m_WaitTimer.SetDuration(RandomWalkDuration());
            m_WaitTimer.Reset();
        }
    }
    else{
        if(m_WaitTimer.Finished()){
            ChooseRandomMovement();

            m_IsWalking = true;
            m_WalkTimer.SetDuration(RandomWalkDuration());
            m_WalkTimer.Reset();
        }
    }

    
}


void NPC::ChooseRandomMovement(){
    int direction = GetRandomValue(0, 3);

    switch (direction){
        case 0:
            m_Directions.up = true;
            m_Directions.down = false;
            m_Directions.left = false;
            m_Directions.right = false;
            break;

        case 1:
            m_Directions.up = false;
            m_Directions.down = true;
            m_Directions.left = false;
            m_Directions.right = false;
            break;

        case 2:
            m_Directions.up = false;
            m_Directions.down = false;
            m_Directions.left = true;
            m_Directions.right = false;
            break;

        case 3:
            m_Directions.up = false;
            m_Directions.down = false;
            m_Directions.left = false;
            m_Directions.right = true;
            break;
    }
}

void NPC::StopMoving(){
    m_CanAnimate = false;
    m_Directions.up = false;
    m_Directions.down = false;
    m_Directions.left = false;
    m_Directions.right = false;
}


float NPC::RandomWalkDuration(){
    return static_cast<float>(GetRandomValue(100, 200)) / 100.0f;
}


float NPC::RandomWaitDuration(){
    return static_cast<float>(GetRandomValue(150, 300)) / 100.0f;
}


void NPC::LoadNPC(std::string& npcType){
    using json = nlohmann::json;

    std::ifstream file(GetNPC(npcType));
    if(!file.is_open()){
        return;
    }

    json data;

    try{
        file >> data;
    
        std::string sprite = "src/assets/images/" + data["sprite"].get<std::string>();
        m_Texture = LoadTexture(sprite.c_str());
        std::string battleSprite = "src/assets/images/" + data["battle_sprite"].get<std::string>();
        m_BattleImagePath = battleSprite;
        m_BattleSpriteMaxFrames = data["max_frame"];
        m_Dialogue = data["dialog"];
        m_Data.name = data["name"];
        m_Data.type = data["class"];
        

        if(data.contains("stats")){
            auto& jStats = data["stats"];
            m_Data.stats.level       = static_cast<int>(jStats["level"]);
            m_Data.stats.exp         = static_cast<int>(jStats["exp"]);
            m_Data.stats.speed       = static_cast<int>(jStats["speed"]);
            m_Data.stats.power       = static_cast<int>(jStats["power"]);
            m_Data.stats.defense     = static_cast<int>(jStats["defense"]);
            m_Data.stats.technique   = static_cast<int>(jStats["technique"]);
            m_Data.stats.charisma    = static_cast<int>(jStats["charisma"]);
            m_Data.stats.luck        = static_cast<int>(jStats["luck"]);
            m_Data.stats.powder_rate = static_cast<int>(jStats["powder_rate"]);
            m_Data.stats.exp_to_give = static_cast<int>(jStats["exp_to_give"]);
        }

        
        if(data.contains("items")){
            const auto& items = data["items"];


            for (const auto& item : items){
                const ItemData* itemData = getItemFromString(item["name"].get<std::string>());
                if(itemData){
                    m_Items.emplace_back(InventoryItem{itemData, 0, item["price"].get<int>()});
                }
            }
        }

        if(data.contains("attacks")){
            auto& attacks = data["attacks"];

            for (const auto& attack : attacks){
                std::string name = attack["name"];
                int power = attack["power"];
                int cost = attack["cost"];
                std::string type = attack["type"];

                Attack a{name, power, cost, type};
            m_Data.attacks.emplace_back(a);
            }
        }
        
    }
    catch (const json::parse_error& e){
        LOG(e.what());
        return;
    }
}


std::string NPC::GetNPC(const std::string& npcName){
    static const std::unordered_map<std::string, std::string> npcImages = {
        {"angel", "angel.json"},
        {"bad_jim", "bad_jim.json"},
        {"crawdaddy", "crawdaddy.json"},
        {"brother", "brother.json"},
        {"clown", "clown.json"},
        {"mr_murica", "mr_murica.json"},
        {"nurse", "nurse.json"},
        {"clerk", "clerk.json"},
        {"punching_bag", "punching_bag.json"}
    };

    auto found = npcImages.find(npcName);

    if(found == npcImages.end()){
        return "src/assets/wrestlers/brother.json";
    }
    std::string path = "src/assets/wrestlers/" + found->second;
    return path;
}


nlohmann::json NPC::GetDialog() const{
    return m_Dialogue;
}


int NPC::GetBattleSpriteMaxFrames() const{
    return m_BattleSpriteMaxFrames;
}


const Data& NPC::GetData() const{
    return m_Data;
}


void NPC::AdjustHP(int hp){
    m_Data.hp += hp;
    if(m_Data.hp > m_Data.maxHp) m_Data.hp = m_Data.maxHp;
}


void NPC::AdjustMP(int mp){
    m_Data.mp += mp;
    if(m_Data.mp > m_Data.maxMp) m_Data.mp = m_Data.maxMp;
}


bool NPC::CanAttack(){
    for(const Attack& attack : m_Data.attacks){
        if(m_Data.mp >= attack.cost){
            return true;
        }
    }
    return false;
}

const std::vector<InventoryItem>& NPC::GetItems() const{
  return m_Items;
}