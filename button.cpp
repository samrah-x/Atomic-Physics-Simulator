#include "button.hpp"

Button::Button(const char* imagePath, Vector2 imagePosition)
{
	texture = LoadTexture(imagePath);
	position = imagePosition;
}

Button::~Button()
{
	UnloadTexture(texture);
}

void Button::Draw()
{
	// Calculate scale factors for width and height
	float scaleX = 130.0 / texture.width;
	float scaleY = 130.0 / texture.height;

	// Draw the button with the calculated scale
	DrawTextureEx(texture, position, 0.0f, scaleX, WHITE);
}
