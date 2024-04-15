#ifndef MYSNAKE_FOOD_H
#define MYSNAKE_FOOD_H

#include "globalScope.h"

class Food {
public:

    // Member variables
    Vector2 position{};
    Image appleImage = LoadImage("Textures\\apple.png");
    Texture2D appleTexture{};

    // Constuctor
    explicit Food(const deque<Vector2>& snakeBody) {
        ImageResize(&appleImage, CELL_SIZE, CELL_SIZE);
        appleTexture = LoadTextureFromImage(appleImage);
        position = generateRandomPosition(snakeBody);
    }

    // Destructor
    ~Food() = default;

    // Methods
    void draw() const;
    Vector2 generateRandomPosition(const deque<Vector2>& snakeBody);
    void unloadMembers();
};

#endif //MYSNAKE_FOOD_H
