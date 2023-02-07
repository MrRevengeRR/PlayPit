#include "raylib.h"
#include "firstPerson.h"

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

            case GameOfLife: {

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

                }break;

                case SectionOther: {

                }break;

                case GameOfLife: {

                }
            }

        EndDrawing();
    }

    // De-Initialization
    UnloadTexture(mainMenuTexture);

    CloseWindow();
    return 0;
}