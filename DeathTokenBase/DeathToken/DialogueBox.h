#ifndef DIALOGUEBOX_H
#define DIALOGUEBOX_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "gameObject.h"

class DialogueBox {
public:
    DialogueBox(): renderer(nullptr), font(nullptr), message(""), visible(false) {}
    DialogueBox(SDL_Renderer* renderer, TTF_Font* font);
    ~DialogueBox() { renderer = nullptr; font = nullptr; };
    void showMessage(const std::string& message);
    void addMessage(const std::string& message);
    void hideMessage();
    void ResetMessage();
    void render() const;
    void render(int x, int y) const;

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    std::string message;
    bool visible;
};

#endif // DIALOGUEBOX_H
