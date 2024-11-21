#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "Component.h"
#include "GameObject.h"
#include "Sprite.h"
#include <string>
#include <memory>

class SpriteRenderer : public Component {
public:
    SpriteRenderer(GameObject& associated);
    SpriteRenderer(GameObject& associated, std::string file, int frameCountW = 1, int frameCountH = 1);
    
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
    void Open(std::string file);
    void SetFrameCount(int frameCountW, int frameCountH);
    void SetFrameTime(float frameTime);
    void SetFrame(int frame);
    
private:
    Sprite sprite;
};

#endif