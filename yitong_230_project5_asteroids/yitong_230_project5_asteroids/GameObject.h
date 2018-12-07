#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <string>

using namespace sf;
using namespace std;

class GameObject
{
public:
	bool reallyDead = false;

	virtual void update(float dt) = 0;
	virtual void draw() = 0;
	virtual Vector2f getCenter() = 0;
	virtual void checkCollisionWith(GameObject * obj) = 0;
	virtual string getName() = 0;
	virtual float getRadius() = 0;
	virtual bool isDead() = 0;
};
