#include "BattleManager.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <random>
#include "json.hpp" 
#include <algorithm>
#include <thread>
#include <chrono>

using json = nlohmann::json;

BattleManager::BattleManager() {
    srand(static_cast<unsigned int>(time(0)));  // Inicializar aleatorio
}

bool BattleManager::loadFightersFromJSON(const string& filename)
{
  ifstream file(filename);
  if (!file.is_open()) {
    std::cout << "No se pudo abrir el archivo de peleadores." << endl;
    return false;
  }

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
    cout << "No se pudo abrir el archivo de enfrentamientos." << endl;
    return false;
  }

  try {
    json j;
    file >> j;

    // Verificar si "matchups" existe en el JSON
    if (j.find("matchups") == j.end()) {
      cout << "No se encuentra el campo 'matchups' en el JSON." << endl;
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
        cout << "Índice de peleador inválido." << endl;
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
    assert(!battleQueue.empty());

    // Obtener el primer enfrentamiento en la cola
    Matchup currentMatch = battleQueue.front();
    battleQueue.erase(battleQueue.begin());

    // Mostrar la descripción de la batalla
    cout << "Descripción de la batalla: " << currentMatch.battleDescription << endl;
    cout << "Peleadores: " << currentMatch.fighter1.getName() << " vs " << currentMatch.fighter2.getName() << endl;

    // Asignar un "mindset" aleatorio a los luchadores
    int rndMindset1 = (rand() % MAXMINDSET) + MINMINDSET;
    int rndMindset2 = (rand() % MAXMINDSET) + MINMINDSET;

   

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

    ExecuteTurns(currentMatch);
}


void 
BattleManager::ExecuteTurns(Matchup currentMatch) {
    
    Fighter fighter1 = currentMatch.fighter1;
    Fighter fighter2 = currentMatch.fighter2;

    float hitBackProb1 = 2.5f + 15.0f * (50.0f - fighter1.getMindset()) / 200.0f;
    float failProb1 = 7.5f + 12.5f * (50.0f - fighter1.getMindset()) / 100.0f;
    float criticalProb1 = 10.0f + 30.0f * (fighter1.getMindset() - 50.0f) / 100.0f;
    
    float hitBackProb2 = 2.5f + 15.0f * (50.0f - fighter2.getMindset()) / 200.0f;
    float failProb2 = 7.5f + 12.5f * (50.0f - fighter2.getMindset()) / 100.0f;
    float criticalProb2 = 10.0f + 30.0f * (fighter2.getMindset() - 50.0f) / 100.0f;

    while (fighter1.isAlive() && fighter2.isAlive()) {
        // Habra que meter los couts en la caja de dialogo en su momento
        cout << "¡" << fighter1.getName() << " se dispone a atacar ferozmente a su enemigo ! \n";
        float prob = rand() % 100;
        // Golpearse a si mismo
        if (prob < hitBackProb1) {
            fighter1.takeDamage(fighter1.getAttack());
            cout << "¡Pero se ha golpeado a si mismo, " << fighter1.getName() << " se ha vuelto loco! \n";
            if (fighter1.isAlive()) {
                fighter1.reduceMindset(MOD);
                cout << "Esto seguro que mina su concentración en el combate.\n";
                cout << "¡Ahora es más probable que pierda!\n";
            }
            else {
                cout << "¡LA CATASTROFE SE HIZO REALIDAD!\n";
                cout << "¡" << fighter1.getName() << " ha caido por su propia mano! \n";
                break;
            }
        }
        // Fallo
        else if (prob < hitBackProb1 + failProb1) // se suman para tener en cuenta que no se cumplido la anterior condicion
        {
            cout << fighter1.getName() << " lamentablemente su golpe. \n";
            fighter1.reduceMindset(MOD);
            cout << "Esto seguro que mina su concentración en el combate.\n";
            cout << "¡Ahora es más probable que pierda!\n";
        }
        // Critico
        else if (prob < hitBackProb1 + failProb1 + criticalProb1) // se suman para tener en cuenta que no se cumplido la anterior condicion
        {
            fighter2.takeDamage(fighter1.getAttack() * 3);
            cout << "¡MADRE MIA, CRÍTICO!" << fighter1.getName() << " acaba de destrozar a su oponente. \n";
            cout << " Tras semejante golpe tal vez deban replantearse el resultado del combate.\n";
            if (fighter2.isAlive()) {
                fighter1.boostMindset(MOD);
                fighter2.reduceMindset(MOD);
                cout << "Esto seguro que mejora su concentración en el combate.\n";
                cout << "¡Ahora es más probable que gane!\n";
                cout << "¡Y "<< fighter2.getName() << " es más probable que pierda!\n";
            }
            else {
                cout << fighter1.getName() << " gana este brutal encuentro.\n";
                cout << "Enhorabuena a todos los que confiaron en nuestro increible ganador.\n";
                break;
            }
        }
        else {
            fighter2.takeDamage(fighter1.getAttack());
            cout << fighter1.getName() << " golpea duramente a su oponente. \n";
            if (!fighter2.isAlive()) {
                cout << fighter1.getName() << " gana este brutal encuentro.\n";
                cout << "Enhorabuena a todos los que confiaron en nuestro increible ganador.\n";
                break;
            }
        }
        this_thread::sleep_for(chrono::seconds(1));

        cout << "Ahora turno de "<< fighter2.getName() <<"\n";
    }
}
