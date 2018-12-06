#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "GameObject.h"
#include "Ship.h"

using namespace sf;

class Bullet : public GameObject
{
public:
	float speed = 600;
	float rot = 0;
	Vector2f size = Vector2f(5, 10);
	Vector2f pos = Vector2f(-100, -100);
	Vector2f vel = Vector2f(0, 0);
	SoundBuffer buf;
	Sound sou;

	virtual void update(float dt);
	virtual void draw();
	virtual Vector2f getCenter();
	virtual void checkCollisionWith(GameObject * obj);
	virtual string getName();
	virtual float getRadius();
};

