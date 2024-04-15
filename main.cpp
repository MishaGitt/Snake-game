#include "globalScope.h"
#include "Snake.h"
#include "Food.h"

bool running = false;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main() {
    //---------------------------------------------------------
    // Initialization
    //---------------------------------------------------------
    SetTraceLogLevel(LOG_ERROR);
    initializeGame();
    Sound eatSound = LoadSound("SFX\\eatSound.mp3");
    Music backgroundMusic = LoadMusicStream("SFX\\backgroundMusic.mp3");
    SetMusicVolume(backgroundMusic, 0.2);
    PlayMusicStream(backgroundMusic);

    Snake snake = Snake();
    Food food = Food(snake.body);

    //---------------------------------------------------------
    // Main game loop
    //---------------------------------------------------------
    for (int frameCounter = 0; !WindowShouldClose(); frameCounter++) {

        BeginDrawing();
        UpdateMusicStream(backgroundMusic);
        DrawBG();

        food.draw();
        snake.draw();
        snake.controls();

        // Update the snake's body movement and check for collision
        if (!(frameCounter % 10) && running) {
            snake.updateBody();

            // Snake eats food
            if (Vector2Equals(snake.body[0], food.position)) {
                PlaySound(eatSound);
                snake.body.push_back(Vector2Subtract(snake.body[0], snake.direction));
                food = Food(snake.body);
                snake.score++;
            }
        }
        snake.checkCollision();

        // If the game is not running (game over), display a message and reset
        if (!running) {
            snake.score = 1;
            snake.body = {Vector2{int(CELL_COUNT/2), int(CELL_COUNT/2)}};
            food = Food(snake.body);

            DrawBG();
            DrawText("Use W-A-S-D or arrows to move", (GetScreenWidth()-MeasureText("Use W-A-S-D or arrows to move", FONT_SIZE))/2,
                     (GetScreenHeight()-MeasureText("Use W-A-S-D or arrows to move", FONT_SIZE))/2,
                     FONT_SIZE, GRAY);
        }
        EndDrawing();
    }

    //--------------------------------------------------------------------------------------
    // De-Initialization
    //--------------------------------------------------------------------------------------
    food.unloadMembers();
    snake.unloadMembers();
    UnloadSound(eatSound);
    UnloadMusicStream(backgroundMusic);
    CloseWindow();

    return 0;
}
