/**
 * Temporary main.cpp
 * 
 * its not very good and exists only for testing
*/
#include <iostream>
#include <math.h>
#include <filesystem>
#include <SFML/Audio.hpp>

#include <graphics/renderer.h>
#include <scene.h>
#include <game.h>

#include <gameObjects/ui/text.h>

#include <thread>

namespace fs = std::filesystem;

bool renderLoad = false;

void renderScreen(Game::SF* dsa, Engine::Scene* scene){
	while(renderLoad){
		dsa->tick(*scene);
	}
}


int main(int argv, char** args){
	Game::SF* game = new Game::SF();

	Engine::Scene scene("Test");

	Engine::GameObject gameObj("../assets/textures/testing/testBoat.jpeg");

	gameObj.transform.scale = Transform::Vector2(100.0, 100.0);
	gameObj.drawable = true;

	scene.addObject(&gameObj);


	while(1){
		game->tick(scene);
	}
	return 0;
}