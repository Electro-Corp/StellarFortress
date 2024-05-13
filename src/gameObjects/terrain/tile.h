/*
  Header for tiles
*/
#pragma once

#include <gameobject.h>
#include <rgb.h>

namespace Game{
  class Tile : public Engine::GameObject {
      private:

      public:
          RGB rgb;

          Tile();

          void update() override;

  #if USE_SFML
          void draw(sf::RenderWindow* window) override;
  #endif
  #if USE_SDL
          void draw(SDL_Renderer* window) override;
  #endif

    };
}