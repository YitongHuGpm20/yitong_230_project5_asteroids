#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "GameObject.h"
#include <string>

using namespace sf;
using namespace std;

class MyButton
{
public:
	MyButton(Vector2f, string);
	Text name;

	bool isHover(Vector2f, FloatRect);
	bool isClicked();
	void DrawButton();
};

