#include "Asteroid.h"

extern RenderWindow window;

void Asteroid::update(float dt)
{
	if (pos.x <= -radius * 2)
		pos.x = window.getSize().x;
	if (pos.x >= window.getSize().x + radius * 2)
		pos.x = 0;
	if (pos.y <= -radius * 2)
		pos.y = window.getSize().y;
	if (pos.y >= window.getSize().y + radius * 2)
		pos.y = 0;
	pos.x += vel.x * dt * speed;
	pos.y += vel.y * dt * speed;
}

void Asteroid::draw()
{
	CircleShape shape;
	shape.setPosition(pos);
	shape.setRadius(radius);
	shape.setTexture(&tex);
	shape.setOrigin(radius / 2, radius / 2);
	shape.setRotation(rot);
	window.draw(shape);
}

Vector2f Asteroid::getCenter()
{
	return pos;
}

void Asteroid::checkCollisionWith(GameObject * obj)
{
	//check collid with bullets
}

string Asteroid::getName()
{
	return "asteroid";
}

float Asteroid::getRadius()
{
	return radius;
}
