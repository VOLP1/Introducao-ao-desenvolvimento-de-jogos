#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Component.h"
#include "GameObject.h"
#include "Sound.h"
#include "Sprite.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include <string>

class Zombie : public Component {
private:
    int hitpoints;
    Sound* deathSound;  // Mudado para ponteiro

public:
    Zombie(GameObject& associated);
    ~Zombie();  // Adicionado destrutor
    
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
    void Damage(int damage);
};

#endif