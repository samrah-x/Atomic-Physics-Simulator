#include "button.hpp"

Rectangle rect;

Button::Button(const char* imagePath, Vector2 imagePosition, float scale)
{
	Image image = LoadImage(imagePath);

	int originalWidth = image.width;
	int originalHeight = image.height;

	int newWidth = static_cast<int>(originalWidth * scale);
	int newHeight = static_cast<int>(originalHeight * scale);

	ImageResize(&image, newWidth, newHeight);
	texture = LoadTextureFromImage(image);
	UnloadImage(image);

	position = imagePosition;

	rect = { position.x, position.y, static_cast<float>(texture.width), static_cast<float>(texture.height) };
}

Button::~Button()
{
	UnloadTexture(texture);
}

void Button::Draw()
{
	/*
	// Calculate scale factors for width and height
	float scaleX = 130.0 / texture.width;
	float scaleY = 130.0 / texture.height;

	// Draw the button with the calculated scale
	DrawTextureEx(texture, position, 0.0f, scaleX, WHITE);
	*/

	DrawTextureV(texture, position, WHITE);
	if (CheckCollisionPointRec(GetMousePosition(), rect))
	{
		DrawRectangleLinesEx(rect, 2, RED); // Highlight border
		// Optionally: Draw a semi-transparent overlay
		DrawRectangle(rect.x, rect.y, rect.width, rect.height, Fade(RED, 0.3f));
	}
	else 
	{
		DrawRectangleLinesEx(rect, 2, BLACK); // Default border
	}
}

bool Button::isPressed(Vector2 mousePos, bool mousePressed)
{
	if (CheckCollisionPointRec(mousePos, rect) && mousePressed)
		return true;
	return false;
}
