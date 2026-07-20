#pragma once
#include "raylib.h"
#include <vector>
#include "Layer.h"
#include <tinyxml2.h>
#include <string>
#include "objects/NPC.h"

struct MapSize{
    int w;
    int h;
};

struct Door{
    const char* path;
    Rectangle rect;
    bool isEntrance;
    bool isExit;
};

class Map{
    public:
        Map(const char* path);
        bool LoadMap(const char* path);
        void Update();
        void Draw();
        MapSize GetMapSize() const;
        std::vector<Rectangle> GetBlockingRects();
        std::vector<Door> GetDoors();
        Vector2 GetPlayerSpawnPoint();


    private:
        const char* m_Path;
        int m_MapWidth;
        int m_MapHeight;
        int m_TileWidth;
        int m_TileHeight;
        std::vector<Layer> m_Layers;
        std::vector<Rectangle> m_BlockingRects;
        std::vector<Door> m_Doors;
        std::vector<NPC> m_NPCs;
        void LoadObjects(tinyxml2::XMLElement* map);
        Vector2 m_PlayerSpawnPoint;
        void LoadTiles(tinyxml2::XMLElement* map);
        void LoadDoors(tinyxml2::XMLElement* objectGroup);
        void LoadBlocking(tinyxml2::XMLElement* objectGroup);
        void LoadNPCs(tinyxml2::XMLElement* objectGroup);


};