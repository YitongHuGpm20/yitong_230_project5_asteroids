#include "MainMenu.h"
#include "AppState.h"
#include "GameLevel.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <vector>
#include <algorithm>
#include <memory>

using namespace sf;

extern RenderWindow window;

MainMenu::MainMenu():newGame(Vector2f(500, 300), "New Game"), quit(Vector2f(550, 400), "Quit") {
	
}

AppState* MainMenu::update_state(float dt)
{
	if (quit.isClicked())
		window.close();
	if (newGame.isClicked())
		return new GameLevel(1);
	return nullptr;
}

void MainMenu::render_frame()
{
	window.clear();
	newGame.DrawButton();
	quit.DrawButton();
}