#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <cmath>
#include <cstdlib>

using namespace std;

bool gameover;
const int width = 20;
const int height = 20;
int tailx[100];
int taily[100];
int tailn = 0;
int speed = 200;
int x, y, fruitx, fruity, score, i, j;

enum Movement { stop = 0, left, right, up, down };
Movement direction; 

void setting() {
    gameover = false;
    direction = stop; 
    x = width / 2;
    y = height / 2;
    fruitx = rand() % width;
    fruity = rand() % height;
    score = 0;
}

void image() {
    system("cls");
    for (i = 0; i < width + 2; i++) {
        cout << "+";
    }
    cout << endl;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (j == 0 || j == width - 1) {
                cout << "+";
            }
            if (i == y && j == x) {
                cout << "O"; 
            }
            else if (i == fruity && j == fruitx) {
                cout << "8"; 
            }
            else {
                bool print = false;
                for (int k = 0; k < tailn; k++) {
                    if (tailx[k] == j && taily[k] == i) {
                        cout << "x"; 
                        print = true;
                    }
                }
                if (!print) {
                    cout << " ";
                }
            }
            if (j == width - 1) {
                cout << "+";
            }
        }
        cout << endl;
    }

    for (i = 0; i < width + 2; i++) {
        cout << "+";
    }
    cout << endl;

    cout << "Game score: " << score << endl;
}

void controls() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'w':
            direction = up;
            break;
        case 's':
            direction = down;
            break;
        case 'a':
            direction = left;
            break;
        case 'd':
            direction = right;
            break;
        }
    }
}

void logic() {
    int prevx = tailx[0];
    int prevy = taily[0];
    int prevXx, prevYy;
    tailx[0] = x;
    taily[0] = y;

    for (i = 1; i < tailn; i++) {
        prevXx = tailx[i];
        prevYy = taily[i];
        tailx[i] = prevx;
        taily[i] = prevy;
        prevx = prevXx;
        prevy = prevYy;
    }

    switch (direction) { 
    case up:
        y--;
        break;
    case down:
        y++;
        break;
    case left:
        x--;
        break;
    case right:
        x++;
        break;
    default:
        break;
    }

    if (x >= width) {
        x = 0;
    }
    else if (x < 0) {
        x = width - 1;
    }

    if (y >= height) {
        y = 0;
    }
    else if (y < 0) {
        y = height - 1;
    }

    for (i = 0; i < tailn; i++) {
        if (tailx[i] == x && taily[i] == y) {
            gameover = true;
        }
    }

    if (x == fruitx && y == fruity) {
        score += 5;
        fruitx = rand() % width;
        fruity = rand() % height;
        tailn++;
    }
}

int main() {
    setting();
    while (!gameover) {
        image();
        controls();
        logic();
        Sleep(speed);
    }
    return 0;
}