#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>

using namespace std;

const int width = 20;
const int height = 20;

struct Point {
    int x, y;
};

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

class SnakeGame {
private:
    vector<Point> snake;
    Point food;
    Direction dir;
    bool gameOver;

public:
    SnakeGame() {
        gameOver = false;
        dir = STOP;
        snake.push_back({width / 2, height / 2});
        food = {rand() % width, rand() % height};
    }

    void Setup() {
        gameOver = false;
        dir = STOP;
        snake.clear();
        snake.push_back({width / 2, height / 2});
        food = {rand() % width, rand() % height};
    }

    void Draw() {
        system("cls");
        for (int i = 0; i < width + 2; i++)
            cout << "#";
        cout << endl;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0)
                    cout << "#";
                if (i == snake[0].y && j == snake[0].x)
                    cout << "O";
                else if (i == food.y && j == food.x)
                    cout << "F";
                else {
                    bool print = false;
                    for (int k = 1; k < snake.size(); k++) {
                        if (snake[k].x == j && snake[k].y == i) {
                            cout << "o";
                            print = true;
                        }
                    }
                    if (!print)
                        cout << " ";
                }
                if (j == width - 1)
                    cout << "#";
            }
            cout << endl;
        }

        for (int i = 0; i < width + 2; i++)
            cout << "#";
        cout << endl;
        cout << "Score: " << snake.size() - 1 << endl;
    }

    void Input() {
        if (_kbhit()) {
            switch (_getch()) {
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

    void Logic() {
        Point head = snake[0];
        Point newHead;

        switch (dir) {
        case LEFT:
            newHead = {head.x - 1, head.y};
            break;
        case RIGHT:
            newHead = {head.x + 1, head.y};
            break;
        case UP:
            newHead = {head.x, head.y - 1};
            break;
        case DOWN:
            newHead = {head.x, head.y + 1};
            break;
        default:
            newHead = head;
        }

        if (newHead.x >= width || newHead.x < 0 || newHead.y >= height || newHead.y < 0)
            gameOver = true;

        for (int i = 1; i < snake.size(); i++)
            if (newHead.x == snake[i].x && newHead.y == snake[i].y)
                gameOver = true;

        if (newHead.x == food.x && newHead.y == food.y) {
            snake.push_back(food);
            food = {rand() % width, rand() % height};
        } else {
            snake.erase(snake.begin());
        }

        snake.insert(snake.begin(), newHead);
    }

    void Run() {
        Setup();
        while (!gameOver) {
            Draw();
            Input();
            Logic();
            Sleep(100);
        }
    }
};

int main() {
    SnakeGame game;
    game.Run();
    return 0;
}