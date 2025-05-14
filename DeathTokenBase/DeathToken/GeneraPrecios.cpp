#include "GeneraPrecios.h"
#include "Game.h"
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
  std::uniform_int_distribution<int> distTipo(0, 4);

  // Asignar textura según tipo de objeto
  switch (distTipo(gen)) {
    case 0:
      objeto.descripcionRango = "Objeto común de baja calidad";
      objeto.minRango = 50;
      objeto.maxRango = 150;
      objeto.tex = PELEASLAMP;  
      break;
    case 1:
      objeto.descripcionRango = "Objeto histórico valioso";
      objeto.minRango = 300;
      objeto.maxRango = 800;
      objeto.tex = PELEASGRAMOPHONE;
      break;
    case 2:
      objeto.descripcionRango = "Artículo coidiciado históricamente";
      objeto.minRango = 500;
      objeto.maxRango = 2000;
      objeto.tex = PELEASCHAMPAGNE;
      break;
    case 3:
      objeto.descripcionRango = "Objeto deseado por los más expertos";
      objeto.minRango = 1000;
      objeto.maxRango = 5000;
      objeto.tex = PELEASPHONE;
      break;

      case 4:
      objeto.descripcionRango = "Reliquia Milenaria";
      objeto.minRango = 4000;
      objeto.maxRango = 7500;
      objeto.tex = PELEASPHONE;
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