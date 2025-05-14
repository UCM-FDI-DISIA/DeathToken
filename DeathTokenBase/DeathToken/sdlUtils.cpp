#include "SDLUtils.h"

Uint32 SDLUtils::lastTime = SDL_GetTicks();
float SDLUtils::deltaTime = 0.0f;

void SDLUtils::updateDeltaTime() {
    Uint32 currTime = SDL_GetTicks();
    deltaTime = (currTime - lastTime) / 1000.0f; 
    lastTime = currTime;
}

float SDLUtils::getDeltaTime() {
    return deltaTime;
}