#include "State.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Component.h"
#include "SpriteRenderer.h"
#include "Music.h"
#include "Zombie.h"  
#include <iostream>

State::State() : quitRequested(false) {
    LoadAssets();
}

State::~State() {
    objectArray.clear();
}

void State::LoadAssets() {
    std::cout << "Loading assets..." << std::endl;
    
    // Criar o GameObject do background
    GameObject* bg = new GameObject();
    
    // Adicionar o componente SpriteRenderer com a imagem de fundo
    SpriteRenderer* renderer = new SpriteRenderer(*bg, "recursos/img/Background.png");
    bg->AddComponent(renderer);
    
    // Definir a posição inicial (0,0 neste caso)
    bg->box.x = 0;
    bg->box.y = 0;
    
    // Adicionar o GameObject ao State
    AddObject(bg);


    GameObject* zombie = new GameObject();
    zombie->box.x = 600;
    zombie->box.y = 450;
    Zombie* zombieComponent = new Zombie(*zombie);
    zombie->AddComponent(zombieComponent);
    AddObject(zombie);
    

    // Carrega e toca a música
    music = new Music();
    music->Open("recursos/audio/BGM.wav");
    music->Play();
}

void State::Update(float dt) {
    Input();
    
    for(int i = 0; i < (int)objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }
    
    for(int i = 0; i < (int)objectArray.size(); i++) {
        if(objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
            i--;
        }
    }
}

void State::Render() {
    for(auto& go : objectArray) {
        go->Render();
    }
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::AddObject(GameObject* object) {
    objectArray.emplace_back(object);
}

void State::Input() {
    SDL_Event event;
    int mouseX, mouseY;
    
    // Obtenha as coordenadas do mouse
    SDL_GetMouseState(&mouseX, &mouseY);
    
    // SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
    while (SDL_PollEvent(&event)) {
        // Se o evento for quit, setar a flag para terminação
        if(event.type == SDL_QUIT) {
            quitRequested = true;
        }
    }
}