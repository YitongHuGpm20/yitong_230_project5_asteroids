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




GameLevel::GameLevel(int level) {
	tex_ship.loadFromFile("spaceship.png");
	buf_ship.loadFromFile("launch.wav");
	sou_ship.setBuffer(buf_ship);
	sou_ship.setVolume(50);
	buf_bullet.loadFromFile("bullet.wav");
	sou_bullet.setBuffer(buf_bullet);

	//setup asteroids
	for (int i = 0; i < 4; i++) {
		Asteroid* a = new Asteroid();
		a->tex.loadFromFile("asteroid.png");
		float angle = rand() % 360;
		a->vel.x = cos((angle * 3.1415926f) / 180);
		a->vel.y = sin((angle * 3.1415926f) / 180);
		do {
			a->pos.x = rand() % 1000 + 100;
			a->pos.y = rand() % 800 + 50;
		} while ((a->pos.x >= 550 && a->pos.x <= 650) || (a->pos.y >= 400 && a->pos.y <= 500));
		addGameObject(a);
	}
}

Vector2i getBucket(Vector2f pos) {
	int col = int(pos.x / BUCKET_WIDTH);
	if (col < 0)
		col = 0;
	else if (col >= COLUMNS)
		col = COLUMNS - 1;
	int row = int(pos.y / BUCKET_HEIGHT);
	if (row < 0)
		row = 0;
	else if (row >= ROWS)
		row = ROWS - 1;
	return Vector2i(col, row);
}

void GameLevel::bucket_add(Vector2i b, GameObject* obj) {
	vector<GameObject*>& v = grid[b.x][b.y];
	v.push_back(obj);
}

void GameLevel::bucket_remove(Vector2i b, GameObject* obj) {
	vector<GameObject*>& v = grid[b.x][b.y];
	for (int i = 0; i < v.size(); ++i) {
		if (v[i] == obj) {
			v.erase(v.begin() + i);
			break;
		}
	}
}

void GameLevel::detect_collisions(GameObject* obj, Vector2i b) {
	int left = max(b.x - 1, 0);
	int right = min(b.x + 1, COLUMNS - 1);
	int top = max(b.y - 1, 0);
	int bot = min(b.y + 1, ROWS - 1);
	for (int bx = left; bx <= right; ++bx) {
		for (int by = top; by <= bot; ++by) {
			vector<GameObject*> & v = grid[bx][by];
			for (GameObject* o : v) {
				if (o != obj)
					obj->checkCollisionWith(o);
			}
		}
	}
}

void GameLevel::addGameObject(GameObject* obj)
{
	objects.push_back(obj);
	bucket_add(getBucket(obj->getCenter()), obj);
}

AppState* GameLevel::update_state(float dt) {	
	//Bucket Grid
	for (int i = 0; i < objects.size(); ++i) {
		GameObject * obj = objects[i];
		Vector2i curBucket = getBucket(obj->getCenter());
		obj->update(dt);
		Vector2i newBucket = getBucket(obj->getCenter());
		if (curBucket != newBucket) {
			bucket_remove(curBucket, obj);
			bucket_add(newBucket, obj);
		}
		detect_collisions(obj, newBucket);
	}
		
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
	

	//update positions of objects
	ship.pos.x += ship.vel.x * dt * ship.speed;
	ship.pos.y += ship.vel.y * dt * ship.speed;
	for (int i = 0; i < 100; i++) {
		bullet[i].pos.x += bullet[i].vel.x * dt * bullet[i].speed * 300;
		bullet[i].pos.y += bullet[i].vel.y * dt * bullet[i].speed * 300;
	}
	

	if (count < 300)
		count++;

	return nullptr;
}

void GameLevel::render_frame() {
	for (int i = 0; i < objects.size(); ++i)
		objects[i]->draw();
	
	window.draw(ship.DrawShip(tex_ship, red, green, blue));
	for (int i = 0; i < 100; i++)
		window.draw(bullet[i].DrawBullet());
}