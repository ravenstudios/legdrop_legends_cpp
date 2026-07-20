#include "Map.h"
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

    LoadBlocking(map);

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

void Map::LoadBlocking(XMLElement* map){
    XMLElement* objectGroup = map->FirstChildElement("objectgroup");

    while (objectGroup)
    {
        const char* name = objectGroup->Attribute("name");

        if (name && std::string(name) == "Blocking"){
            XMLElement* object = objectGroup->FirstChildElement("object");

            while (object){
                m_BlockingRects.push_back({
                    object->FloatAttribute("x") * SCALE,
                    object->FloatAttribute("y") * SCALE,
                    object->FloatAttribute("width") * SCALE,
                    object->FloatAttribute("height") * SCALE
                });

                object = object->NextSiblingElement("object");
            }
        }
        if (name && std::string(name) == "Player Spawn Point"){
            XMLElement* object = objectGroup->FirstChildElement("object");
            m_PlayerSpawnPoint.x = object->FloatAttribute("x") * SCALE;
            m_PlayerSpawnPoint.y = object->FloatAttribute("y") * SCALE;
        }


        objectGroup = objectGroup->NextSiblingElement("objectgroup");
    }
}



 
       

        
        


Vector2 Map::GetPlayerSpawnPoint(){return m_PlayerSpawnPoint;}

std::vector<Rectangle> Map::GetBlockingRects(){
    return m_BlockingRects;
}