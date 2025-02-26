#include "Fighter.h"
#include "json.hpp"

using json = nlohmann::json;

// Implementación de loadFromJSON
bool Fighter::loadFromJSON(const string& filename) {
	  // Abrir el archivo JSON
	  ifstream file(filename);
	  if (!file.is_open()) {
		  cout << "No se pudo abrir el archivo JSON." << endl;
		  return false;
	  }

	  // Cargar el JSON desde el archivo
	  json j;
	  file >> j;

	  // Asignar los valores del JSON a los atributos del peleador
	  name = j["name"];
	  maxHealth = j["health"];
	  health = maxHealth;  // Inicia con la salud máxima
	  attack = j["attack"];
	  desc = j["desc"];
	  ability = maxHealth + (attack * 1.3f);  // Calcular la habilidad
	  mindset = 50; // Valor por defecto para el "mindset"

	  file.close();
	return true;
}

