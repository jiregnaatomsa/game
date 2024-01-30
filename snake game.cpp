#include <iostream>
#include <conio.h>
#include <time.h>

using namespace std;

const int WIDTH = 20;
const int HEIGHT = 20;

enum Direction { UP, DOWN, LEFT, RIGHT };

struct SnakeSegment {
  int x;
  int y;
};

struct Game {
  Direction direction;
  SnakeSegment snake[100]; // Maximum snake length
  int snakeLength;
  int fruitX;
  int fruitY;

  void initialize() {
    direction = RIGHT;
    snakeLength = 1;
    snake[0].x = WIDTH / 2;
    snake[0].y = HEIGHT / 2;
    spawnFruit();
  }

  void update() {
    // Update snake head position based on current direction
    switch (direction) {
      case UP:
        snake[0].y--;
        break;
      case DOWN:
        snake[0].y++;
        break;
      case LEFT:
        snake[0].x--;
        break;
      case RIGHT:
        snake[0].x++;
        break;
    }

    // Check for wall collision
    if (snake[0].x < 0 || snake[0].x >= WIDTH || snake[0].y < 0 || snake[0].y >= HEIGHT) {
      cout << "Game Over!" << endl;
      exit(0);
    }

    // Check for fruit collision
    if (snake[0].x == fruitX && snake[0].y == fruitY) {
      snakeLength++;
      spawnFruit();
    }

    // Move snake body segments
    for (int i = snakeLength - 1; i > 0; i--) {
      snake[i].x = snake[i - 1].x;
      snake[i].y = snake[i - 1].y;
    }
  }

  void draw() {
    system("cls"); // Clear console screen

    // Draw borders
    for (int i = 0; i < WIDTH; i++) {
      cout << '#';
    }
    cout << endl;
    for (int i = 1; i < HEIGHT - 1; i++) {
      cout << '#';
      for (int j = 1; j < WIDTH - 1; j++) {
        bool isSnake = false;
        for (int k = 0; k < snakeLength; k++) {
          if (snake[k].x == j && snake[k].y == i) {
            isSnake = true;
            break;
          }
        }
        if (isSnake) {
          cout << 'o';
        } else {
          cout << ' ';
        }
      }
      cout << '#';
      cout << endl;
    }
    for (int i = 0; i < WIDTH; i++) {
      cout << '#';
    }
    cout << endl;

    // Draw fruit
    cout << "Fruit: @" << fruitX << "," << fruitY << endl;
  }

  void spawnFruit() {
    fruitX = rand() % (WIDTH - 2) + 1;
    fruitY = rand() % (HEIGHT - 2) + 1;

    // Ensure fruit doesn't spawn on the snake
    for (int i = 0; i < snakeLength; i++) {
      if (snake[i].x == fruitX && snake[i].y == fruitY) {
        spawnFruit();
        break;
      }
    }
  }
};

int main() {
  srand(time(0)); // Seed random number generator

  Game game;
  game.initialize();

  while (true) {
    if (_kbhit()) {
      char ch = _getch();
      switch (ch) {
        case 'w':
          if (game.direction != DOWN) game.direction = UP;
          break;
        case 's':
          if (game.direction != UP) game.direction = DOWN;
          break;
        case 'a':
          if (game.direction != RIGHT) game.direction = LEFT;
          break;
        case 'd':
          if (game.direction != LEFT) game.direction = RIGHT;
          break;
        case 'q':
          exit(0);
          break;
      ```
