#pragma once
#include "marbles.h"
#include "game.h"
class MarblesInsanity : public GameState
{
private:
	UIMarblesInsanity* uiI;

	Texture* texture;
	bool gameFinish;
	std::vector<ButtonMarblesInsanity*> trileroButtons;
	std::vector<int> dColor;
	int posColor;
	std::vector<Texture*> CMarbles;

	SDL_Rect wMarble;
	int wMarbleI;
	bool wMarbleShow;

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

