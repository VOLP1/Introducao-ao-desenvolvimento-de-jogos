#include "../include/Zombie.h"
#include "../include/Sprite.h"
#include "../include/GameObject.h"
#include "../include/SpriteRenderer.h"
#include "../include/Animator.h"
#include "../include/Animation.h"
#include <iostream>

Zombie::Zombie(GameObject& associated) : Component(associated), hitpoints(100) {
    std::cout << "Creating Zombie..." << std::endl;
    
    // Criar e configurar o SpriteRenderer
    SpriteRenderer* renderer = new SpriteRenderer(associated, "recursos/img/Enemy.png", 3, 2);
    associated.AddComponent(renderer);
    
    // Criar e configurar o Animator
    Animator* anim = new Animator(associated);
    anim->AddAnimation("walking", Animation(0, 3, 0.1f));
    anim->AddAnimation("dead", Animation(5, 5, 0.0f));
    anim->SetAnimation("walking");
    associated.AddComponent(anim);
    
    std::cout << "Zombie created" << std::endl;
}

Zombie::~Zombie() {
}

void Zombie::Damage(int damage) {
    // Só toma dano se ainda estiver vivo
    if (hitpoints > 0) {
        hitpoints -= damage;
        
        if(hitpoints <= 0) {
            hitpoints = 0;  // Garante que não fique negativo
            auto* anim = (Animator*)associated.GetComponent("Animator");
            if(anim) {
                anim->SetAnimation("dead");
                std::cout << "Zombie died!" << std::endl;
            }
        }
    }
}

void Zombie::Update(float dt) {
    // Só perde vida se ainda estiver vivo
    if (hitpoints > 0) {
        Damage(1);
    }
}

void Zombie::Render() {
    // Renderização é feita pelo SpriteRenderer
}

bool Zombie::Is(std::string type) {
    return type == "Zombie";
}