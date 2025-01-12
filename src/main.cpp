#include <stdlib.h>

#include "raylib.h"
#include "firstPerson.h"
#include "gameOfLife.h"
#include "Particle.h"
#include "blackjack.h"

typedef enum GameScreen {LoadingScreen = 0, MainMenu, Section3D, Section2D, GameOfLife, ParticleSimulation, Impius, Blackjack} GameScreen;

void toggleFullscreen(int screenWidth, int screenHeight);

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

    // Particle simulation
    const int particleCount = 169000;
    Particle *particles = (Particle*)malloc(particleCount * sizeof(Particle));

    // Impius
    
    //Blackjack
    bool bjInGame = false;
    bool playerStand = false;
    bool playerWon = false;
    bool dealerWon = false;
    //int playerAces = 0;
    //int dealerAces = 0;
    int pCards[10] = {0};
    int playerSum = 0, dealerSum = 0;

    Texture cards[54] = {
        LoadTexture("null"),
        LoadTexture("resources/playing_cards/clubs_2.png"), LoadTexture("resources/playing_cards/diamonds_2.png"), LoadTexture("resources/playing_cards/hearts_2.png"), LoadTexture("resources/playing_cards/spades_2.png"),
        LoadTexture("resources/playing_cards/clubs_3.png"), LoadTexture("resources/playing_cards/diamonds_3.png"), LoadTexture("resources/playing_cards/hearts_3.png"), LoadTexture("resources/playing_cards/spades_3.png"),
        LoadTexture("resources/playing_cards/clubs_4.png"), LoadTexture("resources/playing_cards/diamonds_4.png"), LoadTexture("resources/playing_cards/hearts_4.png"), LoadTexture("resources/playing_cards/spades_4.png"),
        LoadTexture("resources/playing_cards/clubs_5.png"), LoadTexture("resources/playing_cards/diamonds_5.png"), LoadTexture("resources/playing_cards/hearts_5.png"), LoadTexture("resources/playing_cards/spades_5.png"),
        LoadTexture("resources/playing_cards/clubs_6.png"), LoadTexture("resources/playing_cards/diamonds_6.png"), LoadTexture("resources/playing_cards/hearts_6.png"), LoadTexture("resources/playing_cards/spades_6.png"),
        LoadTexture("resources/playing_cards/clubs_7.png"), LoadTexture("resources/playing_cards/diamonds_7.png"), LoadTexture("resources/playing_cards/hearts_7.png"), LoadTexture("resources/playing_cards/spades_7.png"),
        LoadTexture("resources/playing_cards/clubs_8.png"), LoadTexture("resources/playing_cards/diamonds_8.png"), LoadTexture("resources/playing_cards/hearts_8.png"), LoadTexture("resources/playing_cards/spades_8.png"),
        LoadTexture("resources/playing_cards/clubs_9.png"), LoadTexture("resources/playing_cards/diamonds_9.png"), LoadTexture("resources/playing_cards/hearts_9.png"), LoadTexture("resources/playing_cards/spades_9.png"),
        LoadTexture("resources/playing_cards/clubs_10.png"), LoadTexture("resources/playing_cards/diamonds_10.png"), LoadTexture("resources/playing_cards/hearts_10.png"), LoadTexture("resources/playing_cards/spades_10.png"),
        LoadTexture("resources/playing_cards/clubs_jack.png"), LoadTexture("resources/playing_cards/diamonds_jack.png"), LoadTexture("resources/playing_cards/hearts_jack.png"), LoadTexture("resources/playing_cards/spades_jack.png"),
        LoadTexture("resources/playing_cards/clubs_queen.png"), LoadTexture("resources/playing_cards/diamonds_queen.png"), LoadTexture("resources/playing_cards/hearts_queen.png"), LoadTexture("resources/playing_cards/spades_queen.png"),
        LoadTexture("resources/playing_cards/clubs_king.png"), LoadTexture("resources/playing_cards/diamonds_king.png"), LoadTexture("resources/playing_cards/hearts_king.png"), LoadTexture("resources/playing_cards/spades_king.png"),
        LoadTexture("resources/playing_cards/clubs_ace.png"), LoadTexture("resources/playing_cards/diamonds_ace.png"), LoadTexture("resources/playing_cards/hearts_ace.png"), LoadTexture("resources/playing_cards/spades_ace.png"),
        LoadTexture("resources/playing_cards/hidden.png")
    };

    // Images
    // Loading in CPU memory (RAM)
    Image mainMenuImg = LoadImage("resources/PlayPit_MainMenu.png");
    Image section2DImg = LoadImage("resources/PlayPit_2DSection.png"); 
    Image bjBackgroundImg = LoadImage("resources/blackjackBackground.png");
    // Loading in GPU memory (VRAM)
    Texture2D mainMenuTexture = LoadTextureFromImage(mainMenuImg);
    Texture2D section2DTexture = LoadTextureFromImage(section2DImg);
    Texture2D bjBackgroundTexture = LoadTextureFromImage(bjBackgroundImg);
    // Unloading images from CPU
    UnloadImage(mainMenuImg);
    UnloadImage(section2DImg);
    UnloadImage(bjBackgroundImg);

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
                    currentScreen = Impius;
                    toggleFullscreen(screenWidth, screenHeight);
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
                
                else if (IsKeyPressed(KEY_TWO) || IsKeyPressed(KEY_KP_2)) {
                    currentScreen = ParticleSimulation;
                    for (long int i = 0; i < particleCount; i++) {
                        particles[i] = Particle(screenWidth, screenHeight);
                    }
                }

                else if (IsKeyPressed(KEY_THREE) || IsKeyPressed(KEY_KP_3)) {
                    currentScreen = Blackjack;
                }

                else if (IsKeyPressed(KEY_B)) {
                    currentScreen = MainMenu;
                }

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

            case ParticleSimulation: {
                if (IsKeyPressed(KEY_B)) {
                    for (long int i = 0; i < particleCount; i++) {
                        particles[i].reset();
                    }
                    currentScreen = Section2D;
                }
                Vector2 mousePos = {(float)GetMouseX(), (float)GetMouseY()};
                for (long int i = 0; i < particleCount; i++) {   
                    particles[i].attract(mousePos, 1);
                    particles[i].doFriction(0.99);
                    particles[i].move(screenWidth, screenHeight);
                }
            }break;

            case Impius: {
                
            }break;

            case Blackjack: {
                if (!bjInGame) {
                    if (IsKeyPressed(KEY_ENTER)) {
                        playerWon = false;
                        dealerWon = false;
                        playerSum = 0;
                        dealerSum = 0;
                        //playerAces = 0;
                        //dealerAces = 0;
                        initBlackjack(pCards);
                        for (int i = 0; i < 10; i++) {
                            if (i < 5) {
                                if (pCards[i] >= 1 && pCards[i] <= 4)
                                    playerSum += 2;
                                else if (pCards[i] >= 5 && pCards[i] <= 8)
                                    playerSum += 3;
                                else if (pCards[i] >= 9 && pCards[i] <= 12)
                                    playerSum += 4;
                                else if (pCards[i] >= 13 && pCards[i] <= 16)
                                    playerSum += 5;
                                else if (pCards[i] >= 17 && pCards[i] <= 20)
                                    playerSum += 6;
                                else if (pCards[i] >= 21 && pCards[i] <= 24)
                                    playerSum += 7;
                                else if (pCards[i] >= 25 && pCards[i] <= 28)
                                    playerSum += 8;
                                else if (pCards[i] >= 29 && pCards[i] <= 32)
                                    playerSum += 9;
                                else if (pCards[i] >= 33 && pCards[i] <= 48)
                                    playerSum += 10;
                                else if (pCards[i] >= 49 && pCards[i] <= 52) {
                                    if (playerSum + 11 > 21)
                                        playerSum += 1;
                                    else 
                                        playerSum += 11;
                                }
                                    //playerAces++;
                            }
                            else {
                                if (pCards[i] >= 1 && pCards[i] <= 4)
                                    dealerSum += 2;
                                else if (pCards[i] >= 5 && pCards[i] <= 8)
                                    dealerSum += 3;
                                else if (pCards[i] >= 9 && pCards[i] <= 12)
                                    dealerSum += 4;
                                else if (pCards[i] >= 13 && pCards[i] <= 16)
                                    dealerSum += 5;
                                else if (pCards[i] >= 17 && pCards[i] <= 20)
                                    dealerSum += 6;
                                else if (pCards[i] >= 21 && pCards[i] <= 24)
                                    dealerSum += 7;
                                else if (pCards[i] >= 25 && pCards[i] <= 28)
                                    dealerSum += 8;
                                else if (pCards[i] >= 29 && pCards[i] <= 32)
                                    dealerSum += 9;
                                else if (pCards[i] >= 33 && pCards[i] <= 48)
                                    dealerSum += 10;
                                else if (pCards[i] >= 49 && pCards[i] <= 52) {
                                    if (dealerSum + 11 > 21)
                                        dealerSum += 1;
                                    else 
                                        dealerSum += 11;
                                }
                                    //dealerAces++;
                            }
                        }
                        if (playerSum == 21 || dealerSum > 21)
                            playerWon = true;
                        if (dealerSum == 21 || playerSum > 21)
                            dealerWon = true;
                        //if ((playerSum == 20 && playerAces == 1) || (playerSum == 21 && playerAces == 0))
                            //playerWon = true;
                        //if (playerSum > 21 || (playerSum == 21 && playerAces >= 1))
                            //dealerWon = true;
                        bjInGame = true;
                    }
                    if (IsKeyPressed(KEY_B)) {
                        currentScreen = Section2D;
                    }
                }
                else if (!playerWon && !dealerWon) {
                    if (IsKeyPressed(KEY_B)) {
                        for (int i = 0; i < 10; i++)
                            pCards[i] = 0;
                        bjInGame = false;
                        playerWon = false;
                        dealerWon = false;
                        playerStand = false;
                        playerSum = 0;
                        dealerSum = 0;
                        //playerAces = 0;
                        //dealerAces = 0;
                        currentScreen = Section2D;
                    }
                    if (IsKeyPressed(KEY_H) && !playerStand && !playerWon && !dealerWon) {
                        hitBlackjack(pCards);
                        playerSum = 0;
                        for (int i = 0; i < 5; i++) {
                            if (pCards[i] >= 1 && pCards[i] <= 4)
                                playerSum += 2;
                            else if (pCards[i] >= 5 && pCards[i] <= 8)
                                playerSum += 3;
                            else if (pCards[i] >= 9 && pCards[i] <= 12)
                                playerSum += 4;
                            else if (pCards[i] >= 13 && pCards[i] <= 16)
                                playerSum += 5;
                            else if (pCards[i] >= 17 && pCards[i] <= 20)
                                playerSum += 6;
                            else if (pCards[i] >= 21 && pCards[i] <= 24)
                                playerSum += 7;
                            else if (pCards[i] >= 25 && pCards[i] <= 28)
                                playerSum += 8;
                            else if (pCards[i] >= 29 && pCards[i] <= 32)
                                playerSum += 9;
                            else if (pCards[i] >= 33 && pCards[i] <= 48)
                                playerSum += 10;
                            else if (pCards[i] >= 49 && pCards[i] <= 52) {
                                if (playerSum + 11 > 21)
                                    playerSum += 1;
                                else 
                                    playerSum += 11;
                            }
                                //playerAces++;
                        }
                        if (playerSum == 21 || dealerSum > 21)
                            playerWon = true;
                        if (dealerSum == 21 || playerSum > 21)
                            dealerWon = true;
                        if (pCards[4] != 0)
                            playerStand = true;
                        //if ((playerSum == 20 && playerAces == 1) || (playerSum == 21 && playerAces == 0))
                           // playerWon = true;
                        //if (playerSum > 21 || (playerSum == 21 && playerAces >= 1))
                            //dealerWon = true;
                        //if (pCards[4] != 0)
                            //playerStand = true;
                        
                        //std::cout << playerSum << " " << dealerSum << " " << playerWon << " " << dealerWon << "\n"; //debug
                        //std::cout << pCards[5] << " " << pCards[6] << " " << pCards[7] << " " << pCards[8] << " " << pCards[9] << " ";
                    }
                    if (IsKeyPressed(KEY_S) && !playerStand && !playerWon && !dealerWon) {
                        playerStand = true;
                        frameCounterLimit = 60;
                        frameCounter = 0;
                        while (dealerSum < 17 || pCards[9] != 0) {
                            dealerHitBlackjack(pCards);
                            dealerSum = 0;
                            while (frameCounter < frameCounterLimit) {
                                frameCounter++;
                            }
                            frameCounter = 0;
                            for (int i = 5; i < 10; i++) {
                                if (pCards[i] >= 1 && pCards[i] <= 4)
                                    dealerSum += 2;
                                else if (pCards[i] >= 5 && pCards[i] <= 8)
                                    dealerSum += 3;
                                else if (pCards[i] >= 9 && pCards[i] <= 12)
                                    dealerSum += 4;
                                else if (pCards[i] >= 13 && pCards[i] <= 16)
                                    dealerSum += 5;
                                else if (pCards[i] >= 17 && pCards[i] <= 20)
                                    dealerSum += 6;
                                else if (pCards[i] >= 21 && pCards[i] <= 24)
                                    dealerSum += 7;
                                else if (pCards[i] >= 25 && pCards[i] <= 28)
                                    dealerSum += 8;
                                else if (pCards[i] >= 29 && pCards[i] <= 32)
                                    dealerSum += 9;
                                else if (pCards[i] >= 33 && pCards[i] <= 48)
                                    dealerSum += 10;
                                else if (pCards[i] >= 49 && pCards[i] <= 52) {
                                    if (dealerSum + 11 > 21)
                                        dealerSum += 1;
                                    else 
                                        dealerSum += 11;
                                }

                                    //dealerAces++;
                            }
                        }  
                        if (playerSum == 21 || (playerSum > dealerSum && playerSum <= 21) || dealerSum > 21)
                            playerWon = true;
                        if (dealerSum == 21 || (dealerSum > playerSum && dealerSum <= 21) || playerSum > 21)
                            dealerWon = true;
                        //if ((playerSum == 20 && playerAces == 1) || (playerSum > dealerSum) || (playerSum == 21 && playerAces == 0) || dealerSum > 21)
                        //    playerWon = true;
                        //if (dealerSum == 21 || playerSum > 21 || (playerSum == 21 && playerAces >= 1) || (dealerSum > playerSum) || (dealerSum == 20 && dealerAces == 1))
                        //    dealerWon = true;
                        //std::cout << playerSum << " " << dealerSum << " " << playerWon << " " << dealerWon << "\n"; //debug
                        //std::cout << pCards[5] << " " << pCards[6] << " " << pCards[7] << " " << pCards[8] << " " << pCards[9] << " ";
                    }       
                }
                else {
                    if (IsKeyPressed(KEY_ENTER)) {
                        playerWon = false;
                        dealerWon = false;
                        playerStand = false;
                        playerSum = 0;
                        dealerSum = 0;
                        for (int i = 0; i < 10; i++)
                            pCards[i] = 0;
                        //playerAces = 0;
                        //dealerAces = 0;
                        initBlackjack(pCards);
                        for (int i = 0; i < 10; i++) {
                            if (i < 5) {
                                if (pCards[i] >= 1 && pCards[i] <= 4)
                                    playerSum += 2;
                                else if (pCards[i] >= 5 && pCards[i] <= 8)
                                    playerSum += 3;
                                else if (pCards[i] >= 9 && pCards[i] <= 12)
                                    playerSum += 4;
                                else if (pCards[i] >= 13 && pCards[i] <= 16)
                                    playerSum += 5;
                                else if (pCards[i] >= 17 && pCards[i] <= 20)
                                    playerSum += 6;
                                else if (pCards[i] >= 21 && pCards[i] <= 24)
                                    playerSum += 7;
                                else if (pCards[i] >= 25 && pCards[i] <= 28)
                                    playerSum += 8;
                                else if (pCards[i] >= 29 && pCards[i] <= 32)
                                    playerSum += 9;
                                else if (pCards[i] >= 33 && pCards[i] <= 48)
                                    playerSum += 10;
                                else if (pCards[i] >= 49 && pCards[i] <= 52) {
                                    if (playerSum + 11 > 21)
                                        playerSum += 1;
                                    else 
                                        playerSum += 11;
                                }
                                    //playerAces++;
                            }
                            else {
                                if (pCards[i] >= 1 && pCards[i] <= 4)
                                    dealerSum += 2;
                                else if (pCards[i] >= 5 && pCards[i] <= 8)
                                    dealerSum += 3;
                                else if (pCards[i] >= 9 && pCards[i] <= 12)
                                    dealerSum += 4;
                                else if (pCards[i] >= 13 && pCards[i] <= 16)
                                    dealerSum += 5;
                                else if (pCards[i] >= 17 && pCards[i] <= 20)
                                    dealerSum += 6;
                                else if (pCards[i] >= 21 && pCards[i] <= 24)
                                    dealerSum += 7;
                                else if (pCards[i] >= 25 && pCards[i] <= 28)
                                    dealerSum += 8;
                                else if (pCards[i] >= 29 && pCards[i] <= 32)
                                    dealerSum += 9;
                                else if (pCards[i] >= 33 && pCards[i] <= 48)
                                    dealerSum += 10;
                                else if (pCards[i] >= 49 && pCards[i] <= 52) {
                                    if (dealerSum + 11 > 21)
                                        dealerSum += 1;
                                    else 
                                        dealerSum += 11;
                                }
                                    //dealerAces++;
                            }
                        }
                        if (playerSum == 21 || dealerSum > 21)
                            playerWon = true;
                        if (dealerSum == 21 || playerSum > 21)
                            dealerWon = true;
                        //if ((playerSum == 20 && playerAces == 1) || (playerSum == 21 && playerAces == 0))
                            //playerWon = true;
                        //if (playerSum > 21 || (playerSum == 21 && playerAces >= 1))
                            //dealerWon = true;
                        bjInGame = true;
                    }
                    if (IsKeyPressed(KEY_B)) {
                        for (int i = 0; i < 10; i++)
                            pCards[i] = 0;
                        bjInGame = false;
                        playerWon = false;
                        dealerWon = false;
                        playerStand = false;
                        playerSum = 0;
                        dealerSum = 0;
                        //playerAces = 0;
                        //dealerAces = 0;
                        currentScreen = Section2D;
                    }
                }
            }
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

                case GameOfLife: {
                    ClearBackground(BLACK);
                    DrawText("Settings", 8, 4, 50, RAYWHITE);
                    DrawText("Speed (A/D):", 4, 60, 25, RAYWHITE);
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

                case ParticleSimulation: {
                    for (int i = 0; i < particleCount; i++) {
                        particles[i].drawPixel();
                    }
                }break;

                case Impius: {
                        DrawText("Nothing here yet", 500, 420, 100, BLACK);
                }break;

                case Blackjack: {
                    DrawTexture(bjBackgroundTexture, 0, 0, WHITE);

                    if (!bjInGame)
                        DrawText("Press enter to play", 365, 385, 50, YELLOW);
                    else {
                        if (!playerWon && !dealerWon)
                            DrawText("Press h to hit, s to stand", 315, 385, 50, WHITE);
                        else 
                            DrawText("Press enter to start new game", 250, 385, 50, WHITE);
                        DrawTexture(cards[pCards[5]], 125, 25, WHITE);
                        if (!playerStand) {
                            if (pCards[6])
                                DrawTexture(cards[53], 322, 25, WHITE);
                            if (pCards[7])
                                DrawTexture(cards[53], 519, 25, WHITE);
                            if (pCards[8])
                                DrawTexture(cards[53], 716, 25, WHITE);
                            if (pCards[9])
                                DrawTexture(cards[53], 913, 25, WHITE);
                        }
                        else {
                            DrawTexture(cards[pCards[6]], 322, 25, WHITE);
                            DrawTexture(cards[pCards[7]], 519, 25, WHITE);
                            DrawTexture(cards[pCards[8]], 716, 25, WHITE);
                            DrawTexture(cards[pCards[9]], 913, 25, WHITE);
                        }

                        DrawTexture(cards[pCards[0]], 125, 542, WHITE);
                        DrawTexture(cards[pCards[1]], 322, 542, WHITE);
                        DrawTexture(cards[pCards[2]], 519, 542, WHITE);
                        DrawTexture(cards[pCards[3]], 716, 542, WHITE);
                        DrawTexture(cards[pCards[4]], 913, 542, WHITE);

                        if (dealerWon) {
                            if (playerWon)
                                DrawText("Tie", 300, 300, 80, YELLOW);
                            else 
                                DrawText("Dealer Won", 300, 300, 80, RED);
                        }
                        else if (playerWon)
                            DrawText("You Won", 350, 300, 80, RED);
                        /*
                        Dealer card positions

                        DrawTexture(cards[0], 125, 25, WHITE);
                        DrawTexture(cards[0], 322, 25, WHITE);
                        DrawTexture(cards[0], 519, 25, WHITE);
                        DrawTexture(cards[0], 716, 25, WHITE);
                        DrawTexture(cards[0], 913, 25, WHITE);

                        Player card positions

                        DrawTexture(cards[0], 125, 542, WHITE);
                        DrawTexture(cards[0], 322, 542, WHITE);
                        DrawTexture(cards[0], 519, 542, WHITE);
                        DrawTexture(cards[0], 716, 542, WHITE);
                        DrawTexture(cards[0], 913, 542, WHITE);
                        */
                    }
                }
            }

        EndDrawing();
    }

    // De-Initialization
    UnloadTexture(mainMenuTexture);
    UnloadTexture(section2DTexture);
    UnloadTexture(bjBackgroundTexture);

    CloseWindow();
    return 0;
}

void toggleFullscreen(int screenWidth, int screenHeight) {
    if (!IsWindowFullscreen()) {
        int monitor = GetCurrentMonitor();
        SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
        ToggleFullscreen();
    }
    else {
        ToggleFullscreen();
        SetWindowSize(screenWidth, screenHeight);
    }
}