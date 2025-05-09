#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

Vector3 g_up = { 0.f, 1.f, 0.f };

int
main(int argc, char** argv) {
    printf("Hello! [ Duck Renderer ] \n");

    // Init ------------------
    InitWindow(1280, 720, "Title");
    SetTargetFPS(120);

    // Model duck_model = LoadModel("../assets/YellowDuck1glb.glb");
    Model duck_model = LoadModel("../assets/duck-photographer.glb");

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.f, 10.f, 10.f };
    camera.target = (Vector3){ 0.f, 0.f, 0.f };
    camera.up = g_up;
    camera.fovy = 45.f;
    camera.projection = CAMERA_PERSPECTIVE;

    while (!WindowShouldClose()) {
        BeginDrawing();

        // Background
        float stime = (sin(GetTime()) + 1.f) / 2.f;
        ClearBackground((Color){ (uint8_t)(stime * 155), 40, 40, (uint8_t)(stime * 255) });
        DrawFPS(10, 10);
        DrawText("Welcome to DuckRenderer", 50, 50, 22, BLACK);

        // 3D World
        BeginMode3D(camera);
        Matrix transform = duck_model.transform;
        transform = MatrixRotateY(stime);
        Matrix scale = MatrixScale(0.2, 0.2, 0.2);
        transform = MatrixMultiply(transform, scale);
        DrawMesh(duck_model.meshes[0], duck_model.materials[0], transform);

        DrawGrid(10, 1.f);
        EndMode3D();

        EndDrawing();
    }

    // De-Init ------------------
    UnloadModel(duck_model);
    CloseWindow();

    return 0;
}
