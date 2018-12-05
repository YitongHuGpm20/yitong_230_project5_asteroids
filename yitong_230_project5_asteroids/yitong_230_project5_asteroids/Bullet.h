#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

using namespace sf;

class Bullet
{
public:
	float speed = 600;
	float rot = 0;
	Vector2f size = Vector2f(5, 10);
	Vector2f pos;
	Vector2f vel = Vector2f(0, 0);

	RectangleShape DrawBullet();
};

