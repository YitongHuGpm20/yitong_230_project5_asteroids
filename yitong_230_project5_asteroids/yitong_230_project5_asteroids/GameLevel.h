#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "AppState.h"
#include "GameObject.h"
#include "Ship.h"
#include "Bullet.h"
#include "AppState.h"
#include "Asteroid.h"
#include "MainMenu.h"
#include <vector>
#include <memory>

using namespace sf;
using namespace std;
const float BUCKET_WIDTH = 120;
const float BUCKET_HEIGHT = 90;
const int COLUMNS = 10;
const int ROWS = 10;
class GameLevel : public AppState
{
private:
	int level;
	int lives;
	int enemiesRemaining = 4 + level - 1;
	Ship ship;
	Texture tex_ship;
	SoundBuffer buf_ship;
	Sound sou_ship;
	Bullet bullet[100];
	SoundBuffer buf_bullet;
	Sound sou_bullet;
	Asteroid asteroid[10];
	Texture tex_ast;
	float green = 255;
	float red = 200;
	float blue = 0;
	bool play_sou_ship = false;
	int bulletNum = 0;
	int count = 300;
	vector<GameObject*> objects;
	vector<GameObject*> grid[COLUMNS][ROWS];
	
public:
	GameLevel(int level);
	virtual AppState* update_state(float dt);
	virtual void render_frame();
	void addGameObject(GameObject* obj);
	void bucket_add(Vector2i b, GameObject* obj);
	void bucket_remove(Vector2i b, GameObject* obj);
	void detect_collisions(GameObject* obj, Vector2i b);
};

