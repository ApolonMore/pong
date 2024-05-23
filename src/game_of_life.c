#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define width 80
#define height 25

void load_file(char buff[height][width]);
void output(char buff[height][width]);
void cp_mass(char buff1[height][width], char buff2[height][width]);
void life(char buff1[height][width], char buff2[height][width], int i, int k);

int main() {
    FILE *fp;
    initscr();
    raw();
    cbreak();
    noecho();
    nodelay(stdscr, 1);
    int n = 100000;
    char field1[height][width];
    char field2[height][width];
    load_file(field1);
    cp_mass(field1, field2);
    output(field1);
    refresh();
    clear();
    usleep(n);
    while (1) {
        char c;
        cp_mass(field2, field1);
        for (int i = 0; i < height; i++) {
            for (int k = 0; k < width; k++) {
                life(field1, field2, i, k);
            }
        }
        if ((fp = freopen("/dev/tty", "r", stdin)) == NULL) {
            printf("n/a");
            break;
        }
        output(field2);
        c = getch();
        if (n > 10000) {
            if (c == '1') n -= 10000;
        }
        if (n < 300000) {
            if (c == '2') n += 10000;
        }
        printf("1 - +Speed, 2 - -Speed, q - exit");
        refresh();
        usleep(n);
        clear();
        if (c == 'q') break;
    }
    fclose(fp);
    getch();
    endwin();
    return 0;
}
void load_file(char buff[height][width]) {
    char c;
    for (int i = 0; i < height; i++) {
        for (int k = 0; k < width + 1; k++) {
            scanf("%c", &c);
            if (c != '\n') buff[i][k] = c;
        }
    }
}
void cp_mass(char buff1[height][width], char buff2[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int k = 0; k < width; k++) {
            buff2[i][k] = buff1[i][k];
        }
    }
}

void output(char buff[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int k = 0; k < width; k++) {
            printw("%c", buff[i][k]);
            if (k + 1 == width) printw("\n");
        }
    }
}

void life(char buff1[height][width], char buff2[height][width], int i, int k) {
    int n = 0;
    for (int j = -1; j <= 1; j++) {
        for (int l = -1; l <= 1; l++) {
            if (j == 0 && l == 0) continue;
            if (i + j < 0 && l + k < 0) {
                if (buff1[height - 1][width - 1] == '#') n++;
            } else if (i + j == height && l + k == width) {
                if (buff1[0][0] == '#') n++;
            } else if (i + j < 0 && l + k == width) {
                if (buff1[height - 1][0] == '#') n++;
            } else if (i + j == height && l + k < 0) {
                if (buff1[0][width - 1] == '#') n++;
            } else if (i + j == height) {
                if (buff1[0][k + l] == '#') n++;
            } else if (i + j < 0) {
                if (buff1[height - 1][k + l] == '#') n++;
            } else if (k + l == width) {
                if (buff1[i + j][0] == '#') n++;
            } else if (k + l < 0) {
                if (buff1[i + j][width - 1] == '#') n++;
            } else {
                if (buff1[i + j][k + l] == '#') n++;
            }
        }
    }
    if (buff1[i][k] == ' ') {
        if (n == 3) buff2[i][k] = '#';
    } else if (buff1[i][k] == '#') {
        if (n == 2 || n == 3)
            buff2[i][k] = '#';
        else
            buff2[i][k] = ' ';
    }
}
