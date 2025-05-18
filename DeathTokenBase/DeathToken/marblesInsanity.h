#pragma once
#include "marbles.h"
#include "game.h"
class MarblesInsanity : public GameState
{
private:
	UIMarblesInsanity* uiI;

	Text* guideText;
	Texture* texture;
	bool gameFinish;
	std::vector<Texture*> CMarbles;
	std::vector<ButtonMarblesInsanity*> trileroButtons;
	std::vector<int> dColor;
	int posColor;

	SDL_Rect wMarble;
	int wMarbleI;
	bool wMarbleShow;

	HUDBet* hud;

public:
	MarblesInsanity(Game* game);
	~MarblesInsanity();
	void render() const override;
	void update() override;
	void StartRoundTrickster();
	void discardMarble(bool marble);
	void createTricksterButtons();
	void createButtonT(int x, int y, int width, int height, Texture* texture, Texture* textureC, bool marble, std::vector<int> marbleColor);
};

