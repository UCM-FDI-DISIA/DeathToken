#ifndef FIGHTER_H
#define FIGHTER_H

#include <iostream>
#include <string>
using namespace std;

// Incluye tu librería de JSON aquí
#include "json/JSON.h"  

class Fighter {
public:
    Fighter() = default;

    // Carga datos del peleador desde un archivo JSON
    bool loadFromJSON(const string& filename);

    // Muestra la información del peleador
    void print() const;

     // Getters
    inline string getName() const
    {
        return name;
    };
    inline int getHealth() const
    {
        return health;
    };
    inline int getAttack() const
    {
        return attack;
    };
    inline string getDesc() const
    {
        return desc;
    };
    inline float getAnim() const 
    {
        return anim;
    };

    inline float CalculateAbility() {
        return (health + (attack * 1.3f));
    }
    inline float SetAnim(float an) {
        anim = an;
    }


  private:
    string name;
    int health;
    int attack;
    string desc;
    float anim;
};

#endif // FIGHTER_H