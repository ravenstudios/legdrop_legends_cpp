#pragma once
#include "raylib.h"
#include <string>
#include <vector>
#include "Constants.h"

struct TileLayer{
    std::string name;
    std::vector<int> tiles;
};

struct TileSet{
    int firstGid;
    int columns;
    Texture2D texture;
};




class Layer{
    public:
        Layer(int mapWidth, int mapHeight);
        void Draw();
        void DrawTile(int gid, int mapX, int mapY);
        void LoadLayer(TileLayer layer);
        void AddTileSet(TileSet ts);

    private:
        std::vector<TileSet> m_TileSets;
        int m_MapWidth = 0;
        int m_MapHeight = 0;
        int m_TileWidth = BLOCK_SIZE / 4;
        int m_TileHeight = BLOCK_SIZE / 4;
        std::vector<TileLayer> m_Layers;
        
};