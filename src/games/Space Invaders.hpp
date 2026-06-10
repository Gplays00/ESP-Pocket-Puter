#pragma once
#include "../global.hpp"

#define SI_W          128
#define SI_H          64
#define SI_ROWS       3
#define SI_COLS       8
#define SI_INV_W      10
#define SI_INV_H      6
#define SI_INV_TOTAL  (SI_ROWS * SI_COLS)
#define SI_BULLET_SPD 4
#define SI_MAX_EBUL   4

static bool     si_inv[SI_ROWS][SI_COLS];
static int16_t  si_inv_x, si_inv_y;
static int8_t   si_inv_dx;
static int16_t  si_px;
static int16_t  si_bx, si_by;
static bool     si_bactive;
static int16_t  si_ebx[SI_MAX_EBUL], si_eby[SI_MAX_EBUL];
static bool     si_ebactive[SI_MAX_EBUL];
static uint16_t si_score;
static uint8_t  si_lives;
static uint8_t  si_move_timer;
static uint8_t  si_move_speed;
static uint8_t  si_shoot_timer;

static int16_t SI_InvLeft() {
    for (int c = 0; c < SI_COLS; c++)
        for (int r = 0; r < SI_ROWS; r++)
            if (si_inv[r][c]) return c;
    return 0;
}

static int16_t SI_InvRight() {
    for (int c = SI_COLS - 1; c >= 0; c--)
        for (int r = 0; r < SI_ROWS; r++)
            if (si_inv[r][c]) return c;
    return SI_COLS - 1;
}

static int SIAlive() {
    int count = 0;
    for (int r = 0; r < SI_ROWS; r++)
        for (int c = 0; c < SI_COLS; c++)
            if (si_inv[r][c]) count++;
    return count;
}

static void SIReset() {
    si_inv_x     = 4;
    si_inv_y     = 8;
    si_inv_dx    = 1;
    si_px        = SI_W / 2 - 4;
    si_bactive   = false;
    si_score     = 0;
    si_lives     = 3;
    si_move_timer  = 0;
    si_move_speed  = 20;
    si_shoot_timer = 0;
    for (int r = 0; r < SI_ROWS; r++)
        for (int c = 0; c < SI_COLS; c++)
            si_inv[r][c] = true;
    for (int i = 0; i < SI_MAX_EBUL; i++) si_ebactive[i] = false;
}

static void SIEnemyShoot() {
    si_shoot_timer++;
    if (si_shoot_timer < 30) return;
    si_shoot_timer = 0;
    for (int i = 0; i < SI_MAX_EBUL; i++) {
        if (!si_ebactive[i]) {
            int col = random(0, SI_COLS);
            int row = -1;
            for (int r = SI_ROWS - 1; r >= 0; r--) {
                if (si_inv[r][col]) { row = r; break; }
            }
            if (row >= 0) {
                si_ebx[i] = si_inv_x + col * (SI_INV_W + 2) + SI_INV_W / 2;
                si_eby[i] = si_inv_y + row * (SI_INV_H + 3) + SI_INV_H;
                si_ebactive[i] = true;
            }
            break;
        }
    }
}

