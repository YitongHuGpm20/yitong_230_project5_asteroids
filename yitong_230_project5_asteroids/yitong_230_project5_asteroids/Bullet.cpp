#include "Bullet.h"
#include <cmath>

extern Ship* s;
extern RenderWindow window;
extern bool boom;
extern Vector2f boomPos;
extern bool isBig;
extern bool isMid;
extern bool isSma;
float length(Vector2f v) {
	return sqrtf(v.x*v.x + v.y*v.y);
}

void Bullet::update(float dt) {
	if (pos.x <= -size.x)
		pos.x = window.getSize().x;
	if (pos.x >= window.getSize().x + size.x)
		pos.x = 0;
	if (pos.y <= -size.y)
		pos.y = window.getSize().y;
	if (pos.y >= window.getSize().y + size.y)
		pos.y = 0;
	pos.x += vel.x * dt * speed * 300;
	pos.y += vel.y * dt * speed * 300;
}

void Bullet::draw() {
	RectangleShape shape;
	shape.setPosition(pos);
	shape.setSize(size);
	shape.setRotation(rot);
	shape.setFillColor(Color::Yellow);
	shape.setOrigin(size.x / 2, size.y / 2);
	window.draw(shape);
}

Vector2f Bullet::getCenter() {
	return pos;
}

void Bullet::checkCollisionWith(GameObject * obj) {
	float dis = length(this->getCenter() - obj->getCenter());
	if (dis <= this->getRadius() + obj->getRadius() && obj->getName() == "asteroid") {
		boom = true;
		boomPos = obj->getCenter();
		reallyDead = true;
		obj->reallyDead = true;
		if (obj->getRadius() == 35) {
			isBig = false;
			isMid = true;
			isSma = false;
		}
		else if (obj->getRadius() == 17.5) {
			isBig = false;
			isMid = false;
			isSma = true;
		}
	}
}

string Bullet::getName() {
	return "bullet";
}

float Bullet::getRadius() {
	return 2.5f;
}

bool Bullet::isDead() {
	return reallyDead;
}
