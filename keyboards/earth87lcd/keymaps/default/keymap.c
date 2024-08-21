// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp.h"
#include "qp_comms.h"

#include "qp_st77xx_opcodes.h"

#include "color.h"
#include "config.h"
#include QMK_KEYBOARD_H
#include <stdio.h>
#include "quantum/painter/qp.h"
#include <qp.h> // 1. Quantum Painter機能ヘッダの追加
// #include "qff/fontopoSOLID-Regular.qff.h"
// #include "qff/smartfont.qff.h"
#include "qff/8px.qff.h"
#include "qff/10px.qff.h"
#include "qff/16px.qff.h"
#include "qgf/Earth87lcd_logo.qgf.h"
#include "qgf/Earth87lcd_logo2.qgf.h"
#include "qgf/Earth87lcd_lcdimage.qgf.h" // LCDの背景画像


// ディスプレイデバイスの宣言
painter_device_t lcd;

// フォントハンドルの宣言
static painter_font_handle_t pixelfont_8px;
static painter_font_handle_t pixelfont_10px;
static painter_font_handle_t pixelfont_16px;

// イメージハンドルの宣言
static painter_image_handle_t img_logo;

// タイピング数カウンタを初期化
static uint32_t typing_count = 0;

// タイマー開始時間を保持する変数
static uint32_t start_time = 0;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
                 KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_MUTE,

                 KC_GRV,  KC_1,   KC_2,   KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,   KC_9,  KC_0, KC_MINS, KC_EQL, KC_INT3, KC_BSPC,
                 KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_ENT,
        KC_PSCR, KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS,
        KC_PGUP, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_INT1, KC_UP,   KC_RSFT,
    	KC_PGDN, KC_LCTL, KC_LGUI, KC_LALT, KC_BSPC, KC_DEL, KC_SPC,   KC_ENT,  KC_GRV,  TO(0),   TO(1),   TO(2),   KC_LEFT, KC_DOWN, KC_RGHT
    ),
	
	[1] = LAYOUT(
                 KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,

                 KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,
    	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,  KC_TRNS,  TO(0),   TO(1),   TO(2),   KC_TRNS, KC_TRNS, KC_TRNS
    ),
	
	[2] = LAYOUT(
                 KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,

                 KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,
    	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,  KC_TRNS,  TO(0),   TO(1),   TO(2),   KC_TRNS, KC_TRNS, KC_TRNS
    ),
};

#define _LAYER0 0
#define _LAYER1 1
#define _LAYER2 2

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =   { ENCODER_CCW_CW(KC_VOLU, KC_VOLD)  },
    [1] =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS)  },
    [2] =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS)  }
};
#endif


void keyboard_post_init_kb(void) {
    //Display timeout
    wait_ms(LCD_WAIT_TIME);
    lcd = qp_st7735_make_spi_device(LCD_HEIGHT, LCD_WIDTH, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, LCD_SPI_DIVISOR, SPI_MODE);
    qp_init(lcd, LCD_ROTATION);

    // Some screens have inverted colors
    #ifdef LCD_INVERT_COLOR
    qp_comms_start(lcd);
    qp_comms_command(lcd, ST77XX_CMD_INVERT_ON);
    qp_comms_stop(lcd);
    #endif

    // Display offset
    qp_set_viewport_offsets(lcd, LCD_OFFSET_X, LCD_OFFSET_Y);

    // Power on display, fill with white
    qp_power(lcd, 1);
    qp_rect(lcd, 0, 0, LCD_HEIGHT, LCD_WIDTH, HSV_BLACK, 1);

	// タイマーの初期化
    start_time = timer_read32();

	// フォントの読み込み
	pixelfont_8px = qp_load_font_mem(font_8px);
	pixelfont_10px = qp_load_font_mem(font_10px);
	pixelfont_16px = qp_load_font_mem(font_16px);
		
	// Logo画像の表示
    img_logo = qp_load_image_mem(gfx_Earth87lcd_lcdimage);
    qp_drawimage(lcd, 0, 0, img_logo);
	
    
	// keyboard_post_init_user() を呼び出して他の初期化を完了
    keyboard_post_init_user();
}

// Layerの表示
void render_layer_state_with_qp(void) {
    char layer_text[16];
    uint8_t current_layer = biton32(layer_state);

    switch (current_layer) {
        case _LAYER0:
            snprintf(layer_text, sizeof(layer_text), "0");
            break;
        case _LAYER1:
            snprintf(layer_text, sizeof(layer_text), "1");
            break;
        case _LAYER2:
            snprintf(layer_text, sizeof(layer_text), "2");
            break;
        default:
            snprintf(layer_text, sizeof(layer_text), "Default");
    }

	qp_drawtext(lcd, 37, 34, pixelfont_16px, layer_text);
	qp_flush(lcd);
}

bool qp_task_user(void) {
    render_layer_state_with_qp(); // Quantum Painter 用のレイヤー表示関数を呼び出し
    return false;
}

// キーが押されたときに呼び出される関数
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        typing_count++;  // キーが押されたときにカウンターを増加
    }
    return true;
}

// タイピング数をLCDに表示する関数
//void render_typing_count(void) {
//       char count_text[32];
//        snprintf(count_text, sizeof(count_text), "%lu", typing_count);  // カウントをテキストに変換
//       qp_drawtext(lcd, 37, 63, pixelfont_16px, count_text);  // タイピング数を表示
//}

void render_typing_count(void) {
    char count_text[32];
    snprintf(count_text, sizeof(count_text), "%lu", typing_count);  // カウントをテキストに変換

    // typing_count の桁数を計算
    int num_digits = 0;
    uint32_t temp = typing_count;
    do {
        num_digits++;
        temp /= 10;
    } while (temp > 0);

    // 桁数に応じて表示位置を調整
    int16_t base_x_position = 40;  // 基本のX座標
    int16_t adjusted_x_position = base_x_position - (num_digits * 3);

    // タイピング数を表示
    qp_drawtext(lcd, adjusted_x_position, 64, pixelfont_16px, count_text); 
    qp_flush(lcd);  // 表示を更新
}

void render_uptime(void) {
    // 経過時間を計算
    uint32_t elapsed_time = timer_elapsed32(start_time);

    // 秒、分、時間に変換
    uint32_t seconds = (elapsed_time / 1000) % 60;
    uint32_t minutes = (elapsed_time / 60000) % 60;
    uint32_t hours = elapsed_time / 3600000;

    // 表示用の文字列を作成
    char uptime_text[32];
    snprintf(uptime_text, sizeof(uptime_text), "%02lu:%02lu:%02lu", hours, minutes, seconds);

    qp_drawtext(lcd, 19, 94, pixelfont_16px, uptime_text);
    qp_flush(lcd);
}

void render_firmware_version(void) {
    // ファームウェアバージョンを表示
    qp_drawtext(lcd, 26, 124, pixelfont_16px, "v1.1.5");
    qp_flush(lcd);
}

void matrix_scan_user(void) {
	render_firmware_version();  // ファームウェアバージョンを表示
    qp_task_user(); // 現在のレイヤーを表示
	render_typing_count();  // タイピング数を表示
	render_uptime();  // アップタイムを表示
}