#include "Sound.h"
#include <stdexcept>
#include <Resources.h>

Sound::Sound() : chunk(nullptr), channel(-1) {
}

Sound::Sound(std::string file) : chunk(nullptr), channel(-1) {
    Open(file);
}

Sound::~Sound() {
    if (chunk != nullptr) {
        Stop();
        Mix_FreeChunk(chunk);
    }
}

void Sound::Play(int times) {
    if (chunk != nullptr) {
        channel = Mix_PlayChannel(-1, chunk, times - 1);
        if (channel == -1) {
            throw std::runtime_error("Unable to play sound: " + std::string(Mix_GetError()));
        }
    }
}

void Sound::Stop() {
    if (chunk != nullptr && channel != -1) {
        Mix_HaltChannel(channel);
    }
}

void Sound::Open(std::string file) {
    chunk = Resources::GetSound(file);
    if (chunk == nullptr) {
        throw std::runtime_error("Unable to load sound file: " + file + " - " + Mix_GetError());
    }
}

bool Sound::IsOpen() {
    return chunk != nullptr;
}