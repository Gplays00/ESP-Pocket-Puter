#pragma once
#include "../global.hpp"

#define SN_W        128
#define SN_H        56
#define SN_CELL     4
#define SN_COLS     (SN_W / SN_CELL)
#define SN_ROWS     (SN_H / SN_CELL)
#define SN_MAXLEN   256
#define SN_SPEED    130

struct SnakePoint { int8_t x; int8_t y; };

static SnakePoint sn_body[SN_MAXLEN];
static int16_t    sn_len;
static uint8_t    sn_dir;
static SnakePoint sn_food;
static uint16_t   sn_score;

static const int8_t SN_DX[] = { 1, 0, -1, 0 };
static const int8_t SN_DY[] = { 0, 1,  0,-1 };

static void SnakePlaceFood() {
    bool ok = false;
    while (!ok) {
        sn_food.x = random(0, SN_COLS);
        sn_food.y = random(0, SN_ROWS);
        ok = true;
        for (int i = 0; i < sn_len; i++)
            if (sn_body[i].x == sn_food.x && sn_body[i].y == sn_food.y) { ok = false; break; }
    }
}

static void SnakeReset() {
    sn_len     = 4;
    sn_dir     = 0;
    sn_score   = 0;
    for (int i = 0; i < sn_len; i++) {
        sn_body[i].x = SN_COLS / 2 - i;
        sn_body[i].y = SN_ROWS / 2;
    }
    SnakePlaceFood();
}

void SnakeGame() {
    SnakeReset();
    bool waiting  = true;
    bool paused   = false;
    bool dead     = false;
    bool exit_sel = false;
    bool last_left   = false;
    bool last_right  = false;
    bool last_center = false;

    while (true) {
        bool left   = ReadButton(BUTTON_LEFT);
        bool right  = ReadButton(BUTTON_RIGHT);
        bool center = ReadButton(BUTTON_CENTER);

        bool pressed_left   = left   && !last_left;
        bool pressed_right  = right  && !last_right;
        bool pressed_center = center && !last_center;

        last_left   = left;
        last_right  = right;
        last_center = center;

        display.clearDisplay();

        if (waiting) {
            display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.setCursor(34, 10);
            display.print("Snake Game");
            display.setCursor(4, 24);
            display.print("Left  = turn left");
            display.setCursor(4, 34);
            display.print("Right = turn right");
            display.setCursor(4, 44);
            display.print("OK    = pause");
            display.setCursor(14, 54);
            display.print("OK to start");
            if (pressed_center) waiting = false;
            display.display();
            delay(40);
            continue;
        }

        if (dead) {
            if (pressed_right) exit_sel = !exit_sel;
            display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.setCursor(40, 8);
            display.print("Game Over");
            display.setCursor(34, 20);
            display.print("Score: ");
            display.print(sn_score);
            display.setCursor(36, 38);
            display.print(exit_sel ? "  Play" : "> Play");
            display.setCursor(36, 50);
            display.print(exit_sel ? "> Exit" : "  Exit");
            if (pressed_center) {
                if (exit_sel) return;
                SnakeReset();
                dead      = false;
                exit_sel  = false;
                waiting   = true;
            }
            display.display();
            delay(40);
            continue;
        }

        if (paused) {
            display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.setCursor(44, 28);
            display.print("PAUSED");
            display.setCursor(18, 42);
            display.print("OK to continue");
            if (pressed_center) paused = false;
            display.display();
            delay(40);
            continue;
        }

        if (pressed_center) { paused = true; display.display(); delay(40); continue; }

        if (pressed_left)  sn_dir = (sn_dir + 3) % 4;
        if (pressed_right) sn_dir = (sn_dir + 1) % 4;

        SnakePoint head = {
            (int8_t)(sn_body[0].x + SN_DX[sn_dir]),
            (int8_t)(sn_body[0].y + SN_DY[sn_dir])
        };

        if (head.x < 0 || head.x >= SN_COLS || head.y < 0 || head.y >= SN_ROWS) {
            dead = true; display.display(); delay(40); continue;
        }
        for (int i = 0; i < sn_len - 1; i++) {
            if (sn_body[i].x == head.x && sn_body[i].y == head.y) {
                dead = true; break;
            }
        }
        if (dead) { display.display(); delay(40); continue; }

        bool ate = (head.x == sn_food.x && head.y == sn_food.y);
        int  newlen = ate ? sn_len + 1 : sn_len;
        for (int i = min(newlen - 1, SN_MAXLEN - 1); i > 0; i--) sn_body[i] = sn_body[i - 1];
        sn_body[0] = head;
        if (ate) {
            if (sn_len < SN_MAXLEN) sn_len++;
            sn_score++;
            SnakePlaceFood();
        }

        display.fillRect(sn_food.x * SN_CELL, sn_food.y * SN_CELL + 8, SN_CELL - 1, SN_CELL - 1, SSD1306_WHITE);

        for (int i = 0; i < sn_len; i++) {
            if (i == 0) {
                display.fillRect(sn_body[i].x * SN_CELL, sn_body[i].y * SN_CELL + 8, SN_CELL, SN_CELL, SSD1306_WHITE);
            } else {
                display.fillRect(sn_body[i].x * SN_CELL + 1, sn_body[i].y * SN_CELL + 9, SN_CELL - 2, SN_CELL - 2, SSD1306_WHITE);
            }
        }

        display.drawLine(0, 7, SN_W, 7, SSD1306_WHITE);
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0);
        display.print("Score:");
        display.print(sn_score);

        uint8_t arrow_x = 100;
        if (sn_dir == 0) { display.print(" >");  }
        if (sn_dir == 1) { display.print(" v");  }
        if (sn_dir == 2) { display.print(" <");  }
        if (sn_dir == 3) { display.print(" ^");  }

        display.display();
        delay(SN_SPEED - min((uint16_t)80, (uint16_t)(sn_score * 2)));
    }
}