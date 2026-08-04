#include "SoundManager.h"
#include "../Constants.h"

SoundManager::SoundManager()
    :m_Song{},
    m_SongLoaded(false)
{
    InitAudioDevice();
}


SoundManager::~SoundManager(){
    UnloadMusicStream(m_Song);
    CloseAudioDevice();
}


void SoundManager::LoadFile(std::string path){
    LOG(path);
    UnloadMusicStream(m_Song);
    std::string file = "src/assets/music/" + path;
    m_Song = LoadMusicStream(file.c_str());
    m_SongLoaded = true;
}


void SoundManager::Update(){
    if(!m_SongLoaded) return;
    UpdateMusicStream(m_Song);
}


void SoundManager::Play(){
    PlayMusicStream(m_Song);
}


void SoundManager::Stop(){

}


void SoundManager::Pause(){

}


void SoundManager::SetLevel(){

}

