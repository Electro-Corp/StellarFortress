/*
  Stores the map
*/
#pragma once

#include <gameObjects/terrain/tile.h>

#include <vector>

#include <gameobject.h>
#include <rgb.h>

namespace Map{
  class MapRow{
  public:
    MapRow(int y, int width);
  
    std::vector<Game::Tile> row;

    Game::Tile operator[](int i);
  };
  class Map : public Engine::GameObject{
  private:
  public:
    Map(int width, int height);
  
    std::vector<MapRow> rows;

    MapRow operator[](int i);

    void update() override;
    
  #if USE_SFML
    void draw(sf::RenderWindow* window) override;
  #endif
  #if USE_SDL
    void draw(SDL_Renderer* window) override;
  #endif
  };
}