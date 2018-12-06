#pragma once
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

class AppState
{
public:
	virtual AppState* update_state(float dt) = 0;
	virtual void render_frame() = 0;
};

