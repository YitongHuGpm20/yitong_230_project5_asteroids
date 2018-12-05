#include "Ship.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

using namespace sf;

RectangleShape Ship::DrawShip(Texture &ship) {
	RectangleShape shape;
	shape.setPosition(pos);
	shape.setSize(size);
	shape.setTexture(&ship);
	shape.setOrigin(size.x / 2, size.y / 2);
	shape.setRotation(rot);
	return shape;
}