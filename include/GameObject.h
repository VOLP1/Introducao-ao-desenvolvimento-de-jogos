#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Rect.h"
#include "Component.h"
#include <vector>
#include <memory>
#include <string>

class GameObject {
private:
    std::vector<Component*> components;
    bool isDead;
    
public:
    Rect box;
    
    GameObject();
    ~GameObject();
    
    void Update(float dt);
    void Render();
    bool IsDead();
    void RequestDelete();
    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);
    Component* GetComponent(std::string type);
};

#endif