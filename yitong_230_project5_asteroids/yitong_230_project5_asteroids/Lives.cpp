#include "Lives.h"

RectangleShape Lives::DrawLives(Texture &ship)
{
	RectangleShape shape;
	loc.y = 900 - size.y - 10;
	shape.setPosition(loc);
	shape.setSize(size);
	shape.setTexture(&ship);
	return shape;
}
