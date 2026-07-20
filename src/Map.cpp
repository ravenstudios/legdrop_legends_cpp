#include "Map.h"
#include <tinyxml2.h>
#include "Constants.h"
#include <sstream>
 #include <filesystem>


using namespace tinyxml2;

Map::Map(const char* path){
    m_Path = path;
    LoadMap();
}


void Map::LoadMap(){
    XMLDocument doc;

    if (doc.LoadFile(m_Path) != XML_SUCCESS){
        LOG("Failed to load map");
        return;
    }

    XMLElement* map = doc.FirstChildElement("map");

    m_MapWidth = map->IntAttribute("width");
    m_MapHeight = map->IntAttribute("height");
    m_TileWidth = map->IntAttribute("tilewidth");
    m_TileHeight = map->IntAttribute("tileheight");

    

    for(XMLElement* layer = map->FirstChildElement("layer");
        layer != nullptr;
        layer = layer->NextSiblingElement("layer")
    ){

        
        

        Layer newLayer = Layer(
            map->IntAttribute("width"),
            map->IntAttribute("height")
        );


        for (XMLElement* tileset = map->FirstChildElement("tileset");
            tileset != nullptr;
            tileset = tileset->NextSiblingElement("tileset"))
        {
            XMLElement* image = tileset->FirstChildElement("image");

            if (image == nullptr) {
                LOG("Tileset has no image");
                continue;
            }

            const char* imageSource = image->Attribute("source");

            if (imageSource == nullptr) {
                LOG("Tileset image has no source");
                continue;
            }

            TileSet ts;

            ts.firstGid = tileset->IntAttribute("firstgid");
            ts.columns = tileset->IntAttribute("columns");
           

            std::filesystem::path source = image->Attribute("source");
            std::filesystem::path texturePath;

            if (source.is_absolute() || FileExists(source.string().c_str())) {
                // Already valid relative to the project working directory
                texturePath = source;
            }
            else {
                // Relative to the TMX file
                texturePath =
                    std::filesystem::path(m_Path).parent_path() / source;
            }

texturePath = texturePath.lexically_normal();

ts.texture = LoadTexture(texturePath.string().c_str());

            newLayer.AddTileSet(ts);
        }

        // XMLElement* layer =
        //     map->FirstChildElement("layer");

        XMLElement* data =
            layer->FirstChildElement("data");

        const char* csv = data->GetText();

        TileLayer tileLayer;
        tileLayer.name = layer->Attribute("name");
        

        std::stringstream ss(csv);
        std::string value;

        while (std::getline(ss, value, ',')) {
            int id = std::stoi(value);
            tileLayer.tiles.push_back(id);
        }
        
        newLayer.LoadLayer(tileLayer);
        m_Layers.emplace_back(newLayer);
    }
    
}


void Map::Update(){

}


void Map::Draw(){
    for(Layer& layer : m_Layers){
        layer.Draw();
    }
}

MapSize Map::GetMapSize() const{
    return {m_MapWidth, m_MapHeight};
}