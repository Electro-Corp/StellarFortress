#include "tile.h"

Game::Tile::Tile(){
  
}

void Game::Tile::update(){
  updateScript();
  updateTransform();
}


#if USE_SDL
void Game::Tile::draw(SDL_Renderer* window){
  SDL_SetRenderDrawColor(window, rgb.r, rgb.g, rgb.b, 255);
  SDL_RenderFillRect(window, &texture_rect);
}
#endif
