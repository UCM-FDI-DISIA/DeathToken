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
    Fighter(): 
        name("")
        , maxHealth(0)
        , health(0)
        , attack(0)
        , desc("Vacio")
        , mindset(50) 
    {}

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
    inline float getAbility() const { return health + attack * 1.3f; }
    inline int getMaxHealth() const { return maxHealth; }
    inline float getMindset() const { return mindset; }

    inline bool isAlive() const { return health > 0; } // es un metodo util para saber si el combate sigue o no

    float getOdds(float Ability2) const;
    std::string getStringMindset() const;

    // Métodos Setters
    inline void setHealth(int value) { health = value; }
    inline void setMindset(float value) { mindset = value; }

    inline void takeDamage(int value) { health = health - value < 0 ? 0 : health - value; }
    inline void boostMindset(float value) { mindset += value; }
    inline void reduceMindset(float value) { mindset -= value; }
   
private:
    string name;
    int maxHealth;
    int health;
    int attack;
    string desc;
    float mindset;    // Valor adicional que puede afectar el rendimiento
};

#endif // FIGHTER_H
