#pragma once
#include "../global.hpp"

#define PG_W         128
#define PG_H         64
#define PG_PAD_W     3
#define PG_PAD_H     14
#define PG_BALL_SIZE 3
#define PG_PAD_SPEED 3
#define PG_WIN_SCORE 5

static float    pg_ball_x, pg_ball_y;
static float    pg_bvx, pg_bvy;
static int16_t  pg_p1y, pg_p2y;
static uint8_t  pg_p1score, pg_p2score;

static void PongResetBall() {
    pg_ball_x = PG_W / 2;
    pg_ball_y = PG_H / 2;
    pg_bvx    = (random(0, 2) ? 1.5f : -1.5f);
    pg_bvy    = (random(0, 2) ? 1.2f : -1.2f);
}

static void PongReset() {
    pg_p1y     = PG_H / 2 - PG_PAD_H / 2;
    pg_p2y     = PG_H / 2 - PG_PAD_H / 2;
    pg_p1score = 0;
    pg_p2score = 0;
    PongResetBall();
}

static void PongAI() {
    float center = pg_p2y + PG_PAD_H / 2;
    if (center < pg_ball_y - 2) pg_p2y += 2;
    if (center > pg_ball_y + 2) pg_p2y -= 2;
    pg_p2y = constrain(pg_p2y, 0, PG_H - PG_PAD_H);
}

void PongGame() {
    PongReset();
    bool waiting  = true;
    bool exit_sel = false;
    bool gameover = false;

    while (true) {
        bool left   = ReadButton(BUTTON_LEFT);
        bool right  = ReadButton(BUTTON_RIGHT);
        bool center = ReadButton(BUTTON_CENTER);

        display.clearDisplay();

        if (waiting) {
            display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.setCursor(40, 16);
            display.print("PONG");
            display.setCursor(8, 30);
            display.print("Left/Right = move");
            display.setCursor(14, 42);
            display.print("Press OK to start");
            if (center) { HaltTillRelease(BUTTON_CENTER); waiting = false; }
            display.display();
            delay(40);
            continue;
        }

        if (gameover) {
            if (right) { exit_sel = !exit_sel; HaltTillRelease(BUTTON_RIGHT); }
            display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.setCursor(34, 6);
            display.print(pg_p1score >= PG_WIN_SCORE ? "You Win!" : "You Lose!");
            display.setCursor(28, 20);
            display.print(pg_p1score);
            display.print(" - ");
            display.print(pg_p2score);
            display.setCursor(36, 38);
            display.print(exit_sel ? "  Play" : "> Play");
            display.setCursor(36, 50);
            display.print(exit_sel ? "> Exit" : "  Exit");
            if (center) {
                HaltTillRelease(BUTTON_CENTER);
                if (exit_sel) return;
                PongReset();
                gameover  = false;
                exit_sel  = false;
                waiting   = true;
            }
            display.display();
            delay(40);
            continue;
        }

        if (left)  pg_p1y -= PG_PAD_SPEED;
        if (right) pg_p1y += PG_PAD_SPEED;
        pg_p1y = constrain(pg_p1y, 0, PG_H - PG_PAD_H);

        PongAI();

        pg_ball_x += pg_bvx;
        pg_ball_y += pg_bvy;

        if (pg_ball_y <= 0 || pg_ball_y + PG_BALL_SIZE >= PG_H) pg_bvy = -pg_bvy;

        if (pg_ball_x <= PG_PAD_W + 1 &&
            pg_ball_y + PG_BALL_SIZE >= pg_p1y &&
            pg_ball_y <= pg_p1y + PG_PAD_H) {
            pg_bvx  = abs(pg_bvx) * 1.05f;
            pg_ball_x = PG_PAD_W + 2;
        }

        if (pg_ball_x + PG_BALL_SIZE >= PG_W - PG_PAD_W - 1 &&
            pg_ball_y + PG_BALL_SIZE >= pg_p2y &&
            pg_ball_y <= pg_p2y + PG_PAD_H) {
            pg_bvx  = -abs(pg_bvx) * 1.05f;
            pg_ball_x = PG_W - PG_PAD_W - PG_BALL_SIZE - 2;
        }

        if (pg_ball_x < 0)    { pg_p2score++; PongResetBall(); delay(500); }
        if (pg_ball_x > PG_W) { pg_p1score++; PongResetBall(); delay(500); }

        if (pg_p1score >= PG_WIN_SCORE || pg_p2score >= PG_WIN_SCORE) gameover = true;

        pg_bvx = constrain(pg_bvx, -4.0f, 4.0f);
        pg_bvy = constrain(pg_bvy, -4.0f, 4.0f);

        display.fillRect(0, pg_p1y, PG_PAD_W, PG_PAD_H, SSD1306_WHITE);
        display.fillRect(PG_W - PG_PAD_W, pg_p2y, PG_PAD_W, PG_PAD_H, SSD1306_WHITE);
        display.fillRect((int)pg_ball_x, (int)pg_ball_y, PG_BALL_SIZE, PG_BALL_SIZE, SSD1306_WHITE);

        for (int y = 0; y < PG_H; y += 6) display.drawPixel(PG_W / 2, y, SSD1306_WHITE);

        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(44, 1);
        display.print(pg_p1score);
        display.print("-");
        display.print(pg_p2score);

        display.display();
        delay(25);
    }
}