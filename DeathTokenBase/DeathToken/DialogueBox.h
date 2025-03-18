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
        , x(800)
        , y(200)
    {}

    DialogueBox(SDL_Renderer* renderer, TTF_Font* font, int posx = 800, int posy = 200, bool update = false, bool transparente = true)
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
        , x(posx)
        , y(posy)
    {
    }

    virtual ~DialogueBox() { renderer = nullptr; font = nullptr; };
    void showMessage(const std::string& message);
    void hideMessage();
    void ResetHistory();
    virtual void render() const;
    void update(float deltaTime);
    void handleEvent(const SDL_Event& event);

    inline void SetPosition(int posx, int posy) {
        x = posx;
        y = posy;
    }

    inline void SetX(int posx) {
        x = posx;
    }

    inline void SetY(int posy) {
        y = posy;
    }

protected:
    SDL_Renderer* renderer;
    TTF_Font* font;
    std::deque<std::string> history;
    std::string message;
    
    int x;
    int y;

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

