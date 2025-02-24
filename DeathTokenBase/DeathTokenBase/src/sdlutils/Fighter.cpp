#include "Fighter.h"
#include "../json/JSON.h"

// Implementación de loadFromJSON
bool Fighter::loadFromJSON(const string& filename) {
    JSONValue* jsonData = JSON::ParseFromFile(filename);

    if (jsonData == nullptr || !jsonData->IsObject()) {
        cout << "Error al cargar el JSON." << endl;
        return false;
    }

    JSONObject root = jsonData->AsObject();
    if (root.find("name") != root.end() && root["name"]->IsString()) {
        name = root["name"]->AsString();
    }
    if (root.find("health") != root.end() && root["health"]->IsNumber()) {
        health = static_cast<int>(root["health"]->AsNumber());
    }
    if (root.find("attack") != root.end() && root["attack"]->IsNumber()) {
        attack = static_cast<int>(root["attack"]->AsNumber());
    }
    if (root.find("desc") != root.end() && root["desc"]->IsString()) {
        desc = root["desc"]->AsString();
    }

    delete jsonData;
    return true;
}


