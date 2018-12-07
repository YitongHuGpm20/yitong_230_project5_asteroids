#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "GameObject.h"

using namespace sf;

class Asteroid : public GameObject
{
public:
	Vector2f pos;
	Vector2f vel;
	float radius = 70;
	float speed = 25;
	float rot;
	Texture tex;
	float green = 0;
	float blue = 0;

	virtual void update(float dt);
	virtual void draw();
	virtual Vector2f getCenter();
	virtual void checkCollisionWith(GameObject * obj);
	virtual string getName();
	virtual float getRadius();
	virtual bool isDead();
};

