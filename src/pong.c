#include <stdio.h>

void fieldDrawing(int width, int height, int ballX, int ballY, int padLeft, int padRight);
void countsDrawing(int countLeft, int countRight, int width);
void MovingRackets(int *padLeft, int *padRight, int height);
void ballMoving(int width, int height, int *ballX, int *ballY, int padLeft, int padRight, int *offsetX,
                int *offsetY);
int countChanging(int *ballX, int *ballY, int *countLeft, int *countRight, int padLeft, int padRight,
                  int *offsetX, int width);

int main() {
    const int width = 80;
    const int height = 25;

    int ballX = 30;
    int ballY = 13;

    int padLeft = 12;
    int padRight = 12;

    int countLeft = 0;
    int countRight = 0;

    int offsetX = 1;
    int offsetY = 1;

    countsDrawing(countLeft, countRight, width);
    fieldDrawing(width, height, ballX, ballY, padLeft, padRight);

    while (countLeft < 21 && countRight < 21) {
        MovingRackets(&padLeft, &padRight, height);
        ballMoving(width, height, &ballX, &ballY, padLeft, padRight, &offsetX, &offsetY);
        countChanging(&ballX, &ballY, &countLeft, &countRight, padLeft, padRight, &offsetX, width);
        countsDrawing(countLeft, countRight, width);
        fieldDrawing(width, height, ballX, ballY, padLeft, padRight);
    }
    return 0;
}
void countsDrawing(int countLeft, int countRight, int width) {
    for (int i = 1; i <= width; i++) {
        switch (i) {
            case 20:
                printf("%d", countLeft);
                break;
            case 60:
                printf("%d", countRight);
                break;
            case 80:
                printf(" \n");
                break;
            default:
                printf(" ");
        }
    }
}

void fieldDrawing(int width, int height, int ballX, int ballY, int padLeft, int padRight) {
    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            if (ballX == j && ballY == i) {
                j == width ? printf("O\n") : printf("O");
            } else if (j == 1 && (i == padLeft || i == padLeft + 1 || i == padLeft + 2)) {
                j == width ? printf("|\n") : printf("|");
            } else if (j == width && (i == padRight || i == padRight + 1 || i == padRight + 2)) {
                printf("|\n");
            } else {
                if (i == 1) {
                    j == width ? printf("'\n") : printf("'");
                } else if (i == height) {
                    j == width ? printf(".\n") : printf(".");
                } else {
                    if (j == width) {
                        printf(" \n");
                    } else {
                        printf(" ");
                    }
                }
            }
        }
    }
}

void MovingRackets(int *padLeft, int *padRight, int height) {
    char key;
    while (scanf("%c", &key)) {
        if (key == ' ') return;
        switch (key) {
            case 'a':
                if ((*padLeft - 1) != 0) *padLeft -= 1;
                return;
            case 'z':
                if ((*padLeft + 2) != height) *padLeft += 1;
                return;
            case 'k':
                if ((*padRight - 1) != 0) *padRight -= 1;
                return;
            case 'm':
                if ((*padRight + 2) != height) *padRight += 1;
                return;
        }
    }
}

void ballMoving(int width, int height, int *ballX, int *ballY, int padLeft, int padRight, int *offsetX,
                int *offsetY) {
    *ballX += *offsetX;
    *ballY += *offsetY;

    if ((*ballX == 2 && *ballY == padLeft) || (*ballX == width - 1 && *ballY == padRight)) {
        *offsetX = -*offsetX;
        if (*offsetY == 1) *offsetY = -1;
    }

    if ((*ballX == 2 && *ballY == padLeft + 1) || (*ballX == width - 1 && *ballY == padRight + 1)) {
        *offsetX = -*offsetX;
    }

    if ((*ballX == 2 && *ballY == padLeft + 2) || (*ballX == width - 1 && *ballY == padRight + 2)) {
        *offsetX = -*offsetX;
        if (*offsetY == -1) *offsetY = 1;
    }

    if (*ballY == 1 || *ballY == height) {
        *offsetY = -*offsetY;
    }
}

int countChanging(int *ballX, int *ballY, int *countLeft, int *countRight, int padLeft, int padRight,
                  int *offsetX, int width) {
    if (*ballX <= 1) {
        *countRight += 1;
        *ballX = 20;
        *ballY = padLeft + 1;
        *offsetX = -*offsetX;
    }
    if (*ballX >= width) {
        *countLeft += 1;
        *ballX = width - 20;
        *ballY = padRight + 1;
        *offsetX = -*offsetX;
    }
    if (*countLeft >= 21) {
        printf("\n>>>>Congratulations! Player ONE has won with score %d to %d!<<<<\n", *countLeft,
               *countRight);
        return 1;
    } else if (*countRight >= 21) {
        printf("\n>>>>Congratulations! Player TWO has won with score %d to %d!<<<<\n", *countLeft,
               *countRight);
        return 1;
    }
    return 0;
}
