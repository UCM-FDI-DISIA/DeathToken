#include "GeneraPrecios.h"
#include <algorithm>
#include <random>

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
  std::uniform_int_distribution<int> distTipo(0, 2);
  std::uniform_int_distribution<int> distTex(0, 4);

  // Lista de texturas posibles
  static const std::vector<TextureName> texturas = {
    PELEASGRAMOPHONE, PELEASLAMP, PELEASPERFUME, PELEASPHONE, PELEASCHAMPAGNE
  };

  // Selecciona una textura aleatoria
  objeto.tex = texturas[distTex(gen)];

  objeto.tex = texturas[distTipo(gen) % texturas.size()];
  switch (distTipo(gen)) {
    case 0:
      objeto.descripcionRango = "�nico en el mundo";
      objeto.minRango = 100;
      objeto.maxRango = 200;
      break;
    case 1:
      objeto.descripcionRango = "Exclusivo";
      objeto.minRango = 50;
      objeto.maxRango = 100;
      break;
    case 2:
      objeto.descripcionRango = "Mundano";
      objeto.minRango = 10;
      objeto.maxRango = 50;
      break;
  }
}
void GeneraPrecios::aplicarModificador(InfoObjeto& objeto)
{
  std::uniform_int_distribution<int> distEstado(0, 3);

  switch (distEstado(gen)) {
    case 0:
      objeto.descripcionModificador = "Perfecto Estado";
      objeto.precioReal =
        objeto.maxRango - (objeto.maxRango - objeto.minRango) * 0.1;
      break;
    case 1:
      objeto.descripcionModificador = "Bien Conservado";
      objeto.precioReal = (objeto.maxRango + objeto.minRango) / 2;
      break;
    case 2:
      objeto.descripcionModificador = "Visiblemente Desgastado";
      objeto.precioReal =
        objeto.minRango + (objeto.maxRango - objeto.minRango) * 0.3;
      break;
    case 3:
      objeto.descripcionModificador = "Deplorable";
      objeto.precioReal =
        objeto.minRango + (objeto.maxRango - objeto.minRango) * 0.1;
      break;
  }
}