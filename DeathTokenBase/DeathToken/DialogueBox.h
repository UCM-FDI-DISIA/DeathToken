//#pragma once
//#include "gameObject.h"
//#include <SDL.h>
//#include <SDL_ttf.h>
//#include <string>
//
//class DialogueBox : public GameObject {
//public:
//    DialogueBox(int x, int y, int w, int h, SDL_Renderer* renderer, TTF_Font* font, const std::string& text);
//    ~DialogueBox();
//
//    void update() override;
//    void render() const override;
//    void handleEvent(const SDL_Event& event);
//
//    void setText(const std::string& newText);
//    bool isActive() const { return active; }
//    void setActive(bool state) { active = state; }
//
//private:
//    SDL_Renderer* renderer;
//    TTF_Font* font;
//    std::string fullText;
//    std::string displayedText;
//    SDL_Texture* textTexture;
//    mutable SDL_Rect textRect;
//    SDL_Rect boxRect;
//
//    bool active;
//    size_t textIndex;
//    Uint32 lastUpdateTime;
//    bool fastForward;
//
//    void updateTexture();
//};
