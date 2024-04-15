#ifndef MYSNAKE_GLOBALSCOPE_H
#define MYSNAKE_GLOBALSCOPE_H

//----------------------------------------------------------------------------------
// Some Defines
//----------------------------------------------------------------------------------
#define CELL_SIZE 70
#define CELL_COUNT 10
#define OFFSET (CELL_COUNT*CELL_SIZE/15.0)
#define FONT_SIZE (OFFSET - CELL_COUNT)

#include "raylib.h"
#include <deque>
#include <raymath.h>
#include <functional>
#include <fstream>

using namespace std;

//------------------------------------------------------------------------------------
// Global Variables Declaration
//------------------------------------------------------------------------------------
static Color greenBG = {173, 214, 68, 255};
static Color darkGreenBG = {166, 209, 60, 255};
static Color border = {74,117,45,255};

extern bool running;

static bool elementInDeque(const deque<Vector2> &searchField, Vector2 elementToFind, bool includeFirstElement) {
    if (includeFirstElement)
        return any_of(searchField.begin()+1, searchField.end(), [&](const Vector2 &vec) { return Vector2Equals(vec, elementToFind); });
    else
        return any_of(searchField.begin(), searchField.end(), [&](const Vector2 &vec) { return Vector2Equals(vec, elementToFind); });
}

static void DrawBG() {
    ClearBackground(border);

    int scoreInFile;
    // Read the current score from the file
    ifstream inputFile("bestScore.txt");
    inputFile >> scoreInFile;
    inputFile.close();

    // Draw best score
    char scoreBuffer[1];
    itoa(scoreInFile, scoreBuffer, 10);
    DrawText("Best score: ", GetScreenWidth() - MeasureText("Best score: ", FONT_SIZE) - CELL_SIZE, 0, FONT_SIZE, WHITE);
    DrawText(scoreBuffer, GetScreenWidth() - CELL_SIZE, 0, FONT_SIZE, WHITE);

    // Draw background palette
    for (int i = 0; i < CELL_COUNT; i++) {
        for (int j = 0; j < CELL_COUNT; j++) {
            if ((i + j) % 2)
                DrawRectangle(i * CELL_SIZE + (int)OFFSET, j * CELL_SIZE + (int)OFFSET, CELL_SIZE, CELL_SIZE, darkGreenBG);
            else
                DrawRectangle(i * CELL_SIZE + (int)OFFSET, j * CELL_SIZE + (int)OFFSET, CELL_SIZE, CELL_SIZE, greenBG);
        }
    }
}

static void writeScoreToFile(int score) {
    int scoreInFile = 1;

    // Read the current score from the file
    ifstream inputFile("bestScore.txt");

    if (inputFile.is_open()) {
        inputFile >> scoreInFile;
        inputFile.close();
    } else { // Create file if it doesn't exist
        ofstream outputFile("bestScore.txt");
        outputFile << score;
    }

    // Write the score to the file if it's higher than the score in the file
    ofstream outputFile("bestScore.txt");

    if (score > scoreInFile)
        outputFile << score;
    else
        outputFile << scoreInFile;

    outputFile.close();
}

static void initializeGame() {
    InitWindow(OFFSET * 2 + CELL_COUNT * CELL_SIZE, OFFSET * 2 + CELL_COUNT * CELL_SIZE, "Snake");
    Image windowIcon = LoadImage("Textures\\windowIcon.png");
    SetWindowIcon(windowIcon);
    UnloadImage(windowIcon);
    InitAudioDevice();
    SetTargetFPS(60);
}

#endif //MYSNAKE_GLOBALSCOPE_H