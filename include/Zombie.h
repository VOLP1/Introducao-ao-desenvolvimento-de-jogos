#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Component.h"
#include "GameObject.h"

class Zombie : public Component {
private:
    int hitpoints;

public:
    Zombie(GameObject& associated);
    virtual ~Zombie();  // Adicionado destrutor virtual
    
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
    void Damage(int damage);
};

#endif