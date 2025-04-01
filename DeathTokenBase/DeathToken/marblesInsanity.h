#pragma once
#include "Marbles.h"
#include "Game.h"
#include "vector"
class MarblesInsanity : public Marbles
{
private:
	Texture* texture;
	bool mInsanity;
	bool gameFinish;
	std::vector<ButtonMarblesInsanity*> trileroButtons;
	std::vector<int> dColor;
	int posColor;
	std::vector<Texture*> CMarbles;
public:
	MarblesInsanity(Game* game);
	~MarblesInsanity();
	void render() const override;
	void update() override;
	void StartRoundTrickster();
	void discardMarble(int x, int y, int widht, int height,bool marble,std::vector<int> color);
	void createTricksterButtons();
	void createButtonT(int x, int y, int widht, int height, Texture* texture, Texture* textureC, bool marble, std::vector<int> marbleColor);


};

