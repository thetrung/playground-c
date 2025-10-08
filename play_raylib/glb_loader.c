#include "raylib.h"
#include "stdio.h"  // for printf(const char*, ..)
#include "string.h" // strcpy (char*, const char*)

void asset_path(const char* asset, char* return_path){
    char asset_path[2048];
    const char* exe_path = GetApplicationDirectory();
    snprintf(asset_path, sizeof(asset_path), "%s%s", exe_path, asset);
    printf("asset_path = %s\n", asset_path);
    strcpy(return_path, asset_path);
}
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    //
    // 3D model loading path
    //--------------------------------------------------------------------------------------
    // * Basically, the core of Asset-Server before asset-pack.
    //   But for now we just simply use this path-correction without caching yet :
    //
    char model_robot_path[2048];
    const char* model_robot = "robot.glb";
    asset_path(model_robot, model_robot_path);
    //
    // Start new window 
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "raylib [models] example - loading gltf");

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 6.0f, 6.0f, 6.0f };    // Camera position
    camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    // Load gltf model
    Model model = LoadModel(model_robot_path);
    Vector3 position = { 0.0f, 0.0f, 0.0f }; // Set model position

    // Load gltf model animations
    int animsCount = 0;
    unsigned int animIndex = 0;
    unsigned int animCurrentFrame = 0;
    ModelAnimation *modelAnimations = LoadModelAnimations(model_robot_path, &animsCount);

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera, CAMERA_ORBITAL);

        // Select current animation
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) 
        animIndex = (animIndex + 1)%animsCount;

        else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
        animIndex = (animIndex + animsCount - 1)%animsCount;

        // Update model animation
        ModelAnimation anim = modelAnimations[animIndex];
        animCurrentFrame = (animCurrentFrame + 1)%anim.frameCount;
        UpdateModelAnimation(model, anim, animCurrentFrame);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                DrawModel(model, position, 1.0f, WHITE);    // Draw animated model
                DrawGrid(10, 1.0f);
            EndMode3D();

            DrawText("Use the LEFT/RIGHT mouse buttons to switch animation", 10, 10, 20, GRAY);
            DrawText(TextFormat("Animation: %s", anim.name), 10, GetScreenHeight() - 20, 10, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadModel(model);         // Unload model and meshes/material

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

