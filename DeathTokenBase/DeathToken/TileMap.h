#pragma once

#include "checkML.h"
#include <vector>
#include <string>

#include "sceneObject.h"

class TileMap : public sceneObject
{
private:
	vector<vector<int>> tile;
public:
	TileMap(PlayState*, string file, Texture* tex);
	void render() const override;
	void update() override {	};
	sceneObject* clone() const override { return nullptr; }
	Collision hit(const SDL_Rect& rect, Collision::Target);
};

