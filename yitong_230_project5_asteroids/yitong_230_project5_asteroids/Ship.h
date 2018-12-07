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

class Ship : public GameObject
{
public:
	float speed = 500;
	float rot = 0;
	Vector2f size = Vector2f(40, 60);
	Vector2f pos = Vector2f(600 - 20, 450 - 30);
	Vector2f vel = Vector2f(0, 0);
	Texture tex;
	SoundBuffer buf;
	Sound sou;
	float green = 255;
	float red = 200;
	float blue = 0;
	int count = 300;

	virtual void update(float dt);
	virtual void draw();
	virtual Vector2f getCenter();
	virtual void checkCollisionWith(GameObject * obj);
	virtual string getName();
	virtual float getRadius();
	virtual bool isDead();
};

