// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "quantum.h"
#include "keycode_utils.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	
    [0] = LAYOUT(
                               TO(9)      ,TO(1),
        KC_F1      ,KC_F2     ,KC_F3      ,KC_F4,
        KC_F5      ,KC_F6     ,KC_F7      ,KC_F8
    ),

    [1] = LAYOUT(
                               TO(0)      ,TO(2),
        KC_TRNS    ,KC_TRNS   ,KC_TRNS    ,KC_TRNS ,
        KC_TRNS    ,KC_TRNS   ,KC_TRNS    ,KC_TRNS
    ),

    [2] = LAYOUT(
                               TO(1)      ,TO(3),
        KC_TRNS    ,KC_TRNS   ,KC_TRNS    ,KC_TRNS ,
        KC_TRNS    ,KC_TRNS   ,KC_TRNS    ,KC_TRNS
    ),

    [3] = LAYOUT(
                               TO(2)      ,TO(4),
        KC_TRNS    ,KC_TRNS   ,KC_TRNS    ,KC_TRNS ,
        KC_TRNS    ,KC_TRNS   ,KC_TRNS    ,KC_TRNS
    ),

    [4] = LAYOUT(
                               TO(3)      ,TO(5),
        KC_TRNS    ,KC_TRNS   ,KC_TRNS    ,KC_TRNS ,
        KC_TRNS    ,KC_TRNS   ,KC_TRNS    ,KC_TRNS
    ),

    [5] = LAYOUT(
                               TO(4)      ,TO(6),
        KC_TRNS    ,KC_TRNS   ,KC_TRNS    ,KC_TRNS ,
        KC_TRNS    ,KC_TRNS   ,KC_TRNS    ,KC_TRNS
    ),

    [6] = LAYOUT(
                               TO(5)      ,TO(7),
        KC_TRNS    ,KC_TRNS   ,KC_TRNS    ,KC_TRNS ,
        KC_TRNS    ,KC_TRNS   ,KC_TRNS    ,KC_TRNS
    ),

    [7] = LAYOUT(
                               TO(6)      ,TO(8),
        KC_TRNS    ,KC_TRNS   ,KC_TRNS    ,KC_TRNS ,
        KC_TRNS    ,KC_TRNS   ,KC_TRNS    ,KC_TRNS
    ),

    [8] = LAYOUT(
                               TO(7)      ,TO(9),
        KC_TRNS    ,KC_TRNS   ,KC_TRNS    ,KC_TRNS ,
        KC_TRNS    ,KC_TRNS   ,KC_TRNS    ,KC_TRNS
    ),

    [9] = LAYOUT(
                               TO(8)      ,TO(0),
        KC_TRNS    ,KC_TRNS   ,KC_TRNS    ,KC_TRNS ,
        KC_TRNS    ,KC_TRNS   ,KC_TRNS    ,KC_TRNS
    )

};

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
}


void oled_write_layer_state(void) {
    // 現在のレイヤー番号を取得
    uint8_t layer = get_highest_layer(layer_state);
    
    // 「Layer:」の文字を表示
    oled_write_P(PSTR("Layer: "), false);

    // レイヤー番号を文字列として表示
    char layer_str[3]; // レイヤー番号を格納する文字列 (2桁まで対応)
    snprintf(layer_str, sizeof(layer_str), "%d", layer);
    oled_write_ln(layer_str, false);  // 改行付きで表示
}


void render_keycodes_row(void) {
    uint8_t layer = get_highest_layer(layer_state);

	oled_set_cursor(0, 2);  // 2行目の先頭にカーソルを移動

    // 1行目 (0,2), (0,3), (0,4), (0,5)
    for (int col = 2; col <= 5; col++) {
        // 動的にキーコードを取得
        uint16_t keycode = keymap_key_to_keycode(layer, (keypos_t){.row = 0, .col = col});
        
        // キーコード名を取得して表示
        oled_write(keycode_to_name(keycode), false);  
        oled_write_P(PSTR(" "), false);  // スペースで区切り
    }

    oled_set_cursor(0, 3);  // 4行目の先頭にカーソルを移動

    // 2行目 (0,6), (0,7), (0,8), (0,9)
    for (int col = 6; col <= 9; col++) {
        // 動的にキーコードを取得
        uint16_t keycode = keymap_key_to_keycode(layer, (keypos_t){.row = 0, .col = col});
        
        // キーコード名を取得して表示
        oled_write(keycode_to_name(keycode), false);
        oled_write_P(PSTR(" "), false);  // スペースで区切り
    }
}


bool oled_task_user(void) {
    oled_write_layer_state();       // 現在のレイヤーを表示する関数
    render_keycodes_row();      // 指定されたキーコードを2行で表示
    return false;
}