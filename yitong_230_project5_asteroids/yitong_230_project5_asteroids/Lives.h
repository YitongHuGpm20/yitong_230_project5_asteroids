#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

using namespace sf;

class Lives
{
public:
	Vector2f size = Vector2f(20, 30);
	float space = 30;
	Vector2f loc;

	RectangleShape DrawLives(Texture&);
};

