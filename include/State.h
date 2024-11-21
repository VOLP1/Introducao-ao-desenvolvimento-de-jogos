#ifndef STATE_H
#define STATE_H

#define INCLUDE_SDL
#include "SDL_include.h"
#include "GameObject.h"
#include "Music.h"
#include <vector>
#include <memory>

class State {
private:
    bool quitRequested;
    std::vector<std::unique_ptr<GameObject>> objectArray;
    void Input();
    Music* music;  // Adicionado o ponteiro para Music

public:
    State();
    ~State();
    
    void LoadAssets();
    void Update(float dt);
    void Render();
    bool QuitRequested();
    void AddObject(GameObject* object);
};

#endif