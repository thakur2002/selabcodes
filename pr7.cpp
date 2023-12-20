// Write a program to find the Weighted Methods per Class given in  Chidamber & Kemerer Metric Suite.
#include <iostream>
#include <conio.h> // For _getch() function
#include <Windows.h>
using namespace std;

// Define constants for the game board size
const int width = 100;
const int height = 20;

// Define the directions for the snake
enum Direction
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Game
{
protected:
    bool gameOver;

public:
    Game() : gameOver(false) {}

    virtual void Draw() = 0;
    virtual void Input() = 0;
    virtual void Logic() = 0;

    bool IsGameOver() const
    {
        return gameOver;
    }
};

class SnakeGame : public Game
{
private:
    int x, y;                   // Head coordinates
    int fruitX, fruitY;         // Fruit coordinates
    int tailLength;             // Length of the tail
    int tailX[100], tailY[100]; // Arrays to store the coordinates of the tail
    Direction dir;              // Current direction

public:
    SnakeGame() : Game(), x(width / 2), y(height / 2), tailLength(0), dir(STOP)
    {
        fruitX = rand() % width;
        fruitY = rand() % height;
    }

    // Function to draw the game board
    void Draw() override
    {
        system("cls"); // Clear the console

        // Draw the upper border
        for (int i = 0; i < width + 2; i++)
            std::cout << "#";
        std::cout << endl;

        // Draw the game board
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (j == 0)
                    std::cout << "#"; // Draw the left border

                // Draw the snake head
                if (i == y && j == x)
                    std::cout << "O";
                // Draw the fruit
                else if (i == fruitY && j == fruitX)
                    std::cout << "F";
                else
                {
                    // Draw the snake tail
                    bool printTail = false;
                    for (int k = 0; k < tailLength; k++)
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            std::cout << "o";
                            printTail = true;
                        }
                    }
                    if (!printTail)
                        std::cout << " ";
                }

                if (j == width - 1)
                    std::cout << "#"; // Draw the right border
            }
            std::cout << endl;
        }

        // Draw the lower border
        for (int i = 0; i < width + 2; i++)
            std::cout << "#";
        std::cout << endl;

        // Display score
        std::cout << "Score:" << tailLength << endl;
    }

    // Function to take input from the user
    void Input() override
    {
        if (_kbhit())
        {
            switch (_getch())
            {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
            }
        }
    }

    // Function to update the game state
    void Logic() override
    {
        // Move the tail
        int prevX = tailX[0];
        int prevY = tailY[0];
        int prev2X, prev2Y;
        tailX[0] = x;
        tailY[0] = y;
        for (int i = 1; i < tailLength; i++)
        {
            prev2X = tailX[i];
            prev2Y = tailY[i];
            tailX[i] = prevX;
            tailY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }

        // Move the head based on the current direction
        switch (dir)
        {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        }

        // Check for collisions with the borders
        if (x < 0 || x >= width || y < 0 || y >= height)
            gameOver = true;

        // Check for collisions with the tail
        for (int i = 0; i < tailLength; i++)
        {
            if (tailX[i] == x && tailY[i] == y)
                gameOver = true;
        }

        // Check if the head reached the fruit
        if (x == fruitX && y == fruitY)
        {
            // Increase score and place a new fruit
            tailLength++;
            fruitX = rand() % width;
            fruitY = rand() % height;
        }
    }

    // Calculate Weighted Methods per Class
    int CalculateWMC() const
    {
        // Assume complexity is based on the number of lines in each method
        int wmc = 0;
        wmc += 1; // Draw method
        wmc += 1; // Input method
        wmc += 1; // Logic method

        return wmc;
    }
};

int main()
{
    SnakeGame snakeGame;
    Game &game = snakeGame;

    while (!game.IsGameOver())
    {
        game.Draw();
        game.Input();
        game.Logic();
        // Sleep or use delay to control the speed of the game
        Sleep(100);
    }

    std::cout << "Game Over!" << endl;

    // Calculate and display Weighted Methods per Class
    int wmc = snakeGame.CalculateWMC();

    std::cout << "Weighted Methods per Class (WMC): " << wmc << endl;

    return 0;
}

// OUTPUT

// Game Over!
// Weighted Methods per Class (WMC): 3
