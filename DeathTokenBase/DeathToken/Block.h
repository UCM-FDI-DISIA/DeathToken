#pragma once
#include "sceneObject.h"

class Block : public sceneObject{
private:
	enum Type{Surprise, Brick, Empty, Hidden, Hit};
	enum Content{ Coin, Mush };

	Texture* mushTex;
	Type tipo;
	Content contenido;
	int frame;

public:
	Block(PlayState* g, istream& in, Texture* text, Texture* mush);
	Block(const Block&);
	~Block() { mushTex = nullptr; }
	sceneObject* clone() const override;
	void render() const override;
	void update() override;
	Collision hit(const SDL_Rect& hit, Collision::Target target) override;
};