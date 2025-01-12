#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include "raylib.h"

// Init
void initGameOfLife(bool matrix[40][40], int rows, int columns);
// Draw
void drawGameOfLife(bool matrix[40][40], int rows, int columns, int cellSize);
// Update
void updateGameOfLife(bool matrix[40][40], int rows, int columns, bool tempMatrix[40][40]);
// Reset
void resetGameOfLife(bool matrix[40][40], int rows, int columns);
//Check if cell is alive/dead
bool isAlive(bool matrix[40][40], int i, int j, int rows, int columns);

#endif