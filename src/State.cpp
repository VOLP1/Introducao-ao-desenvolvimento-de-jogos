#include "../include/State.h"
#include "../include/Game.h"

State::State() : bg(nullptr), music(nullptr) {
    quitRequested = false;
    bg = new Sprite();
    music = new Music();
    LoadAssets();
}

State::~State() {
    delete bg;
    delete music;
}

void State::LoadAssets() {
    bg->Open("recursos/img/Background.png");
    music->Open("recursos/audio/BGM.wav");
    music->Play();
}

void State::Update(float dt) {
    quitRequested = SDL_QuitRequested();
}

void State::Render() {
    bg->Render(0, 0);
}

bool State::QuitRequested() {
    return quitRequested;
}