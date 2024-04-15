#include "Snake.h"

void Snake::draw() {

    // Draw score
    itoa(score, scoreBuffer, 10);
    DrawText("Score: ", OFFSET, 0, FONT_SIZE, WHITE);
    DrawText(scoreBuffer, MeasureText("Score", FONT_SIZE)+(int)FONT_SIZE*2, 0, FONT_SIZE, WHITE);

    // Draw snake body
    for (int i = 0; i < body.size(); i++) {
        auto segment = Rectangle{body[i].x * (float)CELL_SIZE+(float)OFFSET, body[i].y * (float)CELL_SIZE + (float)OFFSET, (float)CELL_SIZE, (float)CELL_SIZE};

        if (!i) {
            DrawRectangleRounded(segment, 0.6, 6, DARKBLUE);
        } else {
            DrawRectangleRoundedLines(segment, 0.6, 6, 3, DARKBLUE);
            DrawRectangleRounded(segment, 0.4, 6, BLUE);
        }
    }
}

void Snake::controls() {
    if ((IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) && (!(bool)direction.x || !running)) {
        direction = {-1, 0};
        running = true;
    }
    if ((IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) && (!(bool)direction.y || !running)) {
        direction = {0, 1};
        running = true;
    }
    if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && (!(bool)direction.y || !running)) {
        direction = {0, -1};
        running = true;
    }
    if ((IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) && (!(bool)direction.x || !running)) {
        direction = {1, 0};
        running = true;
    }
}

void Snake::updateBody() {
    body.pop_back();
    body.push_front(Vector2Add(body[0], direction));
}

void Snake::checkCollision() {

    // Check if the head of the snake collides with the game board boundaries
    if (body[0].y >= CELL_COUNT || body[0].y < 0 ||
        body[0].x >= CELL_COUNT || body[0].x < 0) {

        running = false;
        PlaySound(gameOver);
        writeScoreToFile(score);
        return; // Exit early to avoid additional collision checks
    }

    // Check if the head of the snake collides with its own body
    if (elementInDeque(body, body[0], true)) {

        running = false;
        PlaySound(gameOver);
        writeScoreToFile(score);

        return; // Exit early if there's a collision
    }
}

void Snake::unloadMembers() {
    UnloadSound(gameOver);
}