#include "Bullet.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

using namespace sf;

RectangleShape Bullet::DrawBullet() {
	RectangleShape shape;
	shape.setPosition(pos);
	shape.setSize(size);
	shape.setRotation(rot);
	shape.setFillColor(Color::Yellow);
	return shape;
}