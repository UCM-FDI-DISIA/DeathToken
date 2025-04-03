#include "BattleManager.h"
#include "json.hpp"
#include "Peleas.h"
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <random>
#include "json.hpp" 
#include <algorithm>
using json = nlohmann::json;

BattleManager::BattleManager() {
    srand(static_cast<unsigned int>(time(0)));  // Inicializar aleatorio
}

bool BattleManager::loadFightersFromJSON(const string& filename)
{
	ifstream file(filename);
	if (!file.is_open()) {
#ifdef DEBUG
		std::cout << "No se pudo abrir el archivo de peleadores." << endl;
#endif // DEBUG

  json j;
  file >> j;

  for (auto& item : j["peleadores"]) {
    Fighter fighter;
    // Convertir el JSON a string antes de pasarlo
    fighter.loadFromJSON(item.dump());
    fighters.push_back(fighter);
  }

  file.close();
  return true;
}

bool BattleManager::loadMatchupsFromJSON(const string& filename)
{
	ifstream file(filename);
	if (!file.is_open()) {
#ifdef DEBUG
		cout << "No se pudo abrir el archivo de enfrentamientos." << endl;
#endif
		return false;
	}

  try {
    json j;
    file >> j;

		// Verificar si "matchups" existe en el JSON
		if (j.find("matchups") == j.end()) {
#ifdef DEBUG
			cout << "No se encuentra el campo 'matchups' en el JSON." << endl;
#endif
			return false;
		}

    // Procesar el JSON y cargar los enfrentamientos
    for (auto& item : j["matchups"]) {
      int id1 = item["F1"];
      int id2 = item["F2"];
      int advantageFighterIndex = item["advantageFighterIndex"];
      string battleDescription = item["battleDescription"];

			if (id1 < 0 || id1 >= fighters.size() || id2 < 0 ||
				id2 >= fighters.size()) {
#ifdef DEBUG
				cout << "�ndice de peleador inv�lido." << endl;
#endif
				continue;
			}

      Matchup matchup;
      matchup.fighter1 = fighters[id1];
      matchup.fighter2 = fighters[id2];
      matchup.advantageFighterIndex = advantageFighterIndex;
      matchup.battleDescription = battleDescription;

      battleQueue.push_back(matchup);
    }
  }
  catch (const json::parse_error& e) {
    cout << "Error al procesar el JSON: " << e.what() << endl;
    return false;
  }

  file.close();
  return true;
}

void BattleManager::StartBattle() {
    /*if (battleQueue.empty()) {
        cout << "No hay enfrentamientos en la cola." << endl;
        return;
    }*/
    assert(!battleQueue.empty());

    // Obtener el primer enfrentamiento en la cola
    Matchup currentMatch = battleQueue.front();
    battleQueue.erase(battleQueue.begin());

    // Mostrar la descripci�n de la batalla
    cout << "Descripci�n de la batalla: " << currentMatch.battleDescription << endl;
    cout << "Peleadores: " << currentMatch.fighter1.getName() << " vs " << currentMatch.fighter2.getName() << endl;

    // Asignar un "mindset" aleatorio a los luchadores
    int rndMindset1 = (rand() % MAXMINDSET) + MINMINDSET;
    int rndMindset2 = (rand() % MAXMINDSET) + MINMINDSET;

   
    currentMatch.fighter2.setMindset(rndMindset2);

    if (currentMatch.advantageFighterIndex == 1)
    {
        currentMatch.fighter1.setMindset(rndMindset1 + MOD);
        currentMatch.fighter2.setMindset(rndMindset2 - MOD);
    }
    else
    {
        currentMatch.fighter1.setMindset(rndMindset1 + MOD);
        currentMatch.fighter2.setMindset(rndMindset2 - MOD);
    }
}

void BattleManager::Update(float deltaTime)
{
	if (dialog->passNextState() || currentState == BattleState::START) {
		dialog->BattleStatePass(); // Reiniciamos el temporizador

		switch (currentState) {
		case BattleState::START:
			dialog->showMessage("La pelea ser� un clasicazo en esta arena " + currentMatch.fighter1.getName() + " vs " + currentMatch.fighter2.getName());
			dialog->showMessage(currentMatch.battleDescription);
			dialog->showMessage("Acorde a las normas empieza " + currentMatch.fighter1.getName());
			currentState = BattleState::PLAYER1_TURN;  // Cambiamos al turno del jugador 1
			lastTurn = BattleState::PLAYER1_TURN;  // Inicializamos el �ltimo turno
			break;

		case BattleState::PLAYER1_TURN:
			ActionTurn(currentMatch.fighter1, currentMatch.fighter2);
			currentState = BattleState::EVALUATE;  // Cambiamos a evaluaci�n
			break;

		case BattleState::PLAYER2_TURN:
			ActionTurn(currentMatch.fighter2, currentMatch.fighter1);
			currentState = BattleState::EVALUATE;  // Cambiamos a evaluaci�n
			break;

		case BattleState::EVALUATE:
			if (!currentMatch.fighter1.isAlive() ||
				!currentMatch.fighter2.isAlive()) {
				currentState = BattleState::END;  // Si alguien muri�, terminamos
			}
			else {
				// Cambiar al siguiente turno
				if (lastTurn == BattleState::PLAYER1_TURN) {
					currentState = BattleState::PLAYER2_TURN;
					dialog->showMessage("Turno de " + currentMatch.fighter2.getName());
					dialog->showMessage("�" + currentMatch.fighter2.getName() + " se dispone a atacar ferozmente a su enemigo!");
					lastTurn =
						BattleState::PLAYER2_TURN;  // Actualizamos el �ltimo turno
				}
				else {
					currentState = BattleState::PLAYER1_TURN;
					dialog->showMessage("Turno de " + currentMatch.fighter1.getName());
					dialog->showMessage("�" + currentMatch.fighter1.getName() + " se dispone a atacar ferozmente a su enemigo!");
					lastTurn =
						BattleState::PLAYER1_TURN;  // Actualizamos el �ltimo turno
				}
			}
			break;

		case BattleState::END:
			Fighter* winner = currentMatch.fighter1.isAlive() ?
				&currentMatch.fighter1 :
				&currentMatch.fighter2;
			dialog->showMessage("�La batalla ha terminado! El ganador es: " + winner->getName());
			break;
		}
	}
}


void BattleManager::ActionTurn(Fighter& active, Fighter& objetive)
{
	float hitBackProb = 2.5f + 15.0f * (50.0f - active.getMindset()) / 200.0f;
	float failProb = 7.5f + 12.5f * (50.0f - active.getMindset()) / 100.0f;
	float criticalProb = 10.0f + 30.0f * (active.getMindset() - 50.0f) / 100.0f;
	float prob = dist(gen);

	// Golpearse a s� mismo
	if (prob < hitBackProb) {
		active.takeDamage(active.getAttack());
		dialog->showMessage("�Pero se ha golpeado a s� mismo, " + active.getName() + " se ha vuelto loco!");

		if (active.isAlive()) {
			active.reduceMindset(mindsetRange(gen));
			dialog->showMessage("Esto seguro que mina su concentraci�n en el combate");
			dialog->showMessage("�Ahora es m�s probable que pierda!");
		}
		else {
			dialog->showMessage("�LA CATASTROFE SE HIZO REALIDAD!");
			dialog->showMessage("�" + active.getName() + " ha ca�do por su propia mano!");
		}
	}

	// Fallo
	else if (prob < hitBackProb + failProb) {
		dialog->showMessage(active.getName() + " lamentablemente su golpe ha fallado a su objetivo.");
		active.reduceMindset(mindsetRange(gen));
		dialog->showMessage("Esto seguro que mina su concentraci�n en el combate.");
		dialog->showMessage("�Ahora es m�s probable que pierda!");
	}

	// Cr�tico
	else if (prob < hitBackProb + failProb + criticalProb) {
		objetive.takeDamage(active.getAttack() * 3);
		dialog->showMessage("�MADRE M�A, CR�TICO! " + active.getName() + " acaba de destrozar a su oponente.");
		dialog->showMessage(" Tras semejante golpe tal vez deban replantearse el resultado del combate.");
		if (objetive.isAlive()) {
			active.boostMindset(mindsetRange(gen));
			objetive.reduceMindset(mindsetRange(gen));
			dialog->showMessage("Esto seguro que mejora su concentraci�n en el combate.");
			dialog->showMessage("�Ahora es m�s probable que gane!");
			dialog->showMessage("�Y " + objetive.getName() + " es m�s probable que pierda!");
		}
		else {
			dialog->showMessage(active.getName() + " gana este brutal encuentro.");
			dialog->showMessage("Enhorabuena a todos los que confiaron en nuestro incre�ble ganador.");
		}
	}

	// Ataque normal
	else {
		objetive.takeDamage(active.getAttack());
		dialog->showMessage(active.getName() + " golpea duramente a su oponente.");
		if (!objetive.isAlive()) {
			dialog->showMessage(active.getName() + " gana este brutal encuentro.");
			dialog->showMessage("Enhorabuena a todos los que confiaron en nuestro incre�ble ganador.");
		}
	}
}

//void BattleManager::ExecuteTurns(Matchup currentMatch)
//{
//
//
//	cout << "Comenzar� la pelea " << currentMatch.fighter1.getName() << ".\n";
//	cout << "Mucha suerte a todos los jugadores.\n";
//	cout << "\n";
//
//	auto lastTime = chrono::high_resolution_clock::now();
//
//	auto currentTime = chrono::high_resolution_clock::now();
//	float deltaTime = chrono::duration<float>(currentTime - lastTime).count();
//	lastTime = currentTime;
//	Update(deltaTime);  // Pasamos el delta time a Update
//
//}
