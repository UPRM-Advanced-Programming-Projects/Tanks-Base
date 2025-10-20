/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"
#include "resource_dir.h"
#include "Program.hpp"

int main () {
	// Tell the window to use vsync and work on high DPI displays
	// SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

    // Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");
	SetTargetFPS(60);
	//Can't load sound without this method
    InitAudioDevice();
	
    // Create the window and OpenGL context & tell the window to use vsync and work on high DPI displays
	raylib::Window window(1280, 800, "Tanks!", FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	ImageManager::LoadImages();
	SoundManager::LoadSounds();

	// Create the window and OpenGL context
	// InitWindow(1280, 800, "Hello Project Master!!");

    // Create program (if we were loading images & fonts, 
	//then you need to make sure that you load() them after window creation)
	Program program;


	if (!IsWindowReady()) {
		TraceLog(LOG_ERROR, "Window failed to initialize!");
		return 1;
	}
	// game loop
	while (!WindowShouldClose()) {		// run the loop untill the user presses ESCAPE or presses the Close button on the window

		// drawing
		BeginDrawing();
		ClearBackground(DARKGRAY);

		Vector2 mousePos = GetMousePosition();
		program.Update();
		program.Draw();
		program.KeyPressed(GetKeyPressed());
		program.KeyReleased();
		program.MousePressed(mousePos.x, mousePos.y, MOUSE_BUTTON_LEFT);
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	//End the audio device
	CloseAudioDevice();
	
	// destroy the window and cleanup the OpenGL context
	ImageManager::UnloadImages();
	SoundManager::UnloadSounds();
	window.Close();
	return 0;
}
