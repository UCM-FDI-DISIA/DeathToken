#ifndef FIGHTER_H
#define FIGHTER_H

#include <iostream>
#include <string>
#include <fstream>
//#include "json.hpp" // Usar la librería nlohmann/json

using namespace std;
//using json = nlohmann::json;

class Fighter {
public:
    Fighter() = default;

    // Carga los datos del peleador desde un archivo JSON
    bool loadFromJSON(const string& filename);

    // Métodos Getters para acceder a los atributos
    string getName() const { return name; }
    int getHealth() const { return health; }
    int getAttack() const { return attack; }
    string getDesc() const { return desc; }
    float getAbility() const { return ability; }
    int getMaxHealth() const { return maxHealth; }
    int getMindset() const { return mindset; }

    // Métodos Setters
    void setHealth(int value) { health = value; }
    void setMindset(int value) { mindset = value; }

    // Mostrar los detalles del peleador (opcional para debug)
    void print() const {
        cout << "Nombre: " << name << endl;
        cout << "Salud: " << health << endl;
        cout << "Ataque: " << attack << endl;
        cout << "Descripción: " << desc << endl;
    }

private:
    string name;
    int maxHealth;
    int health;
    int attack;
    string desc;
    float ability;  // Habilidad calculada (puede usarse para determinar las probabilidades)
    int mindset;    // Valor adicional que puede afectar el rendimiento
};

#endif // FIGHTER_H
