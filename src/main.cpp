#include<iostream>

#include<vector>

#include<raylib.h>
#include<raymath.h>

#include"tile.h"

#define LEVEL_PATH "res/maps/test.json"

int main(){


    InitWindow(1600,900,"LEVEL EDITOR");

    std::vector<Tile> tiles = loadLevelFromFile(LEVEL_PATH);

    bool is_debugging=true;

    Camera2D camera = { 0 };
    camera.zoom = 1.0f;

    SetTargetFPS(120);

    while(!WindowShouldClose()){
        if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
        {
            Vector2 delta = GetMouseDelta();
            delta = Vector2Scale(delta, -1.0f/camera.zoom);

            camera.target = Vector2Add(camera.target, delta);
        }

        // Zoom based on mouse wheel
        float wheel = GetMouseWheelMove();
        if (wheel != 0)
        {
            // Get the world point that is under the mouse
            Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

            // Set the offset to where the mouse is
            camera.offset = GetMousePosition();

            // Set the target to match, so that the camera maps the world space point 
            // under the cursor to the screen space point under the cursor at any zoom
            camera.target = mouseWorldPos;

            // Zoom increment
            const float zoomIncrement = 0.125f;

            camera.zoom += (wheel*zoomIncrement);
            if (camera.zoom < zoomIncrement) camera.zoom = zoomIncrement;
        }

        BeginDrawing();

        ClearBackground(LIGHTGRAY);

        BeginMode2D(camera);

        for(auto &tile : tiles)
            tile.Draw(is_debugging);

        EndMode2D();

        EndDrawing();
    }

    return 0;
}
