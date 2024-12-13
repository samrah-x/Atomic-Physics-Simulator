#include "raylib.h"

int main()
{
	InitWindow(800, 600, "Atomic Physics Simulator");

	SetTargetFPS(60);

	while (WindowShouldClose() == false)
	{
		BeginDrawing();
		ClearBackground(BLACK);
		EndDrawing();
	}
	CloseWindow();
}