#pragma once
#include "raylib.h"
#include <vector>
#include "Layer.h"


class Map{
    public:
        Map(const char* path);
        void LoadMap();
        void Update();
        void Draw();

    private:
        const char* m_Path;
        int m_MapWidth;
        int m_MapHeight;
        int m_TileWidth;
        int m_TileHeight;
        std::vector<Layer> m_Layers;
        std::vector<Rectangle> m_BlockingRects;
        // std::vector<Door> m_Doors;
        // std::vector<NPCSpawn> m_NPCs;



};