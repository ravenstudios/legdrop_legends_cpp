#pragma once
#include "MainEntity.h"


class NPC : public MainEntity{
    public:
        NPC(float x, float y, const char* path, bool canWalk);
        void Update(Map* map) override;
    private:
};      bool m_CanWalk;