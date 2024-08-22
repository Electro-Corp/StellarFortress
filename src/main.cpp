/**
 * Temporary main.cpp
 * 
 * its not very good and exists only for testing
*/
#include <iostream>
#include <math.h>
#include <filesystem>
#include <SFML/Audio.hpp>

#include <scene.h>
#include <graphics/renderer.h>
#include <game.h>
#include <gameobject.h>

#include <gameObjects/ui/text.h>

//#include <map/map.h>

#include <thread>

namespace fs = std::filesystem;

bool renderLoad = false;

void tickThread(Game::SF* dsa){
	while(1){
		dsa->tick();
	}
}


int main(int argv, char** args){
	Game::SF* game = new Game::SF();

	Engine::Scene main("Main Menu", "../assets/scenes/mainMenu.json", game);
	Engine::Scene map("Test Map", "../assets/scenes/map.json", game);


	UI::Text fpsText("FPS");
	fpsText.rgb = RGB(255);
	fpsText.transform.scale = Transform::Vector2(200.0, 20.0);
	fpsText.transform.position = Transform::Vector2(0, 0);

	
	std::cout << "Entering main Render loop\n";

	game->mainMenu = std::unique_ptr<Engine::Scene>(&main);

	// Map test scene
	// Engine::Scene map("Map");

	// Map::Map map1(7, 7);

	// map.addObject(&map1);

	// map.addObject(&fpsText);
	
	// map.addObject(&cursor);

	game->scenes.push_back(std::unique_ptr<Engine::Scene>(&main));
	game->scenes.push_back(std::unique_ptr<Engine::Scene>(&map));
	//game->scenes.push_back(std::unique_ptr<Engine::Scene>(&map));

	game->setTickNum(0);
	
	int fps;
	while(1){
		fps = (int)(1000 / game->getDelta());
		fpsText.setText("FPS: " + std::to_string(fps) + " [LOCKED]");
		game->tick();
	}
	/*std::thread t1(&(tickThread), game);

	t1.join();*/
	
	return 0;
}