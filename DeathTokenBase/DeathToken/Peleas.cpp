#include "Button.h"
#include "Game.h"
#include "BattleManager.h"
#include "Peleas.h"
#include <thread>

Peleas::Peleas(Game* game) : GameState(game) , _battleM(new BattleManager()) {
	if (_battleM->loadFightersFromJSON("peleadores.json") && _battleM->loadMatchupsFromJSON("../DeathToken/matchups.json")) 
	{
		std::thread BattleThread([this]() {_battleM->StartBattle();});
		BattleThread.detach();
	}

}