#include "raylib.h"
#include "button.hpp"

int main()
{
	InitWindow(1250, 650, "Atomic Physics Simulator");

	SetTargetFPS(60);

	Texture2D background = LoadTexture("Graphics/b4.jpeg");
	Button fissionButton{ "Graphics/fission.png", { 775, 70 } };
	Button fusionButton{ "Graphics/fusion.png", { 1025, 70 } };
	Button chainRxnButton{ "Graphics/chain.png", { 775, 265 } };
	Button alphaDecayButton{ "Graphics/alpha.png", { 1025, 265 } };
	Button betaDecayButton{ "Graphics/beta.png", { 775, 460 } };
	Button gammaDecayButton{ "Graphics/gamma.png", { 1025, 460 }};
	Button homeButton{ "Graphics/home.png", { 1025, 70 } };

	while (WindowShouldClose() == false)
	{
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