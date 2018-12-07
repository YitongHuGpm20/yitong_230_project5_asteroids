#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "Ship.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "AppState.h"
#include "MainMenu.h"
#include "GameLevel.h"
#include <ctime>
#include <vector>
#include <memory>

using namespace sf;

RenderWindow window;
int count = 300;

int main()
{
	window.create(VideoMode(1200, 900), "Yitong's Spaceship War Game");
	Clock clock;
	
	srand(time(0));

	unique_ptr<AppState> curState(new MainMenu());

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		float dt = clock.restart().asSeconds();
		window.clear();
		AppState* next = curState->update_state(dt);
		curState->render_frame();
		window.display();

		if (next != nullptr)
			curState.reset(next);
	}
	return 0;
}