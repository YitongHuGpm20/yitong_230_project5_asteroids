#include "Ship.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

using namespace sf;

template<typename T>
T easeOut(T start, T end, float t)
{
	--t;
	return start + (end - start) *
		(t * t * t + 1);
}

RectangleShape Ship::DrawShip(Texture &ship, float red, float green, float blue) {
	RectangleShape shape;
	shape.setPosition(pos);
	shape.setSize(size);
	shape.setTexture(&ship);
	shape.setOrigin(size.x / 2, size.y / 2);
	shape.setRotation(rot);
	shape.setFillColor(Color(red, green, blue));
	return shape;
}

void Ship::SpeedUp(float dt, RectangleShape shape) {
	float red = easeOut(255.f, 0.f, dt);
	shape.setFillColor(Color(red, 0, 0));
}