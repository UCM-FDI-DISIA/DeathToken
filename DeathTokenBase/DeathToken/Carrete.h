#pragma once
#include "sceneObject.h"
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

// Clase auxiliar de Slots que representa cada uno de los carretes que giran
class Carrete : public SceneObject {
private:
	constexpr static int NUM_ELEMS = 3; // Celdas por carrete

	const vector<int> frecuencias = { 4,3,3,3,2,2,1}; // recuencias de aparición de los iconos
	vector<int> resultante; // Vector aleatorio con los indices de los iconos formado segun las frecuencias
	int indice; // indice de cual es el actual
	Texture* iconos; // texturas de los iconos
	bool giro = false;
	vector<int>carretesRes; // resultado al parar
	
	vector<int> vectorAleatorio(); // metodo pra generar el vector 'resultado'

	const int delta = 1; // updates de diferencia entre giro y giro
	int act; // update actual

public:
	Carrete(GameState*,Point2D<int>, int, int, Texture*,Texture*);
	~Carrete();
	
	bool getParada() { return giro; } // Devuelve si está girando o no
	vector<int> getCarrete() const { return carretesRes; } // Devuelve el resultado
	void deleteCarrete() { carretesRes.erase(carretesRes.begin(), carretesRes.end()); } // borra el carrete resutado
	void iniciarGiro();
	void pararGiro(); //Detiene el giro del carrete
	void render() const override;
	void update() override;
};
