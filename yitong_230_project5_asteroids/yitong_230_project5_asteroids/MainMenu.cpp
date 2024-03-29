#include "MainMenu.h"
#include "GameLevel.h"

using namespace sf;

extern RenderWindow window;
Text title;
extern Font font;

MainMenu::MainMenu():newGame(Vector2f(410, 400), "(^_^) New Game (^_^)"), quit(Vector2f(460, 500), "(^_^) Quit (^_^)") {
	title.setFont(font);
	title.setString("Yitong's Spaceship War Game");
	title.setCharacterSize(64);
	title.setFillColor(Color::Cyan);
	title.setPosition(Vector2f(180, 100));
	title.setStyle(Text::Italic);
}

AppState* MainMenu::update_state(float dt)
{
	if (quit.isClicked())
		window.close();
	if (newGame.isClicked())
		return new GameLevel(1);
	return nullptr;
}

void MainMenu::render_frame()
{
	window.clear();
	window.draw(title);
	newGame.DrawButton();
	quit.DrawButton();
}