#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

using namespace sf;

class Asteroid
{
public:
	Vector2f pos;
	Vector2f vel;
	float radius = 70;
	float speed = 50;
	float rot;

	CircleShape DrawAst(Texture&);
};

