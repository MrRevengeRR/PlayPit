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
    bool tempMatrix[40][40] = {false};
    bool playing = false;
    bool drawing = false;
    unsigned gameOfLifeGen = 0;
    struct {
        int row = 0, col = 0;
    }drawPos;
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
                }

                else if (IsKeyPressed(KEY_B)) {
                    currentScreen = MainMenu;
                }

            }break;

            case SectionOther: {

            }break;

            case GameOfLife: {
                if (IsKeyPressed(KEY_B)) {
                    currentScreen = Section2D;
                    playing = false;
                    drawing = false;
                }
                if ((IsKeyPressed(KEY_KP_ADD) || IsKeyPressed(KEY_D)) && frameCounterLimit > 0) {
                    frameCounterLimit -= 5;
                }
                if ((IsKeyPressed(KEY_KP_SUBTRACT) || IsKeyPressed(KEY_A)) && frameCounterLimit < 60) {
                    frameCounterLimit += 5;
                }
                if (IsKeyPressed(KEY_ENTER) && !drawing) {
                    playing = !playing;
                }
                if (IsKeyPressed(KEY_G) && !drawing && !playing) {
                    initGameOfLife(matrix, rows, columns);
                    gameOfLifeGen = 0;
                }
                if (IsKeyPressed(KEY_E) && !playing) {
                    drawing = !drawing;
                    gameOfLifeGen = 0;
                }
                if (IsKeyPressed(KEY_R)) {
                    resetGameOfLife(matrix, rows, columns);
                    gameOfLifeGen = 0;
                }

                if (drawing) {
                    if (IsKeyPressed(KEY_RIGHT))
                        drawPos.row = drawPos.row < rows-1 ? drawPos.row + 1 : drawPos.row;
                    if (IsKeyPressed(KEY_LEFT))
                        drawPos.row = drawPos.row > 0 ? drawPos.row - 1 : drawPos.row;
                    if (IsKeyPressed(KEY_UP))
                        drawPos.col = drawPos.col > 0 ? drawPos.col - 1 : drawPos.col;
                    if (IsKeyPressed(KEY_DOWN))
                        drawPos.col = drawPos.col < rows-1 ? drawPos.col + 1 : drawPos.col;
                    if (IsKeyPressed(KEY_O))
                        matrix[drawPos.row][drawPos.col] = !matrix[drawPos.row][drawPos.col];
                }

                if (playing) {
                    frameCounter++;
                    if (frameCounter >= frameCounterLimit) {
                        frameCounter = 0;
                        gameOfLifeGen++;
                        updateGameOfLife(matrix, rows, columns, tempMatrix);
                    }
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
                    DrawText("Speed:", 4, 60, 25, RAYWHITE);
                    DrawText("Press B to go back", 4, 780, 20, RAYWHITE);
                    DrawText("Generate random (G)", 4, 130, 20, RAYWHITE);
                    DrawText("Draw (O)", 4, 170, 20, LIGHTGRAY);
                    DrawText(TextFormat("Generation: %d", gameOfLifeGen), 2, 254, 20, RAYWHITE);

                    drawGameOfLife(matrix, rows, columns, cellSize);

                    if (!drawing) {
                        if (!playing) {
                            DrawText("Press enter to start", 2, 200, 20, GREEN);
                            DrawText("Enter draw mode (E)", 4, 150, 20, RAYWHITE);
                            DrawText("Reset (R)", 2, 222, 20, RAYWHITE);
                        }
                        else {
                            DrawText("Press enter to stop", 2, 200, 20, RED);
                            DrawText("Generate random (G)", 4, 130, 20, LIGHTGRAY);
                            DrawText("Enter draw mode (E)", 4, 150, 20, LIGHTGRAY);
                            DrawText("Reset (R)", 2, 222, 20, GRAY);
                        }
                    }
                    else {
                        DrawText("Press enter to start", 2, 200, 20, LIGHTGRAY);
                        DrawText("Generate random (G)", 4, 130, 20, LIGHTGRAY);
                        DrawText("Exit draw mode (E)", 4, 150, 20, RAYWHITE);
                        DrawText("Draw (O)", 4, 170, 20, GREEN);
                        DrawText("Reset (R)", 2, 222, 20, RAYWHITE);
                        DrawRectangle(drawPos.row * cellSize + 223, drawPos.col * cellSize+1, cellSize-2, cellSize-2, GREEN);
                    }

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
                }
            }

        EndDrawing();
    }

    // De-Initialization
    UnloadTexture(mainMenuTexture);

    CloseWindow();
    return 0;
}