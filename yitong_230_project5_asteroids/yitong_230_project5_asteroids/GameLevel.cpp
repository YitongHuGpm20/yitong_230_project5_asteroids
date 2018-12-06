#include "GameLevel.h"

template<typename T>
T lerp(T start, T end, float t) {
	return start + (end - start) * t;
}
template<typename T>
T easeOut(T start, T end, float t) {
	--t;
	return start + (end - start) * (t * t * t + 1);
}

extern RenderWindow window;

GameLevel::GameLevel(int level)
{
	tex_ship.loadFromFile("spaceship.png");
	buf_ship.loadFromFile("launch.wav");
	sou_ship.setBuffer(buf_ship);
	sou_ship.setVolume(50);
	buf_bullet.loadFromFile("bullet.wav");
	sou_bullet.setBuffer(buf_bullet);
	tex_ast.loadFromFile("asteroid.png");

	//setup asteroids
	for (int i = 0; i < 4; i++) {
		float angle = rand() % 360;
		asteroid[i].vel.x = cos((angle * 3.1415926f) / 180);
		asteroid[i].vel.y = sin((angle * 3.1415926f) / 180);
		do {
			asteroid[i].pos.x = rand() % 1000 + 100;
			asteroid[i].pos.y = rand() % 800 + 50;
		} while ((asteroid[i].pos.x >= 550 && asteroid[i].pos.x <= 650) || (asteroid[i].pos.y >= 400 && asteroid[i].pos.y <= 500));
	}
}

AppState* GameLevel::update_state(float dt)
{	
	for (int i = 0; i < objs.size(); ++i)
		objs[i]->update(dt);
	//if (lives <= 0)
		//return new GameOverScreen();
	if (enemiesRemaining <= 0)
		return new GameLevel(level + 1);
	if (Keyboard::isKeyPressed(Keyboard::Escape))
		return new MainMenu();

	//player control
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		ship.rot += -0.5f;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		ship.rot += 0.5f;
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		ship.vel.x += cos(((ship.rot - 90) * 3.1415926f) / 180) * dt;
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
	for (int i = 0; i < 4; i++) {
		if (asteroid[i].pos.x <= -asteroid[i].radius * 2)
			asteroid[i].pos.x = window.getSize().x;
		if (asteroid[i].pos.x >= window.getSize().x + asteroid[i].radius * 2)
			asteroid[i].pos.x = 0;
		if (asteroid[i].pos.y <= -asteroid[i].radius * 2)
			asteroid[i].pos.y = window.getSize().y;
		if (asteroid[i].pos.y >= window.getSize().y + asteroid[i].radius * 2)
			asteroid[i].pos.y = 0;
	}

	//update positions of objects
	ship.pos.x += ship.vel.x * dt * ship.speed;
	ship.pos.y += ship.vel.y * dt * ship.speed;
	for (int i = 0; i < 100; i++) {
		bullet[i].pos.x += bullet[i].vel.x * dt * bullet[i].speed * 300;
		bullet[i].pos.y += bullet[i].vel.y * dt * bullet[i].speed * 300;
	}
	for (int i = 0; i < 4; i++) {
		asteroid[i].pos.x += asteroid[i].vel.x * dt * asteroid[i].speed;
		asteroid[i].pos.y += asteroid[i].vel.y * dt * asteroid[i].speed;
	}

	if (count < 300)
		count++;

	return nullptr;
}

void GameLevel::render_frame()
{
	for (int i = 0; i < objs.size(); ++i)
		objs[i]->draw();
	
	window.draw(ship.DrawShip(tex_ship, red, green, blue));
	for (int i = 0; i < 100; i++)
		window.draw(bullet[i].DrawBullet());
	for (int i = 0; i < 4; i++)
		window.draw(asteroid[i].DrawAst(tex_ast));
}
