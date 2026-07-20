#include "Layer.h"


Layer::Layer(int mapWidth, int mapHeight){
    m_MapWidth = mapWidth;
    m_MapHeight = mapHeight;
  
}


void Layer::LoadLayer(TileLayer layer){
    m_Layers.emplace_back(layer);
}

void Layer::AddTileSet(TileSet ts){
    m_TileSets.emplace_back(ts);
}


void Layer::Draw()
{
    for (const TileLayer& layer : m_Layers)
    {
        for (int y = 0; y < m_MapHeight; y++)
        {
            for (int x = 0; x < m_MapWidth; x++)
            {
                int index = y * m_MapWidth + x;
                int gid = layer.tiles[index];

                if (gid == 0)
                    continue;

                DrawTile(gid, x, y);
            }
        }
    }
}


void Layer::DrawTile(int gid, int mapX, int mapY)
{
    TileSet* current = nullptr;

    for (TileSet& tileset : m_TileSets){
        if (gid >= tileset.firstGid)
            current = &tileset;
        else
            break;
    }

    int localID = gid - current->firstGid;

    int tilesetColumns = current->columns;

    int sourceX = (localID % tilesetColumns) * m_TileWidth;
    int sourceY = (localID / tilesetColumns) * m_TileHeight;

    Rectangle source{
        static_cast<float>(sourceX),
        static_cast<float>(sourceY),
        static_cast<float>(m_TileWidth),
        static_cast<float>(m_TileHeight)
    };

    Rectangle destination{
        static_cast<float>(mapX * BLOCK_SIZE),
        static_cast<float>(mapY * BLOCK_SIZE),
        static_cast<float>(BLOCK_SIZE),
        static_cast<float>(BLOCK_SIZE)
    };

    DrawTexturePro(
        current->texture,
        source,
        destination,
        Vector2{0, 0},
        0.0f,
        WHITE
    );
}