void SpaceInvaders() {
    SIReset();
    bool waiting  = true;
    bool exit_sel = false;
    bool gameover = false;
    bool won      = false;

    while (true) {
        bool left   = ReadButton(BUTTON_LEFT);
        bool right  = ReadButton(BUTTON_RIGHT);
        bool center = ReadButton(BUTTON_CENTER);

        display.clearDisplay();

        if (waiting) {
            display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.setCursor(20, 14);
            display.print("Space Invaders");
            display.setCursor(4, 28);
            display.print("Left/Right = move");
            display.setCursor(16, 40);
            display.print("OK = shoot");
            display.setCursor(14, 52);
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
            display.setCursor(won ? 28 : 22, 8);
            display.print(won ? "You Win!" : "Game Over!");
            display.setCursor(24, 20);
            display.print("Score: ");
            display.print(si_score);
            display.setCursor(36, 38);
            display.print(exit_sel ? "  Play" : "> Play");
            display.setCursor(36, 50);
            display.print(exit_sel ? "> Exit" : "  Exit");
            if (center) {
                HaltTillRelease(BUTTON_CENTER);
                if (exit_sel) return;
                SIReset();
                gameover = false;
                exit_sel = false;
                won      = false;
                waiting  = true;
            }
            display.display();
            delay(40);
            continue;
        }

        if (left)  si_px -= 3;
        if (right) si_px += 3;
        si_px = constrain(si_px, 0, SI_W - 9);

        if (center && !si_bactive) {
            si_bx      = si_px + 4;
            si_by      = SI_H - 14;
            si_bactive = true;
        }

        if (si_bactive) {
            si_by -= SI_BULLET_SPD;
            if (si_by < 0) si_bactive = false;
            for (int r = 0; r < SI_ROWS; r++) {
                for (int c = 0; c < SI_COLS; c++) {
                    if (!si_inv[r][c]) continue;
                    int16_t ix = si_inv_x + c * (SI_INV_W + 2);
                    int16_t iy = si_inv_y + r * (SI_INV_H + 3);
                    if (si_bx >= ix && si_bx <= ix + SI_INV_W && si_by >= iy && si_by <= iy + SI_INV_H) {
                        si_inv[r][c] = false;
                        si_bactive   = false;
                        si_score     += 10;
                        if (SIAlive() == 0) { gameover = true; won = true; }
                    }
                }
            }
        }

        si_move_timer++;
        if (si_move_timer >= si_move_speed) {
            si_move_timer = 0;
            int left_col  = SI_InvLeft();
            int right_col = SI_InvRight();
            int16_t rightEdge = si_inv_x + right_col * (SI_INV_W + 2) + SI_INV_W;
            int16_t leftEdge  = si_inv_x + left_col  * (SI_INV_W + 2);
            if (si_inv_dx > 0 && rightEdge >= SI_W - 2) {
                si_inv_dx = -1;
                si_inv_y += 3;
            } else if (si_inv_dx < 0 && leftEdge <= 2) {
                si_inv_dx = 1;
                si_inv_y += 3;
            } else {
                si_inv_x += si_inv_dx * 2;
            }
            si_move_speed = max(4, 20 - (SI_INV_TOTAL - SIAlive()));
        }

        SIEnemyShoot();
        for (int i = 0; i < SI_MAX_EBUL; i++) {
            if (!si_ebactive[i]) continue;
            si_eby[i] += 2;
            if (si_eby[i] > SI_H) { si_ebactive[i] = false; continue; }
            if (si_ebx[i] >= si_px && si_ebx[i] <= si_px + 9 && si_eby[i] >= SI_H - 12) {
                si_ebactive[i] = false;
                si_lives--;
                if (si_lives == 0) { gameover = true; won = false; }
            }
        }

        for (int r = 0; r < SI_ROWS; r++) {
            for (int c = 0; c < SI_COLS; c++) {
                if (!si_inv[r][c]) continue;
                int16_t ix = si_inv_x + c * (SI_INV_W + 2);
                int16_t iy = si_inv_y + r * (SI_INV_H + 3);
                display.fillRect(ix, iy, SI_INV_W, SI_INV_H, SSD1306_WHITE);
                display.drawPixel(ix, iy, SSD1306_BLACK);
                display.drawPixel(ix + SI_INV_W - 1, iy, SSD1306_BLACK);
            }
        }

        if (si_bactive) display.drawFastVLine(si_bx, si_by, 4, SSD1306_WHITE);
        for (int i = 0; i < SI_MAX_EBUL; i++) {
            if (si_ebactive[i]) display.drawFastVLine(si_ebx[i], si_eby[i], 4, SSD1306_WHITE);
        }

        display.fillRect(si_px,     SI_H - 12, 9, 3, SSD1306_WHITE);
        display.fillRect(si_px + 2, SI_H - 15, 5, 3, SSD1306_WHITE);
        display.fillRect(si_px + 4, SI_H - 18, 1, 3, SSD1306_WHITE);

        display.drawLine(0, SI_H - 9, SI_W, SI_H - 9, SSD1306_WHITE);

        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, SI_H - 7);
        display.print("SC:");
        display.print(si_score);
        display.setCursor(90, SI_H - 7);
        display.print("LV:");
        display.print(si_lives);

        if (si_inv_y + SI_ROWS * (SI_INV_H + 3) >= SI_H - 12) { gameover = true; won = false; }

        display.display();
        delay(16);
    }
}