#include "GameOverScreen.h"
#include "GameLevel.h"

using namespace sf;

extern RenderWindow window;
Text titleg;
extern Font font;

GameOverScreen::GameOverScreen() :newGame(Vector2f(410, 400), "(^_^) New Game (^_^)"), quit(Vector2f(460, 500), "(^_^) Quit (^_^)") {
	titleg.setFont(font);
	titleg.setString("You lost but try again!");
	titleg.setCharacterSize(64);
	titleg.setFillColor(Color::Cyan);
	titleg.setPosition(Vector2f(300, 100));
	titleg.setStyle(Text::Italic);
}

AppState* GameOverScreen::update_state(float dt)
{
	if (quit.isClicked())
		window.close();
	if (newGame.isClicked())
		return new GameLevel(1);
	return nullptr;
}

void GameOverScreen::render_frame()
{
	window.clear();
	window.draw(titleg);
	newGame.DrawButton();
	quit.DrawButton();
}
