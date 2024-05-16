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
#include <map/map.h>

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

	// Create Main Menu Scene
	Engine::Scene mainMenu("Main Menu");

	Engine::GameObject menuBG("../assets/textures/menu/space.png");
	
	Engine::GameObject logoPt1("../assets/textures/menu/STELLAR.png");
	game->loadScript(&logoPt1, "../assets/scripts/scenes/mainlogo/logoTOP.lua");
	
	Engine::GameObject logoPt2("../assets/textures/menu/FORTRESS.png");
	game->loadScript(&logoPt2, "../assets/scripts/scenes/mainlogo/logoBOT.lua");


	// MAKE SURE TO ADD CURSOR TO EVERY SCENE
	Engine::GameObject cursor("../assets/textures/menu/cursor.png");
	game->loadScript(&cursor, "../assets/scripts/scenes/mainlogo/cursor.lua");

	menuBG.transform.scale = Transform::Vector2(800.0, 600.0);
	logoPt1.transform.position = Transform::Vector2(-800.0, 800.0);
	logoPt2.transform.position = Transform::Vector2(-800.0, -500.0);

	UI::Text playText("Press any key to begin...");
	game->loadScript(&playText, "../assets/scripts/scenes/mainlogo/playtext.lua");
	playText.rgb = RGB(255);
	playText.transform.scale = Transform::Vector2(500.0, 50.0);
	playText.transform.position = Transform::Vector2(135.0, 500);

	UI::Text fpsText("FPS");
	fpsText.rgb = RGB(255);
	fpsText.transform.scale = Transform::Vector2(200.0, 20.0);
	fpsText.transform.position = Transform::Vector2(0, 0);

	// Add them in render order
	mainMenu.addObject(&menuBG);
	mainMenu.addObject(&logoPt1);
	mainMenu.addObject(&logoPt2);
	mainMenu.addObject(&playText);	
	mainMenu.addObject(&fpsText);

	// always render last
	mainMenu.addObject(&cursor);
	
	std::cout << "Entering main Render loop\n";

	game->mainMenu = std::unique_ptr<Engine::Scene>(&mainMenu);

	// Map test scene
	Engine::Scene map("Map");

	Map::Map map1(7, 7);

	map.addObject(&map1);

	map.addObject(&fpsText);
	
	map.addObject(&cursor);

	
	int fps;
	while(1){
		fps = (int)(1000 / game->getDelta());
		fpsText.setText("FPS: " + std::to_string(fps) + " [LOCKED]");
		game->tick(map);
	}
	/*std::thread t1(&(tickThread), game);

	t1.join();*/
	
	return 0;
}