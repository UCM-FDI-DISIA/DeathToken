

#include <map>
#include <SDL_mixer.h>
#include <string>
#include <vector>

class SoundManager {
public:
  enum TipoSonido { EFECTO, MUSICA };

  static SoundManager& obtenerInstancia();

  bool inicializar(int frecuencia = 44100,
                   int canales = 2,
                   int tamañoBuffer = 2048);

  bool cargarSonido(const std::string& rutaArchivo,
                    const std::string& id,
                    TipoSonido tipo);

  bool cargarSonido(const std::vector<std::string>& rutasArchivos,
                    const std::string& id,
                    TipoSonido tipo);

  void reproducirEfecto(const std::string& id, int repeticiones = 0);
  void reproducirMusica(const std::string& id, int repeticiones = -1);

  void pausarMusica();
  void reanudarMusica();
  void detenerMusica();
  void ajustarVolumenMusica(int volumen);
  void ajustarVolumenEfectos(int volumen);

  void liberarSonido(const std::string& id);
  void liberarTodos();
  void limpiar();

  bool musicaEnReproduccion() const;
  bool musicaEnPausa() const;

  SoundManager(const SoundManager&) = delete;
  SoundManager& operator=(const SoundManager&) = delete;

private:
  SoundManager();
  ~SoundManager();

  struct Sonido {
    Mix_Chunk* efecto = nullptr;
    std::vector<Mix_Chunk*> variaciones;
    Mix_Music* musica = nullptr;
    TipoSonido tipo;
    bool multiVariante = false;
  };

  std::map<std::string, Sonido> sonidos;
  std::string musicaActual;
  bool listo = false;
  int volumenMusica = MIX_MAX_VOLUME / 2;
  int volumenEfectos = MIX_MAX_VOLUME / 2;
};
