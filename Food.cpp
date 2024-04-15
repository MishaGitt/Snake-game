#include "Food.h"

// Draw the food on the screen
void Food::draw() const {
    DrawTexture(appleTexture, (int)position.x * CELL_SIZE + (int)OFFSET, (int)position.y * CELL_SIZE + (int)OFFSET, WHITE);
}

// Generate a random position for the food
Vector2 Food::generateRandomPosition(const deque<Vector2>& snakeBody) {
    do {
        int x = GetRandomValue(0, CELL_COUNT - 1);
        int y = GetRandomValue(0, CELL_COUNT - 1);
        position = {(float)x, (float)y};
    } while (elementInDeque(snakeBody, position, false));

    return position;
}

void Food::unloadMembers() {
    UnloadImage(appleImage);
    UnloadTexture(appleTexture);
}