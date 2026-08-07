#pragma once
#include <iostream>
#include <filesystem>

constexpr int TICK_RATE = 60;

constexpr int SCALE = 4;
constexpr int ROWS = 256;
constexpr int COLS = 192;
constexpr int GAME_WIDTH = ROWS * SCALE;
constexpr int GAME_HEIGHT = COLS * SCALE;
constexpr int BLOCK_SIZE = GAME_WIDTH  / 16;


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