#include "../include/GameObject.h"
#include <algorithm>

GameObject::GameObject() : isDead(false) {}

GameObject::~GameObject() {
    for(int i = components.size() - 1; i >= 0; i--) {
        delete components[i];
    }
    components.clear();
}

void GameObject::Update(float dt) {
    for(auto& component : components) {
        component->Update(dt);
    }
}

void GameObject::Render() {
    for(auto& component : components) {
        component->Render();
    }
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(Component* cpt) {
    components.push_back(cpt);
}

void GameObject::RemoveComponent(Component* cpt) {
    auto it = std::find(components.begin(), components.end(), cpt);
    if(it != components.end()) {
        components.erase(it);
    }
}

Component* GameObject::GetComponent(std::string type) {
    for(auto& component : components) {
        if(component->Is(type)) {
            return component;
        }
    }
    return nullptr;
}