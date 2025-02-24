#ifndef FIGHTER_H
#define FIGHTER_H

#include <iostream>
#include <string>
using namespace std;

// Incluye tu librería de JSON aquí
#include "../json/JSON.h"  

#define DEBUG

class Fighter {
public:
    Fighter() = default;

    // Carga datos del peleador desde un archivo JSON
    bool loadFromJSON(const string& filename);

#ifdef DEBUG
    // Muestra la información del peleador
    // Implementación de print
    void print() const {
        cout << "Nombre: " << name << endl;
        cout << "Salud: " << health << endl;
        cout << "Ataque: " << attack << endl;
        cout << "Descripción: " << desc << endl;
    }
#endif // DEBUG

     // Getters
    inline string getName() const {
        return name;
    }
    inline int getHealth() const {
        return health;
    }
    inline int getAttack() const {
        return attack;
    }
    inline string getDesc() const {
        return desc;
    }
    inline float getAbility() const {
        return maxHealth + (attack * 1.3f);
    }
    inline int getMaxHealth() const {
        return maxHealth;
    }
    inline int getMindset() const {
        return mindset;
    }

    //SETTERS:
    inline void setMindset(int value) {
        mindset = value;
    }
    inline void setHealth(int value) {
        health = value;
    }

  private:
    string name;
    int maxHealth; 
    int health; // Current health in battle
    int attack;
    string desc; // Description of the character
    float ability; // Use this to calculate the betting odds
    int mindset;
};

#endif // FIGHTER_H