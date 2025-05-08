#include "GeneraPrecios.h"
#include <algorithm>

GeneraPrecios::GeneraPrecios()
  : gen(std::random_device{}())
{
}

InfoObjeto GeneraPrecios::generarObjeto()
{
  InfoObjeto objeto;
  determinarRango(objeto);
  aplicarModificador(objeto);
  return objeto;
}

void GeneraPrecios::determinarRango(InfoObjeto& objeto)
{
  std::uniform_int_distribution<int> distTipo(0, 3);

  switch (distTipo(gen)) {
    case 0:
      objeto.descripcionRango = "Objeto común de baja calidad";
      objeto.minRango = 50;
      objeto.maxRango = 150;
      break;
    case 1:
      objeto.descripcionRango = "Artefacto histórico valioso";
      objeto.minRango = 300;
      objeto.maxRango = 800;
      break;
    case 2:
      objeto.descripcionRango = "Joyería fina";
      objeto.minRango = 500;
      objeto.maxRango = 2000;
      break;
    case 3:
      objeto.descripcionRango = "Reliquia ancestral";
      objeto.minRango = 1000;
      objeto.maxRango = 5000;
      break;
  }
}

void GeneraPrecios::aplicarModificador(InfoObjeto& objeto)
{
  std::uniform_real_distribution<float> distMod(0.0f, 1.0f);
  float mod = distMod(gen);

  if (mod < 0.2f) {
    objeto.descripcionModificador = "en estado deplorable";
    objeto.precioReal =
      objeto.minRango + (int)((objeto.maxRango - objeto.minRango) * 0.1f);
  }
  else if (mod < 0.5f) {
    objeto.descripcionModificador = "en mal estado";
    objeto.precioReal =
      objeto.minRango + (int)((objeto.maxRango - objeto.minRango) * 0.3f);
  }
  else if (mod < 0.8f) {
    objeto.descripcionModificador = "en condiciones promedio";
    objeto.precioReal = (objeto.minRango + objeto.maxRango) / 2;
  }
  else {
    objeto.descripcionModificador = "en estado excepcional";
    objeto.precioReal =
      objeto.maxRango - (int)((objeto.maxRango - objeto.minRango) * 0.2f);
  }

  objeto.precioReal =
    std::clamp(objeto.precioReal, objeto.minRango, objeto.maxRango);
}