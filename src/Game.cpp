#include "../include/Game.h"
#include "../include/State.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <stdexcept>

Game* Game::instance = nullptr;

Game& Game::GetInstance() {
    if (instance == nullptr) {
        instance = new Game("Eduardo - 190134330", 1200, 900);
    }
    return *instance;
}

Game::Game(std::string title, int width, int height) {
    if (instance != nullptr) {
        throw std::runtime_error("Game instance already exists!");
    }
    instance = this;

    // Inicializa SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        throw std::runtime_error(SDL_GetError());
    }

    // Inicializa SDL_image
    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
    int imgInitResult = IMG_Init(imgFlags);
    if ((imgInitResult & imgFlags) != imgFlags) {
        SDL_Log("Unable to initialize SDL_image: %s", IMG_GetError());
        throw std::runtime_error(IMG_GetError());
    }

    // Inicializa SDL_mixer
    if (Mix_Init(MIX_INIT_OGG) < 0) {
        SDL_Log("Unable to initialize SDL_mixer: %s", Mix_GetError());
        throw std::runtime_error(Mix_GetError());
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0) {
        SDL_Log("Unable to open audio: %s", Mix_GetError());
        throw std::runtime_error(Mix_GetError());
    }

    Mix_AllocateChannels(32);

    // Cria a janela
    window = SDL_CreateWindow(title.c_str(), 
                            SDL_WINDOWPOS_CENTERED, 
                            SDL_WINDOWPOS_CENTERED, 
                            width, 
                            height, 
                            0);
    if (window == nullptr) {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        throw std::runtime_error(SDL_GetError());
    }

    // Cria o renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        throw std::runtime_error(SDL_GetError());
    }

    // Cria o estado do jogo
    state = new State();
}

Game::~Game() {
    delete state;
    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
    }
    if (window != nullptr) {
        SDL_DestroyWindow(window);
    }
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

State& Game::GetState() {
    return *state;
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

void Game::Run() {
    while (!state->QuitRequested()) {
        state->Update(0);
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(33); 
    }
}