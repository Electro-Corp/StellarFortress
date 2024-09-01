#include "transform.h"

Vector2::Vector2(){
    x = 0;
    y = 0;
}

Vector2::Vector2(float x, float y) : x(x), y(y){

}

Transform::Transform(){
    this->angle = 0;
    this->scale.x = 1;
    this->scale.y = 1;
}

Transform::Transform(float x, float y, float ang){
    this->position.x = x;
    this->position.y = y;
    this->angle = ang;
    this->scale.x = 1;
    this->scale.y = 1;
}

Transform::Transform(Vector2 pos, float ang){
    this->position = pos;
    this->angle = ang;
    this->scale.x = 1;
    this->scale.y = 1;
}

Vector2 Vector2::operator+(Vector2 other){
    // Add the vectors
    return Vector2(this->x + other.x, this->y + other.y);
}