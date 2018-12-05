#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "Ship.h";

using namespace sf;

template<typename T>
T lerp(T start, T end, float t)
{
	return start + (end - start) * t;
}


void update_state(float dt);
void render_frame();

RenderWindow window;
Ship ship;
Texture tex_ship;

int main()
{
	window.create(VideoMode(1200, 900), "Yitong's Spaceship War Game");
	Clock clock;
	tex_ship.loadFromFile("spaceship.png");

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		float dt = clock.restart().asSeconds();
		update_state(dt);
		render_frame();
		window.display();
	}
	return 0;
}

void update_state(float dt)
{
	//player control
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		ship.rot += -0.5f;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		ship.rot += 0.5f;
	}	
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		ship.vel.x += cos(((ship.rot-90) * 3.1415926f) / 180) *dt;
		ship.vel.y += sin(((ship.rot - 90) * 3.1415926f) / 180)*dt;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		ship.vel.x -= cos(((ship.rot - 90) * 3.1415926f) / 180)*dt;
		ship.vel.y -= sin(((ship.rot - 90) * 3.1415926f) / 180)*dt;
	}	

	//slow down
	ship.vel.x = lerp(ship.vel.x, 0.f, dt);
	ship.vel.y = lerp(ship.vel.y, 0.f, dt);

	if (ship.pos.x <= -ship.size.x)
		ship.pos.x = window.getSize().x;
	if (ship.pos.x >= window.getSize().x + ship.size.x)
		ship.pos.x = 0;
	if (ship.pos.y <= -ship.size.y)
		ship.pos.y = window.getSize().y;
	if (ship.pos.y >= window.getSize().y + ship.size.y)
		ship.pos.y = 0;

	ship.pos.x += ship.vel.x * dt * ship.speed;
	ship.pos.y += ship.vel.y * dt * ship.speed;
}

void render_frame()
{
	window.clear();
	window.draw(ship.DrawShip(tex_ship));
}