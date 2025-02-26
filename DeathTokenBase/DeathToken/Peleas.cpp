#include "Button.h"
#include "Game.h"
#include "BattleManager.h"
#include "Peleas.h"

Peleas::Peleas(Game* game) : GameState(game) , _battleM(new BattleManager()) {
	if (_battleM->loadFightersFromJSON("peleadores.json")) {
		_battleM->StartBattle();
	}
}