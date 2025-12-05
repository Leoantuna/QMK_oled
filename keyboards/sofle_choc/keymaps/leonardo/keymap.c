#include QMK_KEYBOARD_H
#include "ocean_dream.h"

// =======================
// Layers
// =======================

enum custom_layers {
    _BASE,
    _FN,
    _RGB
};

// =======================
// Keymaps
// =======================

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] =
        LAYOUT(
            KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,    KC_MINS,
            KC_ESC, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,    KC_BSPC,
            KC_TAB, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN, KC_QUOT,
            KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_MUTE,KC_MPLY,KC_N,   KC_M,   KC_COMM, KC_DOT,
            KC_SLSH,KC_RSFT,KC_LCTL,KC_LALT,KC_LGUI,KC_ENT, LT(_RGB,KC_NO),LT(_FN,KC_NO), KC_SPC, KC_RGUI, KC_RALT, KC_RCTL
        ),

    [_FN] =
        LAYOUT(
            KC_NO,  KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN, KC_DEL,
            KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_NO,
            KC_CAPS,KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_PSCR,KC_UP,  KC_LBRC,KC_RBRC,KC_EQL,  KC_BSLS,
            KC_LSFT,KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_LEFT,KC_DOWN,KC_RGHT, KC_NO,
            KC_UNDS,KC_RSFT,KC_LCTL,KC_LALT,KC_LGUI,KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_RGUI,KC_RALT, KC_RCTL
        ),

    [_RGB] =
        LAYOUT(
            RM_TOGG,RM_ON,  RM_NEXT,RM_HUEU,RM_SATU,RM_VALU,KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,
            KC_NO,  RM_OFF, RM_PREV,RM_HUED,RM_SATD,RM_VALD,KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,
            KC_NO,  RM_SPDU,KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,
            KC_NO,  RM_SPDD,KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,
            KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO
        ),
};

// =======================
// OLED
// =======================

// Girar sólo el lado esclavo 180°
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    // Prueba primero con 270
    return OLED_ROTATION_270;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // Lado izquierdo (master): Ocean Dream ocupando toda la pantalla
        render_stars();          // función principal de ocean_dream.c
    } else {
        // Lado derecho (slave): texto estático muy ligero
        oled_clear();
        oled_set_cursor(0, 0);
         oled_write_ln_P(PSTR("   ______   "), false);
        oled_write_ln_P(PSTR("  /| __ |\\ "), false);
        oled_write_ln_P(PSTR(" | |[__]| |"), false);
        oled_write_ln_P(PSTR("  \\|____|/ "), false);
    }
    return false;
}
