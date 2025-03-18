#ifndef DIALOGUEBOX_H
#define DIALOGUEBOX_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <deque>
#include <string>
#include "gameObject.h"

class DialogueBox {
public:
    DialogueBox()
        : renderer(nullptr)
        , font(nullptr)
        , history()
        , message("")
        , visible(false)
        , transparente(true)
        , charIndex(0)
        , currentDialogIndex(0)
        , fast(false)
        , instantDisplay(false)
        , needsUpdate(false) 
    {}
    DialogueBox(SDL_Renderer* renderer, TTF_Font* font, bool update = false, bool transparente = true)
        : renderer(renderer)
        , font(font)
        , visible(false)
        , displayedText("")
        , message("")
        , charIndex(0)
        , currentDialogIndex(0)
        , instantDisplay(false)
        , fast(false)
        , transparente(transparente)
        , needsUpdate(update)
    {}

    virtual ~DialogueBox() { renderer = nullptr; font = nullptr; };
    void showMessage(const std::string& message);
    void hideMessage();
    void ResetHistory();
    virtual void render() const;
    virtual void render(int x, int y) const;
    void updateDialog(float deltaTime);
    void handleEvent(const SDL_Event& event);

protected:
    SDL_Renderer* renderer;
    TTF_Font* font;
    std::deque<std::string> history;
    std::string message;
    bool visible;
    bool transparente;
    bool fast;
    bool instantDisplay;
    bool needsUpdate;
    std::string displayedText;
    int currentDialogIndex;
    int charIndex;
    int completedTextTime = 0;
    const int letterdelay = 30; // en milisegundos
    const int fastLetter = 5; // en milisegundos
};
#endif // DIALOGUEBOX_H

