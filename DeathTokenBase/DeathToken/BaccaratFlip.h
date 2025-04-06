#pragma once
#include "Baccarat.h"
class BaccaratFlip : public Baccarat
{
private:
	//botones, eventos????
	Card* extra1;
	Card* extra2;
	Card* extra3;

	vector<int> extraVals;
	int hiddenExtraIndex = -1;
public:
	BaccaratFlip(Game* game);
	//void addCards() override;
	void handleExtraCards();

	//void generateThreeRandoms();//genera las tres cartas a elegir, tienen que tener un rect que detecte el clik del raton y les haga flip
	void render() const override;
	void handleEvents();//para dar la vuelta a las cartas o decirle que va al player o a la banca
	void gift();//para decir que carta va a quien
	void createBaccaratBetButton(int x, int y, int width, int height);
};

//este juego es el baccarat solo que salen tres cartas aleatorias. Puedes ver dos y repartir si o si una a player y otra a banca
// la ultima carta debes repartirla a uno de los dos sin saber su valor