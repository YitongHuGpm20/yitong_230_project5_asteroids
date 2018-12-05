#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "Ship.h"
#include "Bullet.h"
#include <ctime>

using namespace sf;

template<typename T>
T lerp(T start, T end, float t) {
	return start + (end - start) * t;
}
template<typename T>
T easeOut(T start, T end, float t) {
	--t;
	return start + (end - start) * (t * t * t + 1);
}

void update_state(float dt);
void render_frame();

RenderWindow window;
Ship ship;
Texture tex_ship;
SoundBuffer buf_ship;
Sound sou_ship;
Bullet bullet[100];
SoundBuffer buf_bullet;
Sound sou_bullet;
float green = 255;
float red = 200;
float blue = 0;
bool play_sou_ship = false;
int bulletNum = 0;
int count = 300;

int main()
{
	window.create(VideoMode(1200, 900), "Yitong's Spaceship War Game");
	Clock clock;
	tex_ship.loadFromFile("spaceship.png");
	buf_ship.loadFromFile("launch.wav");
	sou_ship.setBuffer(buf_ship);
	sou_ship.setVolume(50);
	buf_bullet.loadFromFile("bullet.wav");
	sou_bullet.setBuffer(buf_bullet);

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
		if(count < 300)
			count++;
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
		ship.vel.x += cos(((ship.rot-90) * 3.1415926f) / 180) * dt;
		ship.vel.y += sin(((ship.rot - 90) * 3.1415926f) / 180) * dt;
		red = 255;
		blue = 255;
		if (sou_ship.getStatus() != Sound::Playing) {
			sou_ship.play();
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		ship.vel.x -= cos(((ship.rot - 90) * 3.1415926f) / 180) * dt;
		ship.vel.y -= sin(((ship.rot - 90) * 3.1415926f) / 180) * dt;
		red = 255;
		blue = 255;
		if (sou_ship.getStatus() != Sound::Playing) {
			sou_ship.play();
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		if (count == 300 && bulletNum < 100) {
			bullet[bulletNum].pos = ship.pos;
			bullet[bulletNum].vel.x += cos(((ship.rot - 90) * 3.1415926f) / 180) * dt;
			bullet[bulletNum].vel.y += sin(((ship.rot - 90) * 3.1415926f) / 180) * dt;
			bullet[bulletNum].rot = ship.rot;
			bulletNum++;
			count = 0;
			sou_bullet.play();
		}
	}

	//slow down
	ship.vel.x = lerp(ship.vel.x, 0.f, dt);
	ship.vel.y = lerp(ship.vel.y, 0.f, dt);
	
	//speed up
	red = easeOut(red, 200.f, dt);
	blue = easeOut(blue, 0.f, dt);

	//wrap around map
	if (ship.pos.x <= -ship.size.x)
		ship.pos.x = window.getSize().x;
	if (ship.pos.x >= window.getSize().x + ship.size.x)
		ship.pos.x = 0;
	if (ship.pos.y <= -ship.size.y)
		ship.pos.y = window.getSize().y;
	if (ship.pos.y >= window.getSize().y + ship.size.y)
		ship.pos.y = 0;
	for (int i = 0; i < 100; i++) {
		if (bullet[i].pos.x <= -bullet[i].size.x)
			bullet[i].pos.x = window.getSize().x;
		if (bullet[i].pos.x >= window.getSize().x + bullet[i].size.x)
			bullet[i].pos.x = 0;
		if (bullet[i].pos.y <= -bullet[i].size.y)
			bullet[i].pos.y = window.getSize().y;
		if (bullet[i].pos.y >= window.getSize().y + bullet[i].size.y)
			bullet[i].pos.y = 0;
	}

	ship.pos.x += ship.vel.x * dt * ship.speed;
	ship.pos.y += ship.vel.y * dt * ship.speed;
	for (int i = 0; i < 100; i++) {
		bullet[i].pos.x += bullet[i].vel.x * dt * bullet[i].speed * 300;
		bullet[i].pos.y += bullet[i].vel.y * dt * bullet[i].speed * 300;
	}
}

void render_frame()
{
	window.clear();
	window.draw(ship.DrawShip(tex_ship, red, green, blue));
	for (int i = 0; i < 100; i++)
		window.draw(bullet[i].DrawBullet());
}