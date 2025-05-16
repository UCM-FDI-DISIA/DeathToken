#pragma once
#include "slots.h"

#include <iostream>
#include <unordered_map>
#include <vector>

class Carrete;

class SlotsNormal : public Slots {
protected:
  constexpr static int N_COLUM = 3;
  constexpr static float TAM_CELDA = 210;
  constexpr static float TAM_BOTON = 150;

  std::vector<Carrete*>
    carretes;  // Vector con los tres carretes que conforman la máquina
  int
    comprobanteIndice;  // Índice para saber cuándo se han parado los tres carretes
  int canalSonidoGiro = -1;  // Canal de sonido para el giro de los carretes

  int getResult() override { return 0; }

public:
  SlotsNormal(Game*);
  ~SlotsNormal();
  void update() override;
  void render() const override;
  void iniciarGiro() override;
};
