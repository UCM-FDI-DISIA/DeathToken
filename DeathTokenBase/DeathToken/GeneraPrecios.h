#pragma once
#include <random>
#include <string>

struct InfoObjeto {
  std::string nombre;
  std::string descripcionRango;
  std::string descripcionModificador;
  int precioReal;
  int minRango;
  int maxRango;
};

class GeneraPrecios {
public:
  GeneraPrecios();
  InfoObjeto generarObjeto();
  std::mt19937 gen;

private:
  std::string generarNombre();
  void determinarRango(InfoObjeto& objeto);
  void aplicarModificador(InfoObjeto& objeto);
};