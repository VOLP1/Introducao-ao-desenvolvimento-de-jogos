#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "Component.h"
#include "Animation.h"
#include <string>
#include <unordered_map>

class Animator : public Component {
private:
    std::unordered_map<std::string, Animation> animations;
    int frameStart;
    int frameEnd;
    float frameTime;
    int currentFrame;
    float timeElapsed;
    
public:
    Animator(GameObject& associated);
    
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
    
    void SetAnimation(std::string name);
    void AddAnimation(std::string name, Animation anim);
};

#endif