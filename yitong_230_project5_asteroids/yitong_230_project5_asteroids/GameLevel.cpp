#include "GameLevel.h"

extern RenderWindow window;

Ship* s = new Ship();
bool boom = false;
Vector2f boomPos;
int co1, co2;
bool isBig = true;
bool isMid = false;
bool isSma = false;
SoundBuffer buf_ast;
Sound sou_ast;
bool shipDead = false;
Lives lives[3];
int livesLeft = 3;
int level = 1;
int enemiesRemaining = 4 + level - 1;
Texture tex_ship;

GameLevel::GameLevel(int level) {
	buf_ast.loadFromFile("boom_asteroid.wav");
	sou_ast.setBuffer(buf_ast);
	for (int i = 0; i < 10; i++)
		lives[i].loc.x = 10 + lives[i].space * i;
	tex_ship.loadFromFile("spaceship.png");
	
	//setup ship
	s->tex.loadFromFile("spaceship.png");
	s->buf.loadFromFile("launch.wav");
	s->sou.setBuffer(s->buf);
	s->buf_dead.loadFromFile("shipdie.wav");
	s->sou_dead.setBuffer(s->buf_dead);
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

void GameLevel::deleteGameObject(GameObject* obj, int i) {
	bucket_remove(getBucket(obj->getCenter()), obj);
	objects.erase(objects.begin() + i);
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
		if (obj->isDead()) {
			for (int i = 0; i < objects.size(); ++i) {
				if (objects[i] == obj) {
					deleteGameObject(obj, i);
					break;
				}
			}
		}
	}

	//check if shot an asteroid
	if (boom) {
		sou_ast.play();
		if (!isSma) {
			Asteroid* a1 = new Asteroid();
			a1->tex.loadFromFile("asteroid.png");
			float angle1 = rand() % 360;
			a1->vel.x = cos((angle1 * 3.1415926f) / 180);
			a1->vel.y = sin((angle1 * 3.1415926f) / 180);
			if (isBig && !isMid) {
				a1->radius = 35;
				a1->speed = 50;
			}
			else if (!isBig && isMid) {
				a1->radius = 17.5;
				a1->speed = 75;
			}
			a1->pos.x = boomPos.x + rand() % 100;
			a1->pos.y = boomPos.y + rand() % 100 - 50;
			addGameObject(a1);
			Asteroid* a2 = new Asteroid();
			a2->tex.loadFromFile("asteroid.png");
			float angle2 = rand() % 360;
			a2->vel.x = cos((angle2 * 3.1415926f) / 180);
			a2->vel.y = sin((angle2 * 3.1415926f) / 180);
			if (isBig && !isMid) {
				a2->radius = 35;
				a2->speed = 50;
			}	
			else if (!isBig && isMid) {
				a2->radius = 17.5;
				a2->speed = 75;
			}
			a2->pos.x = boomPos.x + rand() % 100;
			a2->pos.y = boomPos.y + rand() % 100 - 50;
			addGameObject(a2);
		}
		boom = false;
		isBig = true;
		isMid = false;
		isSma = false;
	}

	//check if ship has been destroyed
	if (shipDead) {
		s->tex.loadFromFile("shipdie.png");
		s->size = Vector2f(100, 80);
		s->rot = 0;
		s->vel = Vector2f(0, 0);
		if (s->dieCount >= 750) {
			shipDead = false;
			livesLeft--;
			s->dieCount = 0;
			s->tex.loadFromFile("spaceship.png");
			s->size = Vector2f(40, 60);
			s->rot = 0;
			s->vel = Vector2f(0, 0);
			s->pos = Vector2f(600 - 20, 450 - 30);
		}
	}

	//switch scenes
	//if (livesLeft <= 0)
		//return new GameOverScreen();
	if (enemiesRemaining <= 0)
		return new GameLevel(level + 1);
	if (Keyboard::isKeyPressed(Keyboard::Escape))
		return new MainMenu();

	//fire bullet
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
	for (int i = 0; i < livesLeft; i++)
		window.draw(lives[i].DrawLives(tex_ship));
}