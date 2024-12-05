#include "State.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Component.h"
#include "SpriteRenderer.h"
#include "Music.h"
#include "Zombie.h"
#include "TileMap.h"
#include "TileSet.h"
#include <iostream>

State::State() : quitRequested(false) {
    LoadAssets();
}

State::~State() {
    objectArray.clear();
}

void State::LoadAssets() {
    std::cout << "Loading State assets..." << std::endl;
    
    // Cria o tilemap
    GameObject* tileMapObj = new GameObject();
    std::cout << "Creating TileSet..." << std::endl;
    TileSet* tileSet = new TileSet(64, 64, "recursos/img/Tileset.png");  // Note o T maiúsculo
    std::cout << "Creating TileMap..." << std::endl;
    TileMap* tileMap = new TileMap(*tileMapObj, "recursos/map/map.txt", tileSet);
    tileMapObj->AddComponent(tileMap);
    tileMapObj->box.x = 0;
    tileMapObj->box.y = 0;
    AddObject(tileMapObj);
    std::cout << "TileMap added to State" << std::endl;

    // Cria o Zombie
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
    std::cout << "Music started" << std::endl;
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