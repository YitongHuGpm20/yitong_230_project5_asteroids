#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

using namespace sf;

class Ship
{
public:
	float speed = 500;
	float rot = 0;
	Vector2f size = Vector2f(40, 60);
	Vector2f pos = Vector2f(600 - 20, 450 - 30);
	Vector2f vel = Vector2f(0, 0);

	RectangleShape DrawShip(Texture&, float, float, float);
	void SpeedUp(float, RectangleShape);
};

