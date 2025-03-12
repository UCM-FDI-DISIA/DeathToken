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
    virtual ~DialogueBox() { renderer = nullptr; font = nullptr; };
    void showMessage(const std::string& message);
    void addMessage(const std::string& message);
    void hideMessage();
    void ResetMessage();
    virtual void render(bool transparente = true) const;
    virtual void render( int x, int y, bool transparente = true) const;

protected:
    SDL_Renderer* renderer;
    TTF_Font* font;
    std::string message;
    bool visible;
};
#endif // DIALOGUEBOX_H

