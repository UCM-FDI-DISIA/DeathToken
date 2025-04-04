
#include "json.hpp"
#include "Fighter.h"
using json = nlohmann::json;

bool Fighter::loadFromJSON(const std::string& jsonString)
{
  // Convertir la cadena JSON en un objeto json (solo dentro de este método)
  json j = json::parse(jsonString);

  // Asignar los valores
  name = j["name"].get<std::string>();
  maxHealth = j["health"].get<int>();
  health = maxHealth;
  attack = j["attack"].get<int>();
  desc = j["desc"].get<std::string>();
  mindset = 50;  // Valor por defecto

  return true;
}
float 
Fighter::getOdds(float Ability2) const {
    float difference = getAbility() - Ability2;
    if (difference >= 0) {
        if (difference < 14) {
            return 5.0f;  // Cuota 1:5
        }
        else if (difference >= 14 && difference < 28) {
            return 2.75f;  // Cuota 1:2.75
        }
        else if (difference >= 28 && difference < 56) {
            return 2.5f;  // Cuota 1:2.5
        }
        else if (difference >= 56 && difference < 72) {
            return 2.0f;  // Cuota 1:2
        }
        else {
            return 1.5f;  // Cuota 1:1.5
        }
    }
   
    else {

        if (difference > -14) {
            return 5.0f;  // Cuota 1:5
        }
        else if (difference <= -14 && difference > -28) {
            return 3.0f;  // Cuota 1:2.75
        }
        else if (difference <= -28 && difference > -56) {
            return 3.5f;  // Cuota 1:2.5
        }
        else if (difference <= -56 && difference > -72) {
            return 4.0f;  // Cuota 1:2
        }
        else {
            return 5.0f;  // Cuota 1:1.5
        }
        return 1.0f;
    }
    
}
string
Fighter::getStringMindset() const {
        if (mindset < 22) {
            return "Desanimado";
        }
        else if (mindset >= 22 && mindset < 40) {
            return "Distraido"; 
        }
        else if (mindset >= 40 && mindset < 66) {
            return "Preparado";  // Cuota 1:2.5
        }
        else if (mindset >= 66 && mindset < 82) {
            return "Confiado";  // Cuota 1:2
        }
        else {
            return "Invencible";  // Cuota 1:1.5
        }
}

