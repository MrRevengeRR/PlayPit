#include "gameOfLife.h"
#include <cstdlib>
#include <time.h>

void initGameOfLife(bool matrix[40][40], int rows, int columns) {
    // Init random seed
    srand(time(NULL));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrix[i][j] = rand() % 8 == 0 ? true : false;
        }
    }
}

void updateGameOfLife(bool matrix[40][40], int rows, int columns, bool tempMatrix[40][40]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (isAlive(matrix, i, j, rows, columns)) {
                tempMatrix[i][j] = true;
            }
            else {
                tempMatrix[i][j] = false;
            } 
        }
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (isAlive(matrix, i, j, rows, columns)) {
                matrix[i][j] = tempMatrix[i][j];
            }
            else {
                matrix[i][j] = tempMatrix[i][j];
            } 
        }
    }
}

void drawGameOfLife(bool matrix[40][40], int rows, int columns, int cellSize) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            DrawRectangleLines(i * cellSize + 222, j * cellSize, cellSize, cellSize, LIGHTGRAY);
            if (matrix[i][j] == true) {
                DrawRectangle(i * cellSize + 223, j * cellSize+1, cellSize-2, cellSize-2, YELLOW);
            }
            else {
                DrawRectangle(i * cellSize + 223, j * cellSize+1, cellSize-2, cellSize-2, BLACK);
            } 
        }
    }
}

void resetGameOfLife(bool matrix[40][40], int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrix[i][j] = false;
        }
    }
}

bool isAlive(bool matrix[40][40], int i, int j, int rows, int columns) {
    int liveCells = 0;
    
    if (i == 0) {
        if (j == 0) {
            if (matrix[i+1][j] == true) {
                liveCells++;
            }
            if (matrix[i][j+1] == true) {
                liveCells++;
            }
            if (matrix[i+1][j+1] == true) {
                liveCells++;
            }
            
            if (matrix[i][j] == true)
                return liveCells > 1 && liveCells < 4 ? true : false;
            else
                return liveCells == 3 ? true : false;
        }

        else if (j == columns-1) {
            if (matrix[i+1][j] == true) {
                liveCells++;
            }
            if (matrix[i][j-1] == true) {
                liveCells++;
            }
            if (matrix[i+1][j-1] == true) {
                liveCells++;
            }

            if (matrix[i][j] == true)
                return liveCells > 1 && liveCells < 4 ? true : false;
            else
                return liveCells == 3 ? true : false;
        }

        else {
            if (matrix[i][j-1] == true) {
                liveCells++;
            }
            if (matrix[i+1][j-1] == true) {
                liveCells++;
            }
            if (matrix[i+1][j] == true) {
                liveCells++;
            }
            if (matrix[i+1][j+1] == true) {
                liveCells++;
            }
            if (matrix[i][j+1] == true) {
                liveCells++;
            }

            if (matrix[i][j] == true)
                return liveCells > 1 && liveCells < 4 ? true : false;
            else
                return liveCells == 3 ? true : false;
        }
    }

    else if (i == rows-1) {
        if (j == 0) {
            if (matrix[i-1][j] == true) {
                liveCells++;
            }
            if (matrix[i][j+1] == true) {
                liveCells++;
            }
            if (matrix[i-1][j+1] == true) {
                liveCells++;
            }

            if (matrix[i][j] == true)
                return liveCells > 1 && liveCells < 4 ? true : false;
            else
                return liveCells == 3 ? true : false;
        }

        else if (j == columns-1) {
            if (matrix[i-1][j] == true) {
                liveCells++;
            }
            if (matrix[i][j-1] == true) {
                liveCells++;
            }
            if (matrix[i-1][j-1] == true) {
                liveCells++;
            }

            if (matrix[i][j] == true)
                return liveCells > 1 && liveCells < 4 ? true : false;
            else
                return liveCells == 3 ? true : false;
        }

        else {
            if (matrix[i][j-1] == true) {
                liveCells++;
            }
            if (matrix[i-1][j-1] == true) {
                liveCells++;
            }
            if (matrix[i-1][j] == true) {
                liveCells++;
            }
            if (matrix[i-1][j+1] == true) {
                liveCells++;
            }
            if (matrix[i][j+1] == true) {
                liveCells++;
            }

            if (matrix[i][j] == true)
                return liveCells > 1 && liveCells < 4 ? true : false;
            else
                return liveCells == 3 ? true : false;
        }
    }
    else {
        if (j == 0) {
            if (matrix[i-1][j] == true) {
                liveCells++;
            }
            if (matrix[i-1][j+1] == true) {
                liveCells++;
            }
            if (matrix[i][j+1] == true) {
                liveCells++;
            }
            if (matrix[i+1][j] == true) {
                liveCells++;
            }
            if (matrix[i+1][j+1] == true) {
                liveCells++;
            }

            if (matrix[i][j] == true)
                return liveCells > 1 && liveCells < 4 ? true : false;
            else
                return liveCells == 3 ? true : false;
        }

        else if (j == columns-1) {
            if (matrix[i-1][j] == true) {
                liveCells++;
            }
            if (matrix[i-1][j-1] == true) {
                liveCells++;
            }
            if (matrix[i][j-1] == true) {
                liveCells++;
            }
            if (matrix[i+1][j] == true) {
                liveCells++;
            }
            if (matrix[i+1][j-1] == true) {
                liveCells++;
            }

            if (matrix[i][j] == true)
                return liveCells > 1 && liveCells < 4 ? true : false;
            else
                return liveCells == 3 ? true : false;
        }

        else {
            if (matrix[i-1][j-1] == true) {
                liveCells++;
            }
            if (matrix[i-1][j] == true) {
                liveCells++;
            }
            if (matrix[i-1][j+1] == true) {
                liveCells++;
            }
            if (matrix[i][j-1] == true) {
                liveCells++;
            }
            if (matrix[i][j+1] == true) {
                liveCells++;
            }
            if (matrix[i+1][j-1] == true) {
                liveCells++;
            }
            if (matrix[i+1][j] == true) {
                liveCells++;
            }
            if (matrix[i+1][j+1] == true) {
                liveCells++;
            }

            if (matrix[i][j] == true)
                return liveCells > 1 && liveCells < 4 ? true : false;
            else
                return liveCells == 3 ? true : false;
        }
    }
}