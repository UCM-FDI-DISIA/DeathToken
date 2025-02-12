#include "checkML.h"

#include <fstream>
#include "TileMap.h"
#include "Texture.h"
#include "playState.h"

TileMap::TileMap(PlayState* g, string file, Texture* tex)
	:sceneObject(g, tex), tile(Game::WIN_HEIGHT)
{
	//leemos el archivo csv y lo guardamos en la matriz tile
	ifstream csv;
	csv.open(file);
	if (!csv.is_open())throw "Error al cargar Tilemap";
	int i = 0;
	while (!csv.eof()) {
		int k;
		csv >> k;
		tile[i].push_back(k);
		char c; csv.get(c);
		if (c == '\n') {
			++i;
		}
	}
	csv.close();
	state->setMaxOffset(tile[0].size());
}
void TileMap::render() const {
	SDL_SetRenderDrawColor((state->getGame())->getRenderer(), state->getColor().R, state->getColor().G, state->getColor().B, 255);
	SDL_RenderClear((state->getGame())->getRenderer());

	//cacheamos las constantes
	int side = Game::TILE_SIDE;
	int width = Game::WIN_WIDTH;
	int height = Game::WIN_HEIGHT;
	int x0 = state->getOffset() / side;
	int d0 = state->getOffset() % side;

	SDL_Rect rect;
	rect.w = side;
	rect.h = side;

	// Pintamos los WINDOW_WIDTH + 1 (aunque se salga) x WINDOW_HEIGHT recuadros del mapa
	for (int i = 0; i < width + 1; ++i) {
		for (int j = 0; j < height; ++j) {
			// Índice en el conjunto de patrones de la matriz de índices
			int indice = tile[j][x0 + i];

			//comprobamos que no sea posicion vacia (-1)
			if (indice != -1) {
				// Separa número de fila y de columna
				int fx = indice % 9;
				int fy = indice / 9;

				rect.x = -d0 + i * side;
				rect.y = j * side;

				// Usa renderFrame para pintar la tesela
				texture->renderFrame(rect, fy, fx);
			}
		}
	}
}
Collision TileMap::hit(const SDL_Rect& rect, Collision::Target target){
	constexpr int OBSTACLE_THRESHOLD = 4; // constante
	Collision collide;
	// Celda del nivel que contiene la esquina superior izquierda del rectángulo
	int row0 = rect.y / Game::TILE_SIDE;
	int col0 = rect.x / Game::TILE_SIDE;

	// Celda del nivel que contiene la esquina inferior derecha del rectángulo
	int row1 = (rect.y + rect.h - 1) / Game::TILE_SIDE;
	int col1 = (rect.x + rect.w - 1) / Game::TILE_SIDE;
	
	bool fin = false;
	//Recorremos los tiles que ocupa el sprite comprobando su contenido
	for (int row = row0; row <= row1; ++row) {
		for (int col = col0; col <= col1; ++col) {
			if (target == Collision::PLAYER && (tile[row][col] == 34 || tile[row][col] == 43)){
				fin = true; // Si es bandera se dispara el fin del juego
			}
			else if (tile[row][col] % texture->getNumColumns() < OBSTACLE_THRESHOLD && tile[row][col] != -1) { // Si es un bloque se devuelve la intersección
				SDL_Rect block;
				block.h = block.w = Game::TILE_SIDE;
				block.x = col * Game::TILE_SIDE;
				block.y = row * Game::TILE_SIDE;
				SDL_Rect inter;
				SDL_IntersectRect(&rect, &block, &inter);
				collide = {Collision::OBSTACLE, inter.w, inter.h};
				return collide;
			}
		}
	}
	if(fin)state->nextLevel();
	return collide;
}