#include "Asteroid.h"

extern RenderWindow window;

template<typename T>
T lerp(T start, T end, float t) {
	return start + (end - start) * t;
}
template<typename T>
T easeOut(T start, T end, float t) {
	--t;
	return start + (end - start) * (t * t * t + 1);
}

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
	if (this->getRadius() == 70) {
		speed = lerp(speed, 75.f, dt);
	}
	else if (this->getRadius() == 35) {
		speed = lerp(speed, 100.f, dt);
	}
	else if (this->getRadius() == 17.5) {
		speed = lerp(speed, 125.f, dt);
	}
	green = easeOut(green, 255.f, dt);
	blue = easeOut(blue, 255.f, dt);
}

void Asteroid::draw()
{
	CircleShape shape;
	shape.setPosition(pos);
	shape.setRadius(radius);
	shape.setTexture(&tex);
	shape.setOrigin(radius, radius);
	shape.setRotation(rot);
	shape.setFillColor(Color(255, green, blue));
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

bool Asteroid::isDead()
{
	return reallyDead;
}
