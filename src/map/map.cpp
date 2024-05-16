#include <map/map.h>


Map::MapRow::MapRow(int y, int width){
  for(int x = 0; x < width; x++){
    Game::Tile tile(RGB(0, 255, 0, 255));
    tile.transform.scale = Transform::Vector2(100, 100);
    tile.transform.position = Transform::Vector2(x * tile.transform.scale.x, y * tile.transform.scale.y);
    tile.update();
    this->row.push_back(tile);
  }
}

Map::Map::Map(int width, int height){
  // Replace with actual generation
  for(int y = 0; y < height; y++){
    this->rows.push_back(MapRow(y, width));
  }
}

Map::MapRow Map::Map::operator[](int i){
    return this->rows[i];
}


Game::Tile Map::MapRow::operator[](int i){
    return this->row[i];
}

void Map::Map::update(){
  // Update each tile 
}

void Map::Map::draw(SDL_Renderer* window){
  // Render each tile
  for(int y = 0; y < this->rows.size(); y++){
    for(int x = 0; x < this->rows[y].row.size(); x++){
      this->rows[y].row[x].draw(window);
    }
  }
}