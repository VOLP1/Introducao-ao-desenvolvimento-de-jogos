#include "../include/Sprite.h"
#include "../include/Game.h"
#include <stdexcept>

Sprite::Sprite() : texture(nullptr) {
    width = 0;
    height = 0;
}

Sprite::Sprite(std::string file) : texture(nullptr) {
    Open(file);
}

Sprite::~Sprite() {
    if(texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Open(std::string file) {
    if(texture != nullptr) {
        SDL_DestroyTexture(texture);
    }

    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if(texture == nullptr) {
        throw std::runtime_error("Could not load texture: " + std::string(SDL_GetError()));
    }

    if(SDL_QueryTexture(texture, nullptr, nullptr, &width, &height) != 0) {
        throw std::runtime_error("Could not query texture: " + std::string(SDL_GetError()));
    }

    SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y) {
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = clipRect.w;
    dstRect.h = clipRect.h;

    if(SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect) != 0) {
        throw std::runtime_error("Could not render texture: " + std::string(SDL_GetError()));
    }
}

int Sprite::GetWidth() {
    return width;
}

int Sprite::GetHeight() {
    return height;
}

bool Sprite::IsOpen() {
    return texture != nullptr;
}