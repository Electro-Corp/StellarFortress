#include "tile.h"

Game::Tile::Tile(RGB color){
  this->rgb = color;
}

void Game::Tile::update(){
  updateScript();
  updateTransform();
}


#if USE_SDL
void Game::Tile::draw(SDL_Renderer* window){
  SDL_SetRenderDrawColor(window, rgb.r, rgb.g, rgb.b, 255);
  SDL_RenderFillRect(window, &texture_rect);
  SDL_SetRenderDrawColor(window, 255, 0, 0, 255);
  SDL_RenderDrawRect(window, &texture_rect);
  //SDL_RenderDrawRect(window, &texture_rect);
}
#endif
