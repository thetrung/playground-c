#include "raylib.h"
int main(void) {
  InitWindow(1600, 1200, "raylib-grid on C");
  // Define the camera to look into our 3d world
  Camera camera = {0};
  camera.position = (Vector3){6.0f, 6.0f, 6.0f}; // Camera position
  camera.target = (Vector3){0.0f, 2.0f, 0.0f};   // Camera looking at point
  camera.up =
      (Vector3){0.0f, 1.0f, 0.0f}; // Camera up vector (rotation towards target)
  camera.fovy = 45.0f;             // Camera field-of-view Y
  camera.projection = CAMERA_PERSPECTIVE; // Camera projection type
  SetTargetFPS(60);            // Set our game to run at 60 frames-per-second
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    UpdateCamera(&camera, CAMERA_ORBITAL);
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(camera);
    DrawGrid(40, .5f);
    EndMode3D();
    EndDrawing();
  }
  CloseWindow(); // Close window and OpenGL context
  return 0;
}
