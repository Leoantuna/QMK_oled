#include QMK_KEYBOARD_H

enum custom_layers {
    _BASE,
    _FN,
    _RGB
};

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

#ifdef OLED_ENABLE

// Si el lado esclavo está físicamente invertido, lo giramos 180°
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;
    }
    return rotation;
}

// ---------- RENDER MASTER (lado principal) ----------

static void render_layer_state_oled(void) {
    oled_write_ln_P(PSTR("Layer"), false);
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case _BASE:
            oled_write_ln_P(PSTR(" BASE"), false);
            break;
        case _FN:
            oled_write_ln_P(PSTR(" FN  "), false);
            break;
        case _RGB:
            oled_write_ln_P(PSTR(" RGB "), false);
            break;
        default:
            oled_write_ln_P(PSTR(" ??? "), false);
            break;
    }
}

static void render_wpm_oled(void) {
    uint8_t wpm = get_current_wpm();
    char    wpm_str[4];
    snprintf(wpm_str, sizeof(wpm_str), "%3d", wpm);

    oled_write_ln_P(PSTR("WPM"), false);
    oled_write_P(PSTR("  "), false);
    oled_write(wpm_str, false);
}

static void render_lock_status_oled(void) {
    oled_write_ln_P(PSTR("Lock"), false);
    oled_write_P(host_keyboard_led_state().caps_lock ? PSTR(" CAPS") : PSTR(" ----"), false);
    oled_write_P(PSTR("\n"), false);
}

static void render_master_oled(void) {
    oled_clear();
    render_layer_state_oled();
    oled_write_P(PSTR("\n"), false);
    render_wpm_oled();
    oled_write_P(PSTR("\n"), false);
    render_lock_status_oled();
}

// ---------- RENDER SLAVE (lado secundario) ----------

// Pequeña "animación" de barra
static uint32_t anim_timer = 0;
static uint8_t  anim_pos   = 0;

static void render_slave_oled(void) {
    // Encabezado fijo
    oled_set_cursor(0, 0);
    oled_write_ln_P(PSTR(" SOFLE CHOC "), false);
    oled_write_ln_P(PSTR("  Leonardo  "), false);
    oled_write_P(PSTR("\n"), false);

    // Barra animada simple
    if (timer_elapsed32(anim_timer) > 120) {
        anim_timer = timer_read32();
        anim_pos   = (anim_pos + 1) % 10;
    }

    oled_set_cursor(0, 4);
    oled_write_P(PSTR("["), false);
    for (uint8_t i = 0; i < 10; i++) {
        if (i == anim_pos) {
            oled_write_P(PSTR("#"), false);
        } else {
            oled_write_P(PSTR("-"), false);
        }
    }
    oled_write_P(PSTR("]"), false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_master_oled();
    } else {
        render_slave_oled();
    }
    return false;
}

#endif  // OLED_ENABLE
