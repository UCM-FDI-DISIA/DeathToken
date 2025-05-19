#include "firebaseUtils.h"
#include "ranking.h"
#include "game.h"
#include <SDL.h>
#include <cctype>
using namespace std;

Ranking::Ranking(Game* game, GameState* lastState) : GameState(game), state(lastState), background(game->getTexture(BLACKFOND))
{
    background->modAlfa(200);

	vector<FirebaseUtils::userData> ranking = FirebaseUtils::getRanking();

    Text* title = new Text(state, game->getTypo(RANKINGT),Game::WIN_WIDTH / 2, relativeY(Game::WIN_HEIGHT / 7), relativeY(10), Text::CENTRO);
    title->setMessage(" RANKING DE JUGADORES ");
    this->addObjects(title);
    
    int startY = relativeY(Game::WIN_HEIGHT / 7 + 250);
    int stepY = relativeY(100);
    int mostrar = 0;
    if (ranking.size() <= 5) {
        mostrar = ranking.size();
    }
    else {
        mostrar = 5;
    }

    for (int i = 0; i < mostrar; ++i) {
        auto& user = ranking[i];

        string msg = to_string(i + 1) + ". " + (user.nombre) + "  -FICHAS: " + to_string(user.fichas) + "  -ALMAS: " + to_string(user.almas);
        for (char& c : msg) {
            if (isalpha(static_cast<unsigned char>(c))) {
                c = toupper(static_cast<unsigned char>(c));
            }
        }
        Text* line = new Text(state, game->getTypo(RANKINGN), Game::WIN_WIDTH/2,(startY + i * stepY), relativeY(1), Text::CENTRO);
       
        line->setMessage(msg);
        this->addObjects(line);
    }

    ui = new UIRanking(this, game);

}

void Ranking::render() const
{
	state->render();
    background->render();
	GameState::render();
}

void Ranking::update()
{
    ui->update();
}

 int Ranking::relativeX(const float& n)
{
	int m = (int)((n / 1920.0f) * Game::WIN_WIDTH);
	return m;
}

 int
Ranking::relativeY(const float& n)
{
	int m = (int)((n / 1080.0f) * Game::WIN_HEIGHT);
	return m;
}