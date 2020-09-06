#include QMK_KEYBOARD_H

enum combos {
    FD_BASELAYER,
    VC_CPLAYER
};

const uint16_t PROGMEM fd_combo[] = {KC_F, KC_D, COMBO_END};
const uint16_t PROGMEM vc_combo[] = {KC_V, KC_C, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [FD_BASELAYER] = COMBO(fd_combo, XXXXXXX),
  [VC_CPLAYER] = COMBO(vc_combo, XXXXXXX)
};

enum sofle_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _QWERTY,
    CPLAYER
};

enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  ESC   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | \ |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Shift  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  Backspace   |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |Ctrl+Space|   Z  |   X  |   C  |   V  |   B  | Mute |    | Sleep |   N  |   M  |   ,  |   .  |   /  |CAPSLOCK|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | Lbf | COPY. alt |PASTE, ctrl | /Enter, command  /       \Space, command \  | Left | Up | Down | Right |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_QWERTY] = LAYOUT( \
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_GRV, \
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_NONUS_BSLASH, \
  KC_LALT,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  RALT_T(KC_BSPC), \
  LCTL(KC_SPC), KC_Z, KC_X,  KC_C,    KC_V,    KC_B, KC_MUTE,     RGUI(RCTL(KC_Q)), KC_N,  KC_M,    KC_COMM,  KC_DOT, KC_SLSH,  KC_CAPSLOCK, \
  KC_UNDO, KC_LALT, KC_LCTRL, KC_LSHIFT, LCMD_T(KC_ENT),      RCMD_T(KC_SPC),  KC_RSHIFT, KC_RCTRL, KC_RALT, KC_RIGHT \
),
[CPLAYER] = LAYOUT( \
  _______,   _______,   _______,    _______,    _______,    _______,         _______,    _______,    _______,    _______,    _______,  _______, \
  _______,   _______,   _______,    _______,    _______,    _______,         _______,    _______,    _______,    _______,    _______,  _______, \
  _______,   _______,   _______,    _______,    _______,    _______,         _______,    _______,    _______,    _______, _______,  _______, \
  _______, LCMD(KC_Z), LCMD(KC_X),  LCMD(KC_C),    LCMD(KC_V),               _______, _______,     _______, _______,  _______,    _______,  _______, _______,  _______, \
    _______, _______, _______, _______, _______,      _______,  _______, _______, _______, _______ \
)
};

#ifdef OLED_DRIVER_ENABLE

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0
    };

    oled_write_P(qmk_logo, false);
}

static void print_status_narrow(void) {
    // Print current mode
    oled_write_P(PSTR("\n"), false);
    oled_write_ln_P(PSTR("MODE"), false);
    oled_write_ln_P(PSTR(""), false);

    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("Qwrt"), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case CPLAYER:
            oled_write_ln_P(PSTR("CP"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
    }
    return true;
}

void process_combo_event(uint8_t combo_index, bool pressed) {
    switch (combo_index)
    {
    case FD_BASELAYER:
        if (pressed) {
            layer_clear();
            layer_on(_QWERTY);
        }
        break;
    case VC_CPLAYER:
        if (pressed) {
            layer_on(CPLAYER);
        }
    default:
        break;
    }
}

#ifdef ENCODER_ENABLE

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_RIGHT);
        } else {
            tap_code(KC_LEFT);
        }
    }
}

#endif
