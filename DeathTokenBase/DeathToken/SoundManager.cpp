#include "SoundManager.h"
#include <SDL.h>
#include <iostream>

SoundManager& SoundManager::obtenerInstancia()
{
  static SoundManager instancia;
  return instancia;
}

SoundManager::SoundManager()
{
  musicaActual = "";
}

SoundManager::~SoundManager()
{
  limpiar();
}

bool SoundManager::inicializar(int frecuencia, int canales, int tamañoBuffer)
{
  if (listo)
    return true;

  if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
    std::cerr << "Error SDL_InitSubSystem: " << SDL_GetError() << std::endl;
    return false;
  }

  if (Mix_OpenAudio(frecuencia, MIX_DEFAULT_FORMAT, canales, tamañoBuffer) <
      0) {
    std::cerr << "Error Mix_OpenAudio: " << Mix_GetError() << std::endl;
    return false;
  }

  Mix_AllocateChannels(16);
  listo = true;
  return true;
}

bool SoundManager::cargarSonido(const std::string& rutaArchivo,
                                const std::string& id,
                                TipoSonido tipo)
{
  if (!listo)
    return false;
  if (sonidos.find(id) != sonidos.end())
    return false;

  Sonido sonido;
  sonido.tipo = tipo;

  if (tipo == EFECTO) {
    sonido.efecto = Mix_LoadWAV(rutaArchivo.c_str());
    if (!sonido.efecto)
      return false;
    sonido.multiVariante = false;
  }
  else {
    sonido.musica = Mix_LoadMUS(rutaArchivo.c_str());
    if (!sonido.musica)
      return false;
  }

  sonidos[id] = sonido;
  return true;
}

bool SoundManager::cargarSonido(const std::vector<std::string>& rutasArchivos,
                                const std::string& id,
                                TipoSonido tipo)
{
  if (tipo != EFECTO || !listo || sonidos.find(id) != sonidos.end())
    return false;

  Sonido sonido;
  sonido.tipo = tipo;
  sonido.multiVariante = true;

  for (const auto& ruta : rutasArchivos) {
    Mix_Chunk* efecto = Mix_LoadWAV(ruta.c_str());
    if (!efecto) {
      for (auto v : sonido.variaciones)
        Mix_FreeChunk(v);
      return false;
    }
    sonido.variaciones.push_back(efecto);
  }

  sonidos[id] = sonido;
  return true;
}

void SoundManager::reproducirEfecto(const std::string& id, int repeticiones)
{
  if (!listo || sonidos.find(id) == sonidos.end())
    return;

  Sonido& sonido = sonidos[id];
  if (sonido.tipo != EFECTO)
    return;

  if (sonido.multiVariante && !sonido.variaciones.empty()) {
    int indice = rand() % sonido.variaciones.size();
    Mix_PlayChannel(-1, sonido.variaciones[indice], repeticiones);
  }
  else if (!sonido.multiVariante && sonido.efecto) {
    Mix_PlayChannel(-1, sonido.efecto, repeticiones);
  }
}

void SoundManager::reproducirMusica(const std::string& id, int repeticiones)
{
  if (!listo || sonidos.find(id) == sonidos.end())
    return;

  Sonido& sonido = sonidos[id];
  if (sonido.tipo != MUSICA || !sonido.musica)
    return;

  Mix_PlayMusic(sonido.musica, repeticiones);
  musicaActual = id;
  Mix_VolumeMusic(volumenMusica);
}

void SoundManager::pausarMusica()
{
  if (Mix_PlayingMusic())
    Mix_PauseMusic();
}

void SoundManager::reanudarMusica()
{
  if (Mix_PausedMusic())
    Mix_ResumeMusic();
}

void SoundManager::detenerMusica()
{
  Mix_HaltMusic();
  musicaActual = "";
}

void SoundManager::ajustarVolumenMusica(int volumen)
{
  volumenMusica = volumen;
  Mix_VolumeMusic(volumen);
}

void SoundManager::ajustarVolumenEfectos(int volumen)
{
  volumenEfectos = volumen;
  for (auto& par : sonidos) {
    if (par.second.tipo == EFECTO) {
      if (par.second.multiVariante) {
        for (auto efecto : par.second.variaciones) {
          Mix_VolumeChunk(efecto, volumen);
        }
      }
      else if (par.second.efecto) {
        Mix_VolumeChunk(par.second.efecto, volumen);
      }
    }
  }
}

void SoundManager::liberarSonido(const std::string& id)
{
  if (sonidos.find(id) == sonidos.end())
    return;

  Sonido& sonido = sonidos[id];
  if (sonido.tipo == EFECTO) {
    if (sonido.multiVariante) {
      for (auto efecto : sonido.variaciones)
        Mix_FreeChunk(efecto);
      sonido.variaciones.clear();
    }
    else {
      Mix_FreeChunk(sonido.efecto);
      sonido.efecto = nullptr;
    }
  }
  else {
    if (musicaActual == id)
      detenerMusica();
    Mix_FreeMusic(sonido.musica);
    sonido.musica = nullptr;
  }

  sonidos.erase(id);
}

void SoundManager::liberarTodos()
{
  for (auto& par : sonidos) {
    if (par.second.tipo == EFECTO) {
      if (par.second.multiVariante) {
        for (auto efecto : par.second.variaciones)
          Mix_FreeChunk(efecto);
      }
      else {
        Mix_FreeChunk(par.second.efecto);
      }
    }
    else {
      Mix_FreeMusic(par.second.musica);
    }
  }
  sonidos.clear();
  musicaActual = "";
}

void SoundManager::limpiar()
{
  liberarTodos();
  if (listo) {
    Mix_CloseAudio();
    Mix_Quit();
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
    listo = false;
  }
}

bool SoundManager::musicaEnReproduccion() const
{
  return Mix_PlayingMusic() != 0;
}

bool SoundManager::musicaEnPausa() const
{
  return Mix_PausedMusic() != 0;
}