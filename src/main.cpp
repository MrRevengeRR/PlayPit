#include "raylib.h"

typedef enum GameScreen { LoadingScreen = 0, MainMenu, Section3D, Section2D, SectionOther} GameScreen;

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


int main(void)
{
    // Initialization
    const int screenWidth = 1200;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "PlayPit 0.0.1");
    GameScreen currentScreen = LoadingScreen;

    // Variables
    int frameCounter = 0;

    //Objects
    Camera camera;

    //Other Variables
    Image mainMenuImg = LoadImage("C:\\Users\\Luci\\Documents\\C++\\.Projects\\PlayPit\\res\\PlayPit_MainMenu.png");     // Loaded in CPU memory (RAM)
    Texture2D mainMenuTexture = LoadTextureFromImage(mainMenuImg);          // Loaded in GPU memory (VRAM)
    UnloadImage(mainMenuImg);          

    SetTargetFPS(60);               

    while (!WindowShouldClose())
    {
        // Update
        switch(currentScreen)
        {
            case LoadingScreen: {

                frameCounter++;
                if (frameCounter >= 120) {
                    frameCounter = 0;
                    currentScreen = MainMenu;
                }
                    
            }break;

            case MainMenu: {

                if (IsKeyPressed(KEY_ONE) || IsKeyPressed(KEY_KP_1)) {
                    currentScreen = Section3D;
                    init3DFirstPerson(camera);
                }
                    
                else if (IsKeyPressed(KEY_TWO) || IsKeyPressed(KEY_KP_2))
                    currentScreen = Section2D;
                else if (IsKeyPressed(KEY_THREE) || IsKeyPressed(KEY_KP_4))
                    currentScreen = SectionOther;

            }break;

            case Section3D: {
                UpdateCamera(&camera);
            }break;

            case Section2D: {

            }break;

            case SectionOther: {

            }break;
        }

        // Draw
        BeginDrawing();

            ClearBackground(RAYWHITE);

            switch(currentScreen)
            {
                case LoadingScreen: {
                    DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);
                    DrawText("Loading...", 560, 333, 25, WHITE);
                }break;

                case MainMenu: {
                    DrawTexture(mainMenuTexture, 0, 0, WHITE);
                }break;

                case Section3D: {
                    draw3DFirstPerson(camera);  
                }break;
            }

        EndDrawing();
    }

    // De-Initialization
    UnloadTexture(mainMenuTexture);

    CloseWindow();
    return 0;
}