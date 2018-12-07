#include "Ship.h"

template<typename T>
T lerp(T start, T end, float t) {
	return start + (end - start) * t;
}
template<typename T>
T easeOut(T start, T end, float t) {
	--t;
	return start + (end - start) * (t * t * t + 1);
}

extern RenderWindow window;

void Ship::update(float dt)
{
	//player control
	if (Keyboard::isKeyPressed(Keyboard::Left))
		rot += -0.5f;
	if (Keyboard::isKeyPressed(Keyboard::Right))
		rot += 0.5f;
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		vel.x += cos(((rot - 90) * 3.1415926f) / 180) * dt;
		vel.y += sin(((rot - 90) * 3.1415926f) / 180) * dt;
		red = 255;
		blue = 255;
		if (sou.getStatus() != Sound::Playing)
			sou.play();
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		vel.x -= cos(((rot - 90) * 3.1415926f) / 180) * dt;
		vel.y -= sin(((rot - 90) * 3.1415926f) / 180) * dt;
		red = 255;
		blue = 255;
		if (sou.getStatus() != Sound::Playing)
			sou.play();
	}
	
	//slow down
	vel.x = lerp(vel.x, 0.f, dt);
	vel.y = lerp(vel.y, 0.f, dt);

	//speed up
	red = easeOut(red, 200.f, dt);
	blue = easeOut(blue, 0.f, dt);

	//wrap around map
	if (pos.x <= -size.x)
		pos.x = window.getSize().x;
	if (pos.x >= window.getSize().x + size.x)
		pos.x = 0;
	if (pos.y <= -size.y)
		pos.y = window.getSize().y;
	if (pos.y >= window.getSize().y + size.y)
		pos.y = 0;

	//update positions of objects
	pos.x += vel.x * dt * speed;
	pos.y += vel.y * dt * speed;

	if (count < 300)
		count++;
}

void Ship::draw()
{
	RectangleShape shape;
	shape.setPosition(pos);
	shape.setSize(size);
	shape.setTexture(&tex);
	shape.setOrigin(size.x / 2, size.y / 2);
	shape.setRotation(rot);
	shape.setFillColor(Color(red, green, blue));
	window.draw(shape);
}

Vector2f Ship::getCenter()
{
	return pos;
}

void Ship::checkCollisionWith(GameObject * obj)
{
	//collide with asteroids and destroyed
}

string Ship::getName()
{
	return "ship";
}

float Ship::getRadius()
{
	return 20.f;
}

bool Ship::isDead()
{
	return reallyDead;
}
