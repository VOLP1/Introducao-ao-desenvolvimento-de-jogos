#include "../include/Music.h"
#include <stdexcept>

Music::Music() : music(nullptr) {
}

Music::Music(std::string file) : music(nullptr) {
    Open(file);
}

Music::~Music() {
    Stop(0);
    if(music != nullptr) {
        Mix_FreeMusic(music);
    }
}

void Music::Play(int times) {
    if(music != nullptr) {
        Mix_PlayMusic(music, times);
    }
}

void Music::Stop(int msToStop) {
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(std::string file) {
    music = Mix_LoadMUS(file.c_str());
    if(music == nullptr) {
        throw std::runtime_error("Could not load music: " + std::string(Mix_GetError()));
    }
}

bool Music::IsOpen() {
    return music != nullptr;
}