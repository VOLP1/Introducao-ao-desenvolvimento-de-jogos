#ifndef SPRITE_H
#define SPRITE_H

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include <string>

class Sprite {
public:
    Sprite();
    Sprite(std::string file, int frameCountW = 1, int frameCountH = 1);
    ~Sprite();
    Sprite& operator=(const Sprite& other);
    
    void Open(std::string file);
    void SetClip(int x, int y, int w, int h);
    void Render(int x, int y);
    int GetWidth();     // Removido o corpo da função
    int GetHeight();    // Removido o corpo da função
    bool IsOpen();      // Removido o corpo da função
    void SetFrame(int frame);
    void SetFrameCount(int frameCountW, int frameCountH);
    void SetFrameTime(float frameTime);
    void Update(float dt);

private:
    SDL_Texture* texture;
    std::string texturePath;
    int width;
    int height;
    SDL_Rect clipRect;
    int frameCount;
    float frameTime;
    int currentFrame;
    int frameCountW;
    int frameCountH;
};

#endif