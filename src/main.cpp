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

	UI::Text playText("Press any key to continue...");
	game->loadScript(&playText, "../assets/scripts/scenes/mainlogo/playtext.lua");
	playText.rgb = RGB(255);
	playText.transform.scale = Transform::Vector2(500.0, 50.0);
	playText.transform.position = Transform::Vector2(135.0, 500);

	// Add them in render order
	mainMenu.addObject(&menuBG);
	mainMenu.addObject(&logoPt1);
	mainMenu.addObject(&logoPt2);
	mainMenu.addObject(&playText);
	mainMenu.addObject(&cursor);

	
	
	Engine::Scene scene("Test");

	Engine::GameObject gameObj("../assets/textures/load.png");
	game->loadScript(&gameObj, "../assets/scripts/testing/test.lua");

	UI::Text testText("Hello World!");
	testText.rgb = RGB(255);
	testText.transform.scale = Transform::Vector2(100.0, 100.0);

	gameObj.transform.scale = Transform::Vector2(800.0, 600.0);
	gameObj.drawable = true;

	scene.addObject(&gameObj);
	scene.addObject(&testText);


	std::cout << "Entering main Render loop\n";
	while(1){
		game->tick(mainMenu);
	}
	return 0;
}