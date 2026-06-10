#pragma once
#include "../global.hpp"

#define FB_SCREEN_W   128
#define FB_SCREEN_H   64
#define FB_GRAVITY    2
#define FB_FLAP       -6
#define FB_PIPE_W     8
#define FB_PIPE_GAP   20
#define FB_PIPE_SPEED 2
#define FB_BIRD_X     20
#define FB_BIRD_SIZE  4

enum FBState { FB_WAITING, FB_PLAYING, FB_DEAD };

struct FBPipe { int16_t x; int16_t gap_y; bool scored; };

static int16_t  fb_bird_y;
static int16_t  fb_bird_vel;
static uint16_t fb_score;
static FBState  fb_state;
static FBPipe   fb_pipes[2];

static void FBResetPipes() {
    fb_pipes[0] = { FB_SCREEN_W + 10, 12 + random(0, 28), false };
    fb_pipes[1] = { FB_SCREEN_W + 10 + (FB_SCREEN_W / 2), 12 + random(0, 28), false };
}

static void FBReset() {
    fb_bird_y = FB_SCREEN_H / 2;
    fb_bird_vel = 0;
    fb_score = 0;
    fb_state = FB_WAITING;
    FBResetPipes();
}

static bool FBCollides(FBPipe& p) {
    bool in_x = (FB_BIRD_X + FB_BIRD_SIZE > p.x) && (FB_BIRD_X < p.x + FB_PIPE_W);
    bool in_y = (fb_bird_y < p.gap_y) || (fb_bird_y + FB_BIRD_SIZE > p.gap_y + FB_PIPE_GAP);
    return in_x && in_y;
}

static void FBDrawPipe(FBPipe& p) {
    display.fillRect(p.x, 0, FB_PIPE_W, p.gap_y, SSD1306_WHITE);
    display.fillRect(p.x, p.gap_y + FB_PIPE_GAP, FB_PIPE_W, FB_SCREEN_H - (p.gap_y + FB_PIPE_GAP), SSD1306_WHITE);
}

void FlappyBird() {
    FBReset();
    bool exit_selected = false;

    while (true) {
        bool ok    = ReadButton(BUTTON_CENTER);
        bool right = ReadButton(BUTTON_RIGHT);
        display.clearDisplay();

        if (fb_state == FB_WAITING) {
            display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.setCursor(20, 20);
            display.print("Flappy Bird");
            display.setCursor(14, 38);
            display.print("Press OK to start");
            display.fillRect(FB_BIRD_X, FB_SCREEN_H / 2, FB_BIRD_SIZE, FB_BIRD_SIZE, SSD1306_WHITE);
            if (ok) {
                HaltTillRelease(BUTTON_CENTER);
                fb_state    = FB_PLAYING;
                fb_bird_vel = FB_FLAP;
            }
        }

        else if (fb_state == FB_PLAYING) {
            if (ok) fb_bird_vel = FB_FLAP;
            fb_bird_vel += FB_GRAVITY / 2;
            fb_bird_y   += fb_bird_vel / 2;

            for (int i = 0; i < 2; i++) {
                fb_pipes[i].x -= FB_PIPE_SPEED;
                if (!fb_pipes[i].scored && fb_pipes[i].x + FB_PIPE_W < FB_BIRD_X) {
                    fb_pipes[i].scored = true;
                    fb_score++;
                }
                if (fb_pipes[i].x + FB_PIPE_W < 0) {
                    fb_pipes[i].x      = FB_SCREEN_W + 10;
                    fb_pipes[i].gap_y  = 12 + random(0, 28);
                    fb_pipes[i].scored = false;
                }
                FBDrawPipe(fb_pipes[i]);
                if (FBCollides(fb_pipes[i])) { fb_state = FB_DEAD; exit_selected = false; }
            }

            if (fb_bird_y < 0 || fb_bird_y + FB_BIRD_SIZE > FB_SCREEN_H) {
                fb_state = FB_DEAD; exit_selected = false;
            }

            display.fillRect(FB_BIRD_X, fb_bird_y, FB_BIRD_SIZE, FB_BIRD_SIZE, SSD1306_WHITE);
            display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.setCursor(2, 2);
            display.print(fb_score);
        }

        else if (fb_state == FB_DEAD) {
            if (right) { exit_selected = !exit_selected; HaltTillRelease(BUTTON_RIGHT); }

            display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.setCursor(44, 8);
            display.print("You died!");
            display.setCursor(44, 20);
            display.print("Score: ");
            display.print(fb_score);
            display.setCursor(40, 38);
            display.print(exit_selected ? "  Play" : "> Play");
            display.setCursor(40, 50);
            display.print(exit_selected ? "> Exit" : "  Exit");

            if (ok) {
                HaltTillRelease(BUTTON_CENTER);
                if (exit_selected) return; 
                FBReset();
                fb_state    = FB_PLAYING;
                fb_bird_vel = FB_FLAP;
            }
        }

        display.display();
        delay(40);
    }
}   