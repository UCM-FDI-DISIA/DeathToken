#pragma once
#include "Marbles.h"
#include "Game.h"
#include "vector"
class MarblesInsanity : public Marbles
{
private:
	Texture* texture;
	bool mInsanity;
	std::vector<ButtonMarbles*> trileroButtons;
	std::vector<int> dColor;
	int posColor;
	Button* tButton1;
	Button* tButton2;
	Button* tButton3;



public:
	MarblesInsanity(Game* game);
	~MarblesInsanity();
	void render() const override;
	void update() override;
	void StartRoundTrickster();
	void discardMarble(int color);
	void createTricksterButtons();


};

