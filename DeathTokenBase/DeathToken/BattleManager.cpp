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
#include <SDL_ttf.h>

using json = nlohmann::json;
// Valores para el animo
const int MINMINDSET = 20;
const int MAXMINDSET = 80;
const int MOD = 20;

// Tiempo entre turnos (milisegundos)
constexpr int MSEG = 1500;

// Para random
random_device rd;
mt19937 gen(rd());
uniform_real_distribution<float> dist(0.0f, 100.0f);
uniform_int_distribution<int> range(0, 27); // 28 es el numero de enfrentamientos (nºpeleadores * (nºpeleadores - 1) /2) y hay 8 peleadores. Incluyendo el 0 lo hace que llegue hasta el 27
uniform_real_distribution<float> mindsetRange(5, 20);
uniform_real_distribution<float> inicialMindSet(MINMINDSET, MAXMINDSET);


BattleManager::BattleManager() :
    fighters()
    , battleQueue()
    , currentMatch()
{
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

    int i = range(gen);

    // Obtener el primer enfrentamiento en la cola
    currentMatch = battleQueue[i];

    // Mostrar la descripción de la batalla
    cout << "Descripción de la batalla: " << currentMatch.battleDescription << endl;
    cout << "Peleadores: " << currentMatch.fighter1.getName() << " vs " << currentMatch.fighter2.getName() << endl;

    // Asignar un "mindset" aleatorio a los luchadores
    float rndMindset1 = inicialMindSet(gen);
    float rndMindset2 = inicialMindSet(gen);

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

void
BattleManager::ActionTurn(Fighter& active, Fighter& objetive) {



    float hitBackProb = 2.5f + 15.0f * (50.0f - active.getMindset()) / 200.0f;
    float failProb = 7.5f + 12.5f * (50.0f - active.getMindset()) / 100.0f;
    float criticalProb = 10.0f + 30.0f * (active.getMindset() - 50.0f) / 100.0f;

    // Habra que meter los couts en la caja de dialogo en su momento
    cout << "¡" << active.getName() << " se dispone a atacar ferozmente a su enemigo!\n";
    float prob = dist(gen);

    // Golpearse a si mismo
    if (prob < hitBackProb) {
        active.takeDamage(active.getAttack());
        cout << "¡Pero se ha golpeado a si mismo, " << active.getName() << " se ha vuelto loco!\n";
        if (active.isAlive()) {
            active.reduceMindset(mindsetRange(gen));
            cout << "Esto seguro que mina su concentración en el combate\n";
            cout << "¡Ahora es más probable que pierda!\n";
        }
        else {
            cout << "¡LA CATASTROFE SE HIZO REALIDAD!\n";
            cout << "¡" << active.getName() << " ha caido por su propia mano!\n";
        }
    }

    // Fallo
    else if (prob < hitBackProb + failProb) // se suman para tener en cuenta que no se cumplido la anterior condicion
    {
        cout << active.getName() << " lamentablemente su golpe ha fallado a su objetivo.\n";
        active.reduceMindset(mindsetRange(gen));
        cout << "Esto seguro que mina su concentración en el combate.\n";
        cout << "¡Ahora es más probable que pierda!\n";
    }

    // Critico
    else if (prob < hitBackProb + failProb + criticalProb) // se suman para tener en cuenta que no se cumplido la anterior condicion
    {
        objetive.takeDamage(active.getAttack() * 3);
        cout << "¡MADRE MIA, CRÍTICO!" << active.getName() << " acaba de destrozar a su oponente.\n";
        cout << " Tras semejante golpe tal vez deban replantearse el resultado del combate.\n";
        if (objetive.isAlive()) {
            active.boostMindset(mindsetRange(gen));
            objetive.reduceMindset(mindsetRange(gen));
            cout << "Esto seguro que mejora su concentración en el combate.\n";
            cout << "¡Ahora es más probable que gane!\n";
            cout << "¡Y " << objetive.getName() << " es más probable que pierda!\n";
        }
        else {
            cout << active.getName() << " gana este brutal encuentro.\n";
            cout << "Enhorabuena a todos los que confiaron en nuestro increible ganador.\n";
        }
    }
    // No hay acciones especiales
    else {
        objetive.takeDamage(active.getAttack());
        cout << active.getName() << " golpea duramente a su oponente. \n";
        if (!objetive
            .isAlive()) {
            cout << active.getName() << " gana este brutal encuentro.\n";
            cout << "Enhorabuena a todos los que confiaron en nuestro increible ganador.\n";
        }
    }
}
void
BattleManager::ExecuteTurns(Matchup currentMatch) {

    Fighter fighter1 = currentMatch.fighter1;
    Fighter fighter2 = currentMatch.fighter2;

    // Empieza el que tiene menos habilidad
    if (fighter1.getAbility() > fighter2.getAbility()) {
        fighter2 = currentMatch.fighter1;
        fighter1 = currentMatch.fighter2;
    }

    cout << "Comenzará la pelea " << fighter1.getName() << ".\n";
    cout << "Mucha suerte a todos los jugadores.\n";
    cout << "\n";
    while (fighter1.isAlive() && fighter2.isAlive()) {

        ActionTurn(fighter1, fighter2);

        if (!(fighter1.isAlive() && fighter2.isAlive())) {
            break;
        }

        this_thread::sleep_for(chrono::milliseconds(MSEG));
        cout << "\n";

        cout << "Ahora es turno de " << fighter2.getName() << ".\n";
        ActionTurn(fighter2, fighter1);
        if (!(fighter1.isAlive() && fighter2.isAlive())) {
            break;
        }

        this_thread::sleep_for(chrono::milliseconds(MSEG));
        cout << "\n";

        cout << "Ahora es turno de " << fighter1.getName() << ".\n";

    }
}
