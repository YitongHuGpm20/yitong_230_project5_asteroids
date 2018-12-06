#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "AppState.h"
#include "MyButton.h"
#include <vector>
#include <memory>

using namespace sf;

class MainMenu : public AppState
{
private:
	MyButton newGame;
	MyButton quit;
public:
	MainMenu();
	virtual AppState* update_state(float dt);
	virtual void render_frame();
};