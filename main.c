#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WIDTH 40
#define HEIGHT 20

char map[HEIGHT][WIDTH];
int tux_x, tux_y;
int beastie_x, beastie_y;
int botnet_x, botnet_y;
int rescued = 0;
int invincible = 0;

void init_map() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (y == 0 || y == HEIGHT - 1 || x == 0 || x == WIDTH - 1) {
                if ((x + y) % 2 == 0) {
                    map[y][x] = '#'; // white
                } else {
                    map[y][x] = '~'; // Teal with ~ as a placeholder
                }
            } else {
                map[y][x] = ' ';
            }
        }
    }

    tux_x = 1;
    tux_y = 1;
    beastie_x = WIDTH - 2;
    beastie_y = HEIGHT - 2;
    botnet_x = WIDTH / 2;
    botnet_y = HEIGHT / 2;

    map[tux_y][tux_x] = 'T';
    map[beastie_y][beastie_x] = 'B';
    map[botnet_y][botnet_x] = 'X';
}

void draw_map() {
    system("clear");
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (map[y][x] == '#') {
                printf("\x1b[37m#"); // white
            } else if (map[y][x] == '~') {
                printf("\x1b[36m~"); // teal
            } else if (map[y][x] == 'T') {
                printf("\x1b[32mT"); // green
            } else if (map[y][x] == 'B') {
                printf("\x1b[33mB"); // yellow
            } else if (map[y][x] == 'X') {
                printf("\x1b[31mX"); // red
            } else {
                printf("\x1b[0m "); // Resets the color
            }
        }
        printf("\x1b[0m\n"); // Reset the colors an new line
    }
}

void move_tux(char direction) {
    int new_x = tux_x;
    int new_y = tux_y;

    switch (direction) {
        case 'w': new_y--; break;
        case 's': new_y++; break;
        case 'a': new_x--; break;
        case 'd': new_x++; break;
        default: return;
    }

    if (map[new_y][new_x] != '#' && map[new_y][new_x] != '~') {
        map[tux_y][tux_x] = ' ';
        tux_x = new_x;
        tux_y = new_y;
        map[tux_y][tux_x] = 'T';
    }
}

void move_botnet() {
    if (invincible) return;

    int dx = (tux_x > botnet_x) ? 1 : ((tux_x < botnet_x) ? -1 : 0);
    int dy = (tux_y > botnet_y) ? 1 : ((tux_y < botnet_y) ? -1 : 0);
    int new_x = botnet_x + dx;
    int new_y = botnet_y + dy;

    if (map[new_y][new_x] != '#' && map[new_y][new_x] != '~' && map[new_y][new_x] != 'B') {
        map[botnet_y][botnet_x] = ' ';
        botnet_x = new_x;
        botnet_y = new_y;
        map[botnet_y][botnet_x] = 'X';
    }
}

int main() {
    srand(time(NULL));
    init_map();

    while (1) {
        draw_map();

        if (tux_x == beastie_x && tux_y == beastie_y) {
            rescued = 1;
            printf("\x1b[33mTux rescued Beastie! Freedom!\x1b[0m\n");
            break;
        }

        if (tux_x == botnet_x && tux_y == botnet_y && !invincible) {
            printf("\x1b[31mTux got infected by the Botnet! Game Over!\x1b[0m\n");
            break;
        }

        printf("Enter move (w/a/s/d) ps: check  the source for some secret input options :): ");
        char input[50];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "Linux Torvalds") == 0 || strcmp(input, "685108800") == 0 || strcmp(input, "Fuck Nvidia") == 0) {
            invincible = 1;
            printf("\x1b[32mInvincibility activated!\x1b[0m\n");
        } else if (strlen(input) == 1 && (input[0] == 'w' || input[0] == 'a' || input[0] == 's' || input[0] == 'd')){
            move_tux(input[0]);
        }
        else{
            printf("\x1b[31mInvalid input\x1b[0m\n");
        }

        move_botnet();
    }

    return 0;
}
