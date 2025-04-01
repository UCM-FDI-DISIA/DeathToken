#pragma once

#include <SDL.h>

class SDLUtils {
private:
    static Uint32 lastTime;
    static float deltaTime;

public:
    static void updateDeltaTime();
    static float getDeltaTime();
};