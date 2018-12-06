#include "Ship.h"

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