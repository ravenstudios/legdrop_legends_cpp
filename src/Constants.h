#pragma once
#include <iostream>
#include <filesystem>

constexpr int TICK_RATE = 60;

constexpr int SCALE = 4;
constexpr int GAME_WIDTH = 256 * SCALE;
constexpr int GAME_HEIGHT = 192 * SCALE;
constexpr int BLOCK_SIZE = GAME_WIDTH  / 16;
constexpr int WORLD_WIDTH = 1500;
constexpr int WORLD_HEIGHT = 1500;



template<typename T>
inline void Log(const std::string& file, int line, const T& message)
{
    std::cout
        << '['
        << std::filesystem::path(file).filename().string()
        << ':'
        << line
        << "] "
        << message
        << '\n';
}

#define LOG(x) Log(__FILE__, __LINE__, x)