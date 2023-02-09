#include "raylib.h"
#include "firstPerson.h"
#include "gameOfLife.h"

typedef enum GameScreen { LoadingScreen = 0, MainMenu, Section3D, Section2D, SectionOther, GameOfLife} GameScreen;

int main(void)
{
    // Initialization
    const int screenWidth = 1200;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "PlayPit 0.0.1");
    GameScreen currentScreen = LoadingScreen;

    // Variables
    int frameCounter = 0;
    int frameCounterLimit = 0;

    // 3D First Person
    Camera camera;

    // Game of life
    bool matrix[40][40] = {false};
    const int rows = 40;
    const int columns = 40;
    const int cellSize = screenHeight/columns;

    // Other Variables
    // Loading in CPU memory (RAM)
    Image mainMenuImg = LoadImage("C:\\Users\\Luci\\Documents\\C++\\.Projects\\PlayPit\\res\\PlayPit_MainMenu.png");
    Image section2DImg = LoadImage("C:\\Users\\Luci\\Documents\\C++\\.Projects\\PlayPit\\res\\PlayPit_2DSection.png"); 
    // Loading in GPU memory (VRAM)
    Texture2D mainMenuTexture = LoadTextureFromImage(mainMenuImg);
    Texture2D section2DTexture = LoadTextureFromImage(section2DImg);
    // Unloading images from CPU
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
                    
                else if (IsKeyPressed(KEY_TWO) || IsKeyPressed(KEY_KP_2)) {
                    currentScreen = Section2D;
                }
                    
                else if (IsKeyPressed(KEY_THREE) || IsKeyPressed(KEY_KP_4)) {
                    currentScreen = SectionOther;
                }
                    
            }break;

            case Section3D: {
                UpdateCamera(&camera);
            }break;

            case Section2D: {
                if (IsKeyPressed(KEY_ONE) || IsKeyPressed(KEY_KP_1)) {
                    currentScreen = GameOfLife;
                    frameCounter = 0;
                    frameCounterLimit = 15;
                    initGameOfLife(matrix, rows, columns);
                }

                else if (IsKeyPressed(KEY_B)) {
                    currentScreen = MainMenu;
                }

            }break;

            case SectionOther: {

            }break;

            case GameOfLife: {
                frameCounter++;
                if (IsKeyPressed(KEY_B)) {
                    currentScreen = Section2D;
                }
                if ((IsKeyPressed(KEY_KP_ADD) || IsKeyPressed(KEY_D)) && frameCounterLimit > 0) {
                    frameCounterLimit -= 5;
                }
                if ((IsKeyPressed(KEY_KP_SUBTRACT) || IsKeyPressed(KEY_A)) && frameCounterLimit < 60) {
                    frameCounterLimit += 5;
                }

                if (frameCounter >= frameCounterLimit) {
                    frameCounter = 0;
                    updateGameOfLife(matrix, rows, columns);
                }
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

                case Section2D: {
                    DrawTexture(section2DTexture, 0, 0, WHITE);
                }break;

                case SectionOther: {

                }break;

                case GameOfLife: {
                    ClearBackground(BLACK);
                    DrawText("Settings", 8, 4, 50, RAYWHITE);
                    DrawText("Speed:", 5, 60, 25, RAYWHITE);
                    DrawText("Press b to go back", 5, 780, 20, RAYWHITE);
                    if (frameCounterLimit <= 60)
                        DrawCircle(10, 100, 6, RAYWHITE);
                    if (frameCounterLimit <= 55)
                        DrawCircle(24, 100, 6, RAYWHITE);
                    if (frameCounterLimit <= 50)
                        DrawCircle(38, 100, 6, RAYWHITE);
                    if (frameCounterLimit <= 45)
                        DrawCircle(52, 100, 6, RAYWHITE);
                    if (frameCounterLimit <= 40)
                        DrawCircle(66, 100, 6, RAYWHITE);
                    if (frameCounterLimit <= 35)
                        DrawCircle(80, 100, 6, RAYWHITE);
                    if (frameCounterLimit <= 30)
                        DrawCircle(94, 100, 6, RAYWHITE);
                    if (frameCounterLimit <= 25)
                        DrawCircle(108, 100, 6, RAYWHITE);
                    if (frameCounterLimit <= 20)
                        DrawCircle(122, 100, 6, RAYWHITE);
                    if (frameCounterLimit <= 15)
                        DrawCircle(136, 100, 6, RAYWHITE);
                    if (frameCounterLimit <= 10)
                        DrawCircle(150, 100, 6, RAYWHITE);
                    if (frameCounterLimit <= 5)
                        DrawCircle(164, 100, 6, RAYWHITE);
                    if (frameCounterLimit <= 0)
                        DrawCircle(178, 100, 6, RAYWHITE);
                    drawGameOfLife(matrix, rows, columns, cellSize);
                }
            }

        EndDrawing();
    }

    // De-Initialization
    UnloadTexture(mainMenuTexture);

    CloseWindow();
    return 0;
}