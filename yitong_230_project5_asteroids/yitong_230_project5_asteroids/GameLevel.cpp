#include "GameLevel.h"

extern RenderWindow window;

Ship* s = new Ship();

GameLevel::GameLevel(int level) {
	//setup ship
	s->tex.loadFromFile("spaceship.png");
	s->buf.loadFromFile("launch.wav");
	s->sou.setBuffer(s->buf);
	s->sou.setVolume(50);
	addGameObject(s);

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

	//switch scenes
	//if (lives <= 0)
		//return new GameOverScreen();
	if (enemiesRemaining <= 0)
		return new GameLevel(level + 1);
	if (Keyboard::isKeyPressed(Keyboard::Escape))
		return new MainMenu();

	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		if (s->count == 300) {
			Bullet* b = new Bullet();
			b->buf.loadFromFile("bullet.wav");
			b->sou.setBuffer(b->buf);
			b->sou.setVolume(20);
			b->pos = s->pos;
			b->rot = s->rot;
			b->vel.x += cos(((s->rot - 90) * 3.1415926f) / 180) * dt;
			b->vel.y += sin(((s->rot - 90) * 3.1415926f) / 180) * dt;
			s->count = 0;
			b->sou.play();
			addGameObject(b);
		}
	}

	return nullptr;
}

void GameLevel::render_frame() {
	for (int i = 0; i < objects.size(); ++i)
		objects[i]->draw();
}