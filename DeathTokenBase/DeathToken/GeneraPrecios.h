﻿#pragma once
#include <random>
#include <string>
#include "game.h"

struct InfoObjeto {
  TextureName tex;
  std::string nombre = "";
  std::string descripcionRango = "";
  std::string descripcionModificador = "";
  int precioReal = 0;
  int minRango = 0;
  int maxRango = 0;
};

class GeneraPrecios {
public:
  GeneraPrecios(std::mt19937);
  InfoObjeto generarObjeto();
  std::mt19937 gen;

private:
  void determinarRango(InfoObjeto& objeto);
  void aplicarModificador(InfoObjeto& objeto);
};