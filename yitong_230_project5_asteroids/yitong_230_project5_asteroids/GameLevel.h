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
	vector<GameObject*> objects;
	vector<GameObject*> grid[COLUMNS][ROWS];
	
public:
	vector<GameObject*> &boomGrid = grid[0][0];

	GameLevel(int level);
	virtual AppState* update_state(float dt);
	virtual void render_frame();
	void addGameObject(GameObject* obj);
	void deleteGameObject(vector<GameObject*> &v, int i);
	void bucket_add(Vector2i b, GameObject* obj);
	void bucket_remove(Vector2i b, GameObject* obj);
	void detect_collisions(GameObject* obj, Vector2i b);
};