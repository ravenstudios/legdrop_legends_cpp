#pragma once
#include <string>
#include <vector>
#include "../Constants.h"

struct ItemData {
    std::string name;
    int hp;
    int mp;
    std::string type;
    std::string message;
    std::string discerption;

};

struct InventoryItem {
    const ItemData* item;
    int qty;
    int price;
};


const ItemData bandaid{
    "Bandaid",
    25,
    0,
    "restore_hp",
    "Player used Bandaid",
    "Restores 25 HP"
};

const ItemData beer{
    "Beer",
    0,
    25,
    "restore_mp",
    "Player used Beer",
    "Restores 25 MP"
};

const ItemData blade{
    "Blade",
    0,
    25,
    "restore_mp",
    "Player used Blade and got color",
    "Gets color and gets a buff"
};

const std::vector<const ItemData*> ALL_ITEMS{
    &bandaid,
    &beer,
    &blade
};

inline const ItemData* getItemFromString(const std::string& name){
    for(const ItemData* item :ALL_ITEMS){
        if(item->name == name) return item;
    }
    return nullptr;
}