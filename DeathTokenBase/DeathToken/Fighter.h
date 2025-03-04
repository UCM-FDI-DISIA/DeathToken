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

#ifdef DEBUG
    // Mostrar los detalles del peleador (opcional para debug)
    inline void print() const {
        cout << "Nombre: " << name << endl;
        cout << "Salud: " << health << endl;
        cout << "Ataque: " << attack << endl;
        cout << "Descripción: " << desc << endl;
    }

#endif // DEBUG

    // Carga los datos del peleador desde un archivo JSON
    bool loadFromJSON(const std::string& s);

    // Métodos Getters para acceder a los atributos
    inline string getName() const { return name; }
    inline int getHealth() const { return health; }
    inline int getAttack() const { return attack; }
    inline string getDesc() const { return desc; }
    inline float getAbility() const { return ability; }
    inline int getMaxHealth() const { return maxHealth; }
    inline int getMindset() const { return mindset; }

    // Métodos Setters
    inline void setHealth(int value) { health = value; }
    inline void setMindset(int value) { mindset = value; }
   
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
