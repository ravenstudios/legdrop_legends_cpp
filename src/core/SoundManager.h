#pragma once
#include "raylib.h"
#include <string>

class SoundManager{
    public:
        SoundManager();
        ~SoundManager();
        void LoadFile(std::string path);
        void Play();
        void Stop();
        void Pause();
        void SetLevel();
        void Update();




    private:
        Music m_Song;
        bool m_SongLoaded = false;
};