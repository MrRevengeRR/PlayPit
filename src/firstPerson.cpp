#include "firstPerson.h"

void init3DFirstPerson(Camera &camera) {
    //Variables
    camera = { 0 };
    camera.position = { 0.0f, 1.0f, 0.0f };
    camera.target = { 0.0f, 0.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    //Others
    SetCameraMode(camera, CAMERA_FIRST_PERSON);
}

void draw3DFirstPerson(Camera &camera) {
    BeginMode3D(camera);
        DrawPlane({0.0f, 0.0f, 0.0f}, {30.0f, 30.0f}, LIGHTGRAY);
        DrawCube({ -16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, BLUE);   
        DrawCube({ 16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, LIME);
        DrawCube({ 0.0f, 2.5f, 16.0f }, 32.0f, 5.0f, 1.0f, GOLD);
    EndMode3D();
}