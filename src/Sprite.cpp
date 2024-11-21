#include "../include/Sprite.h"
#include "../include/Game.h"
#include <stdexcept>
#include <iostream>

Sprite::Sprite() : 
    texture(nullptr),
    width(0),
    height(0),
    frameCount(1),
    frameTime(0),
    currentFrame(0),
    frameCountW(1), 
    frameCountH(1) {
}

Sprite::Sprite(std::string file, int frameCountW, int frameCountH) : 
    texture(nullptr),
    width(0),
    height(0),
    frameCount(frameCountW * frameCountH),
    frameTime(0),
    currentFrame(0),
    frameCountW(frameCountW), 
    frameCountH(frameCountH) {
    Open(file);
}

Sprite::~Sprite() {
    if(texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

Sprite& Sprite::operator=(const Sprite& other) {
    if(this != &other) {
        if(texture != nullptr) {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
        
        width = other.width;
        height = other.height;
        frameCount = other.frameCount;
        frameTime = other.frameTime;
        currentFrame = other.currentFrame;
        frameCountW = other.frameCountW;
        frameCountH = other.frameCountH;
        clipRect = other.clipRect;
        texturePath = other.texturePath;
        
        if(!texturePath.empty()) {
            texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), texturePath.c_str());
            if(texture == nullptr) {
                throw std::runtime_error("Could not reload texture in copy");
            }
        }
    }
    return *this;
}

void Sprite::Open(std::string file) {
    std::cout << "Attempting to load texture: " << file << std::endl;
    
    texturePath = file;
    
    if(texture != nullptr) {
        std::cout << "Destroying previous texture" << std::endl;
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if(texture == nullptr) {
        std::cout << "Failed to load texture! SDL Error: " << SDL_GetError() << std::endl;
        throw std::runtime_error("Could not load texture: " + std::string(SDL_GetError()));
    }

    std::cout << "Texture loaded successfully" << std::endl;
    if(SDL_QueryTexture(texture, nullptr, nullptr, &width, &height) != 0) {
        std::cout << "Failed to query texture! SDL Error: " << SDL_GetError() << std::endl;
        throw std::runtime_error("Could not query texture: " + std::string(SDL_GetError()));
    }
    
    std::cout << "Texture size: " << width << "x" << height << std::endl;
    SetClip(0, 0, width/frameCountW, height/frameCountH);
    std::cout << "Frame size: " << width/frameCountW << "x" << height/frameCountH << std::endl;
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y) {
    if(texture == nullptr) {
        std::cout << "Attempting to render null texture" << std::endl;
        return;
    }

    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = clipRect.w;
    dstRect.h = clipRect.h;

    int result = SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect);
    if(result != 0) {
        std::cout << "Failed to render texture! SDL Error: " << SDL_GetError() << std::endl;
        std::cout << "Texture address: " << texture << std::endl;
        std::cout << "Clip rect: " << clipRect.x << "," << clipRect.y << "," << clipRect.w << "," << clipRect.h << std::endl;
        std::cout << "Dst rect: " << dstRect.x << "," << dstRect.y << "," << dstRect.w << "," << dstRect.h << std::endl;
        throw std::runtime_error("Could not render texture: " + std::string(SDL_GetError()));
    }
}

int Sprite::GetWidth() {
    return width/frameCountW;
}

int Sprite::GetHeight() {
    return height/frameCountH;
}

bool Sprite::IsOpen() {
    return texture != nullptr;
}

void Sprite::Update(float dt) {
    if(frameTime > 0) {
        SetFrame((currentFrame + 1) % frameCount);
    }
}

void Sprite::SetFrame(int frame) {
    if (frame < 0 || frame >= frameCount) return;
    
    int frameWidth = width/frameCountW;
    int frameHeight = height/frameCountH;
    
    int row = frame / frameCountW;
    int col = frame % frameCountW;
    
    SetClip(col * frameWidth, row * frameHeight, frameWidth, frameHeight);
    currentFrame = frame;
}

void Sprite::SetFrameCount(int frameCountW, int frameCountH) {
    this->frameCountW = frameCountW;
    this->frameCountH = frameCountH;
    this->frameCount = frameCountW * frameCountH;
    
    if(texture != nullptr) {
        SetFrame(0);
    }
}

void Sprite::SetFrameTime(float frameTime) {
    this->frameTime = frameTime;
}