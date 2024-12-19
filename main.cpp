#include "raylib.h"
#include <iostream>
#include "button.hpp"

using namespace std;
int main()
{
	InitWindow(1250, 650, "Atomic Physics Simulator");

	SetTargetFPS(60);

	Texture2D background = LoadTexture("Graphics/b4.jpeg");
	Button fissionButton{ "Graphics/fission.png", { 775, 70 }, 0.25 };
	Button fusionButton{ "Graphics/fusion.png", { 1025, 70 }, 0.25 };
	Button chainRxnButton{ "Graphics/chain.png", { 775, 265 }, 0.25 };
	Button alphaDecayButton{ "Graphics/alpha.png", { 1025, 265 }, 0.25 };
	Button betaDecayButton{ "Graphics/beta.png", { 775, 460 }, 0.25 };
	Button gammaDecayButton{ "Graphics/gamma.png", { 1025, 460 }, 0.25 };
	Button homeButton{ "Graphics/home.png", { 1025, 70 }, 0.25 };

	while (WindowShouldClose() == false)
	{
		Vector2 mousePosition = GetMousePosition();
		bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

		if (fissionButton.isPressed(mousePosition, mousePressed))
		{
			cout << "fission button pressed." << endl;
		}

		// start drawing
		BeginDrawing();

		// clear screen
		ClearBackground(BLACK);

		// scale texture to fit screen
		Vector2 position = { 0.0f, 0.0f };
		Vector2 scale = { (float)GetScreenWidth() / background.width,
						(float)GetScreenHeight() / background.height };

		// draw scaled bkgd
		DrawTextureEx(background, position, 0.0f, scale.x, WHITE);
		fissionButton.Draw();
		fusionButton.Draw();
		chainRxnButton.Draw();
		alphaDecayButton.Draw();
		betaDecayButton.Draw();
		gammaDecayButton.Draw();

		EndDrawing();
	}
	CloseWindow();
}