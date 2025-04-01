#pragma once
#include "Marbles.h"
#include "Game.h"
#include "vector"
class MarblesInsanity : public Marbles
{
private:
	Texture* texture;
	bool mInsanity;
	std::vector<ButtonMarblesInsanity*> trileroButtons;
	std::vector<int> dColor;
	int posColor;
	



public:
	MarblesInsanity(Game* game);
	~MarblesInsanity();
	void render() const override;
	void update() override;
	void StartRoundTrickster();
	void discardMarble(int color);
	void createTricksterButtons();


};

