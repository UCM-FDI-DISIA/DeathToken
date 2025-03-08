#ifndef DIALOGUEBOX_H
#define DIALOGUEBOX_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class DialogueBox {
public:
    DialogueBox(SDL_Renderer* renderer, TTF_Font* font);
    ~DialogueBox() { renderer = nullptr; TTF_CloseFont(font); };
    void showMessage(const std::string& message);
    void hideMessage();
    void ResetMessage();
    void render();

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    std::string message;
    bool visible;
};

#endif // DIALOGUEBOX_H
