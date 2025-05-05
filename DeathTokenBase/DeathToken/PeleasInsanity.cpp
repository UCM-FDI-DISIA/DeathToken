#include "PeleasInsanity.h"
#include <cstdlib>
#include <ctime>
#include <string>

PeleasInsanity::PeleasInsanity(Game* game)
    : GameState(game),
    currentState(State::INICIO),
    input1(new InputBox(game->getRenderer(), game->getTypo(FIGHTS_SMALL), 
           static_cast<int>(Game::WIN_WIDTH / 3), 
           static_cast<int>(3 * Game::WIN_HEIGHT / 4), 
           true, false, 400, 180)),
    correctPrice(0),
    playerGuess(0),
    stateStartTime(SDL_GetTicks()),
    lastUpdate(0) {
    
    srand(static_cast<unsigned>(time(nullptr)));
    correctPrice = rand() % 1000 + 1;  
    input1->setMaxLength(3);
    input1->showMessage("¡Adivina el precio del objeto!");
    input1->setActive(false);
    addEventListener(input1);
}

void PeleasInsanity::render() const {
    SDL_Rect fondo = {0, 0, Game::WIN_WIDTH, Game::WIN_HEIGHT};
    SDL_SetRenderDrawColor(game->getRenderer(), 0, 255, 255, 255);
    SDL_RenderFillRect(game->getRenderer(), &fondo);

    switch(currentState) {
        case State::INICIO:
        case State::COMPARACION:
        case State::FINAL:
            input1->render();
            break;
        case State::INPUT:
            input1->render();
            break;
    }
    GameState::render();
}

void PeleasInsanity::update() {
    Uint32 currentTime = SDL_GetTicks();
    switch(currentState) {
        case State::INICIO:
            if(currentTime - stateStartTime >= 2000) { // 2 segundos de espera
                currentState = State::INPUT;
                input1->clearInput();
                input1->setActive(true);
                stateStartTime = currentTime;
            }
            break;

        case State::INPUT:
            input1->update(currentTime - lastUpdate);
            if(!input1->getActive()) { // Usuario presionó Enter
                try {
                    playerGuess = std::stoi(input1->getMessage());
                } catch(...) {
                    playerGuess = 0;
                }
                currentState = State::COMPARACION;
                input1->showMessage("Verificando...");
                stateStartTime = currentTime;
            }
            break;

        case State::COMPARACION:
            if(currentTime - stateStartTime >= 1000) { // 1 segundo de "verificación"
                currentState = State::FINAL;
                if(playerGuess == correctPrice) {
                    input1->showMessage("¡Correcto! Ganaste.");
                } else {
                    input1->showMessage("Perdiste. Precio: " + std::to_string(correctPrice));
                }
                stateStartTime = currentTime;
            }
            break;

        case State::FINAL:
            if(currentTime - stateStartTime >= 3000) { 
                currentState = State::INICIO;
                correctPrice = rand() % 1000 + 1; 
                input1->showMessage("¡Adivina el precio del objeto!");
                stateStartTime = currentTime;
            }
            break;
    }
    lastUpdate = currentTime;
    GameState::update();
}