#include "Map.h"
#include "Constants.h"
#include <sstream>
 #include <filesystem>


using namespace tinyxml2;

Map::Map(const char* path){
    LoadMap(path);
}


bool Map::LoadMap(const char* path){
    m_Layers.clear();
    m_BlockingRects.clear();
    m_Doors.clear();
    m_Path = path;
    XMLDocument doc;

    if (doc.LoadFile(m_Path) != XML_SUCCESS){
        LOG("Failed to load map");
        LOG(doc.ErrorStr());
        return false;
    }

    XMLElement* map = doc.FirstChildElement("map");

    
    LoadTiles(map);
    LoadObjects(map);

    m_MapWidth = map->IntAttribute("width");
    m_MapHeight = map->IntAttribute("height");
    m_TileWidth = map->IntAttribute("tilewidth");
    m_TileHeight = map->IntAttribute("tileheight");
    return true;
}


void Map::LoadTiles(XMLElement* map){
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

void Map::LoadObjects(XMLElement* map){
    LOG("**************************** LOAD OBJECTS*************************");
    XMLElement* objectGroup = map->FirstChildElement("objectgroup");

    while (objectGroup)
    {
        const char* name = objectGroup->Attribute("name");

        if (name && std::string(name) == "Blocking"){
            LoadBlocking(objectGroup);
        }

        if (name && std::string(name) == "Player Spawn Point"){
            LOG("******************* LOADED SP***********************************");
            XMLElement* object = objectGroup->FirstChildElement("object");
            m_PlayerSpawnPoint.x = object->FloatAttribute("x") * SCALE;
            m_PlayerSpawnPoint.y = object->FloatAttribute("y") * SCALE;
        }

        if (name && std::string(name) == "doors"){
            LoadDoors(objectGroup);
        }

        objectGroup = objectGroup->NextSiblingElement("objectgroup");
    }
}


void Map::LoadBlocking(XMLElement* objectGroup){
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


void Map::LoadDoors(XMLElement* objectGroup){
    XMLElement* object = objectGroup->FirstChildElement("object");
    
    while (object){
        Door d;

        d.rect = {
            object->FloatAttribute("x") * SCALE,
            object->FloatAttribute("y") * SCALE,
            object->FloatAttribute("width") * SCALE,
            object->FloatAttribute("height") * SCALE
        };

        XMLElement* properties = object->FirstChildElement("properties");

        if (properties){
            XMLElement* property = properties->FirstChildElement("property");

            while (property){
                const char* name = property->Attribute("name");

                if (name && std::string(name) == "map_file"){
                    d.path = property->Attribute("value");
                }
                if (name && std::string(name) == "entrance"){
                    d.isEntrance = true;
                    d.isExit = false;
                }
                if (name && std::string(name) == "exit"){
                    d.isEntrance = false;
                    d.isExit = true;
                }

                property = property->NextSiblingElement("property");
            }
        }

        m_Doors.push_back(d);

        object = object->NextSiblingElement("object");
    }
}



Vector2 Map::GetPlayerSpawnPoint(){return m_PlayerSpawnPoint;}

std::vector<Rectangle> Map::GetBlockingRects(){
    return m_BlockingRects;
}


std::vector<Door> Map::GetDoors(){    
    return m_Doors;
}