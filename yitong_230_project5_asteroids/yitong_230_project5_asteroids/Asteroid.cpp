#include "Asteroid.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

using namespace sf;

CircleShape Asteroid::DrawAst(Texture &stone) {
	CircleShape shape;
	shape.setPosition(pos);
	shape.setRadius(radius);
	shape.setTexture(&stone);
	shape.setOrigin(radius / 2, radius / 2);
	shape.setRotation(rot);
	return shape;
}