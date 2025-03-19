
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
  ability = maxHealth + (attack * 1.3f);
  mindset = 50;  // Valor por defecto

  return true;
}
