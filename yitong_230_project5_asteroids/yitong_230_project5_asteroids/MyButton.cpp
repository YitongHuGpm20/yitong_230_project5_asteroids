#include "MyButton.h"

extern RenderWindow window;
Font font;

MyButton::MyButton(Vector2f pos, string str) {
	
	font.loadFromFile("arial.ttf");
	name.setFont(font);
	name.setCharacterSize(36);
	name.setFillColor(Color::White);
	name.setStyle(Text::Bold);
	name.setPosition(pos);
	name.setString(str);
}

bool MyButton::isHover(Vector2f mousePos, FloatRect textPos) {
	return textPos.left <= mousePos.x && textPos.left + textPos.width >= mousePos.x && textPos.top <= mousePos.y && textPos.top + textPos.height >= mousePos.y;
}

bool MyButton::isClicked() {
	Vector2i mouseI = Mouse::getPosition(window);
	Vector2f mouseF = Vector2f((float)mouseI.x, (float)mouseI.y);
	if (isHover(mouseF, name.getGlobalBounds())) {
		name.setFillColor(Color::Green);
		if(Mouse::isButtonPressed(Mouse::Left))
			return true;
	}
	else
		name.setFillColor(Color::White);
	return false;
}

void MyButton::DrawButton() {
	window.draw(name);
}