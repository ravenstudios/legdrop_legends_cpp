#include "Player.h"
#include "../Map.h"

Player::Player()
    : MainEntity("src/assets/images/manager-Sheet.png"),
    m_CurrentWrestler(std::make_unique<NPC>(0, 0, "bad_jim", false))
{
  m_Roster.emplace_back(std::make_unique<NPC>(0, 0, "brother", false));
  m_Roster.emplace_back(std::make_unique<NPC>(0, 0, "mr_murica", false));
  m_Roster.emplace_back(std::make_unique<NPC>(0, 0, "crawdaddy", false)); 
}



void Player::Update(Map* map){
    m_Map = map;
    MainEntity::Update(map);
    Walk();
    CheckDoorCollision();


}

void Player::Draw(){
    MainEntity::Draw();
    // if(m_IsTalking){
    //   DrawRectangle(m_TalkHitBox.x, m_TalkHitBox.y, m_TalkHitBox.width, m_TalkHitBox.height, RED);
    // }
}

void Player::Input(InputState* inputState){
      m_Directions.up = inputState->up;
      m_Directions.down = inputState->down;
      m_Directions.left = inputState->left;
      m_Directions.right = inputState->right;
}

void Player::ClearInput(){
      m_Directions.up = false;
      m_Directions.down = false;
      m_Directions.left = false;
      m_Directions.right = false;
      m_TalkHitBox = {};
}


void Player::Walk(){
  if (m_Directions.up){
      m_Direction = 1;
      Move(0, -1);
      m_AnimationTimer.SetPause(false);
  }
  if (m_Directions.right){
      m_Direction = 2;
      Move(1, 0);
      m_AnimationTimer.SetPause(false);
  }
  if (m_Directions.down){
      m_Direction = 0;
      Move(0, 1);
      m_AnimationTimer.SetPause(false);
  }
  if (m_Directions.left){
      m_Direction = 3;
      Move(-1, 0);
      m_AnimationTimer.SetPause(false);
  }

  bool walking =
  m_Directions.up ||
  m_Directions.down ||
  m_Directions.left ||
  m_Directions.right;

  if (walking){
      m_CanAnimate = true;
  }
  else{
      m_CanAnimate = false;
  }

}

void Player::Talk(){
  m_TalkHitBox = GetTalkHitBox();

  for (const auto& npc : m_Map->GetNPCs()) {
    if (CheckCollisionRecs(m_TalkHitBox, npc->GetRect())) {
        m_IsTalking = true;
        m_CurrentNPC = npc.get();
        return;
    }
  }
  m_CurrentNPC = nullptr;
}


void Player::CheckDoorCollision(){
  for (const Door& door : m_Map->GetDoors()){
    if (CheckCollisionRecs(m_Rect, door.rect)){
        
      std::string path = std::string("src/assets/maps/") + door.path;
      if(door.isEntrance){
        int x = static_cast<int>(door.rect.x / BLOCK_SIZE) * BLOCK_SIZE;
        int y = static_cast<int>(door.rect.y / BLOCK_SIZE) * BLOCK_SIZE;
        m_LastPOS = {static_cast<float>(x), static_cast<float>(y) + BLOCK_SIZE};
        m_Map->LoadMap(path.c_str());
        SetSpawnPoint(m_Map->GetPlayerSpawnPoint());
        m_MapChanged = true;
        return;
      }
      if(door.isExit){
        m_Map->LoadMap(path.c_str());
        SetSpawnPoint(m_LastPOS);
        m_MapChanged = true;
        return;
      }
    }
  }
}


Rectangle Player::GetTalkHitBox(){
  float w = 20;
  float h = BLOCK_SIZE / 2;
   // UP
  if(m_Direction == 1){
    return {(m_Rect.x + (m_Rect.width  / 2)) - w / 2, m_Rect.y - h, w, h};
  }
  // RIGHT
  if(m_Direction == 2){
    return {m_Rect.x + m_Rect.width, m_Rect.y + m_Rect.height / 2 - w / 2, h, w};
  }
  // DOWN
  if(m_Direction == 0){
    return {(m_Rect.x + (m_Rect.width  / 2)) - w / 2, m_Rect.y + m_Rect.height, w, h};
  }
  // LEFT
  if(m_Direction == 3){
    return {m_Rect.x - h, m_Rect.y + m_Rect.height / 2 - w / 2, h, w};
  }
  return {0, 0, 0, 0};
}


NPC* Player::GetCurrentNPC(){
  return m_CurrentNPC;
}

bool Player::GetInDialog() const{
return m_InDialog;
}

NPC* Player::GetCurrentWrestler(){
  return m_CurrentWrestler.get();
}

std::vector<std::unique_ptr<NPC>>& Player::GetRoster(){
  return m_Roster;
}

void Player::SetCurrentWrestler(int index){
  if(index >= m_Roster.size()){
    LOG("index out of bounds");
    return;
  }
  std::swap(m_CurrentWrestler, m_Roster[index]); 
}


void Player::AdjustItemQty(int index, int qty){
  LOG(index);
  m_Items[index].qty += qty;
  if(m_Items[index].qty <= 0) m_Items.erase(m_Items.begin() + index);
}

const std::vector<InventoryItem>& Player::GetItems() const{
  return m_Items;
}


void Player::UseItem(int index){
  auto item = m_Items[index];
  if(item.item->type == "restore_hp"){
    m_CurrentWrestler->AdjustHP(item.item->hp);
    AdjustItemQty(index, -1);
  }
  if(item.item->type == "restore_mp"){
    m_CurrentWrestler->AdjustMP(item.item->mp);
    AdjustItemQty(index, -1);
  }
}

const int Player::GetMoney() const{
  return m_Money;
}


void Player::AdjustMoney(int money){
  m_Money += money;
}


void Player::AddItem(const ItemData* item, int qty){
  for(auto& inventoryItem : m_Items){
      if (inventoryItem.item == item){
          inventoryItem.qty += qty;
          return;
      }
  }

  m_Items.emplace_back(InventoryItem{item, qty});
}



bool Player::GetMapChanged(){
  bool changed = m_MapChanged;
  m_MapChanged = false;
  return changed;
}