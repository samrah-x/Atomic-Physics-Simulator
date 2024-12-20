#pragma once
#include "raylib.h"
#include <functional>

class Button
{
public:
	Button(const char* imagePath, Vector2 imagePosition, float scale);
	~Button();
	void Draw();
	bool isPressed(Vector2 mousePos, bool mousePressed);
	void setOnPressAction(std::function<void()> action);
	void press();
	bool updateCursor(Vector2 mousePos);
private:
	Texture2D texture;
	Vector2 position;
	std::function<void()> onPressAction;
	Rectangle rect;
};