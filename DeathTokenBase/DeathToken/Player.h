#pragma once

#include "sceneObject.h"
#include "EventHandler.h"

class Player : public sceneObject, public EventHandler {
private:
	static constexpr int SPEED_MAG = 8;
	static constexpr int JUMP_MAG = 16;
	static constexpr int MAX_JUMP = 5;
	static constexpr int INV_TIME = 2 * Game::FRAME_RATE;
	enum Salto { SUELO, SALTO, CAIDA };

	Point2D<> OGpos;
	Texture* miniTexture;
	Texture* superTexture;
	bool super;
	bool invencible;
	int timeInv;
	int vidas;
	Salto salto;
	int currentjump;

	void MovementFrames();
	bool deadAnim();
public:
	Player(GameState* g,istream& in, Texture* tex, Texture* superTex);
	Player(const Player&);
	~Player() { miniTexture = nullptr; superTexture = nullptr; }
	sceneObject* clone() const override;
	void render() const override;
	void update() override;
	Collision hit(const SDL_Rect&, Collision::Target) override;
	void handleEvent(const SDL_Event& evento) override;
	bool getSuper() const { return super; }
	bool getInv() const { return invencible; }
	int getVidas() const { return vidas; }
	void resetLevel();
	void superOrDamage(bool);
};