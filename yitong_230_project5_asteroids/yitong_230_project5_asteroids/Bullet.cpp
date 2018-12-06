#include "Bullet.h"

RectangleShape Bullet::DrawBullet() {
	RectangleShape shape;
	shape.setPosition(pos);
	shape.setSize(size);
	shape.setRotation(rot);
	shape.setFillColor(Color::Yellow);
	return shape;
}