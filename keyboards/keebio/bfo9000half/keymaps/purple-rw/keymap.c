/* Copyright 2021-2023 Rhys Wong
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Only 34 keys (3x5+2 each hand) are really needed.
 * Additional keys are for conveninence, but limited by available keycaps.
 * Designed for use with Linux in mind, with US/English layout.
 */

#include QMK_KEYBOARD_H
#include "os_detection.h"
#ifdef AUDIO_ENABLE
#    include "muse.h"
#endif

enum planck_layers {
    _COLEMAK,	// Colemak-DH
    _QWERTY,    // Qwerty
    _HANDSDN,   // Hands Down Neu 30
    _COLEMNT,   // Colemanite
    _RAISE,     // Numbers & Symbols
    _LOWER,     // Navigation & Functions
    _KEYPD,     // Keypad
    _MODS,      // Modifiers, Multimedia & Macros
    _MOUSE,     // Mouse
    _ADJST      // Adjustment
};

enum planck_keycodes {
    COLEMAK = QK_USER,
    QWERTY,
    HANDSDN,
    COLEMNT,

    M_UNDO,
    M_CUT,
    M_COPY,
    M_PASTE,
    M_SELAL,    // select all
    M_ZMIN,     // zoom in
    M_ZMOUT     // zoom out
};

/* Operating system dependent shortcut keys */
const uint16_t PROGMEM osd_keys[][3] = {
                  /*  Linux       Windows     MacOS
                      xfce        Magnifier   accessibility  */
    /* M_UNDO  */   { C(KC_Z),    C(KC_Z),    G(KC_Z)       },
    /* M_CUT   */   { C(KC_X),    C(KC_X),    G(KC_X)       },
    /* M_COPY  */   { C(KC_C),    C(KC_C),    G(KC_C)       },
    /* M_PASTE */   { C(KC_V),    C(KC_V),    G(KC_V)       },
    /* M_SELAL */   { C(KC_A),    C(KC_A),    G(KC_A)       },
    /* M_ZMIN  */   { A(KC_WH_D), G(KC_EQL),  G(A(KC_EQL))  },
    /* M_ZMOUT */   { A(KC_WH_U), G(KC_MINS), G(A(KC_MINS)) }
};

/* Layer keys */
#define MODS    TT(_MODS)
#define MOUSE   TG(_MOUSE)
#define ADJST   TG(_ADJST)

/* Mod/Layer-tap keys */
#define MT_SPC  LSFT_T(KC_SPC)
#define LT_TAB  LT(_LOWER, KC_TAB)
#define LT_ENT  LT(_RAISE, KC_ENT)
#define LT_Z    LT(_KEYPD, KC_Z)
#define LT_X    LT(_KEYPD, KC_X)

/* One-shot modifier keys */
#define OS_LSFT OSM(MOD_LSFT)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_LALT OSM(MOD_LALT)
#define OS_LGUI OSM(MOD_LGUI)
#define OS_RSFT OSM(MOD_RSFT)
#define OS_RCTL OSM(MOD_RCTL)
#define OS_RALT OSM(MOD_RALT)
#define OS_RGUI OSM(MOD_RGUI)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak
 * ,--------------------------------------------------------------.
 * | Esc  | Left |Right |  7   | Del  |  6   | Down |  Up  |BkSpc |
 * |------+------+------+------+------+------+------+------+------|
 * |  9   |  5   |  3   |  1   |  '   |  0   |  2   |  4   |  8   |
 * |------+------+------+------+------+------+------+------+------|
 * |  Q   |  W   |  F   |  P   |  B   |  L   |  U   |  Y   |  ;   |
 * |------+------+------+------+------+------+------+------+------|
 * |  A   |  R   |  S   |  T   |  M   |  N   |  E   |  I   |  O   |
 * |------+------+------+------+------+------+------+------+------|
 * |  Z   |  X   |  C   |  D   |  G   |  H   |  J   |  K   |  V   |
 * |------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  | GUI  | Tab  |Shift |Enter |  ,   |  .   |  /   |
 * `--------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT(
    KC_ESC,  KC_LEFT, KC_RGHT, KC_7,    KC_DEL,  KC_6,    KC_DOWN, KC_UP,   KC_BSPC,
    KC_9,    KC_5,    KC_3,    KC_1,    KC_QUOT, KC_0,    KC_2,    KC_4,    KC_8,
    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_L,    KC_U,    KC_Y,    KC_SCLN,
    KC_A,    KC_R,    KC_S,    KC_T,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,
    LT_Z,    KC_X,    KC_C,    KC_D,    KC_G,    KC_H,    KC_J,    KC_K,    KC_V,
    KC_LCTL, KC_LALT, KC_LGUI, LT_TAB,  MT_SPC,  LT_ENT,  KC_COMM, KC_DOT,  KC_SLSH
),

/* Qwerty
 * ,--------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------|
 * |  Q   |  W   |  E   |  R   |  T   |  U   |  I   |  O   |  P   |
 * |------+------+------+------+------+------+------+------+------|
 * |  A   |  S   |  D   |  F   |  H   |  J   |  K   |  L   |  ;   |
 * |------+------+------+------+------+------+------+------+------|
 * |  Z   |  X   |  C   |  V   |  B   |  N   |  M   |  G   |  Y   |
 * |------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |
 * `--------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT(
    _______, _______, _______, KC_5,    _______, KC_6,    _______, _______, _______,
    KC_1,    KC_2,    KC_3,    KC_4,    _______, KC_7,    KC_8,    KC_9,    KC_0,
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
    LT_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_G,    KC_Y,
    _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Hands Down Neu 30
 * ,--------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------|
 * |  W   |  F   |  M   |  P   |  V   |  .   |  Q   |  J   |  Z   |
 * |------+------+------+------+------+------+------+------+------|
 * |  R   |  S   |  N   |  T   |  G   |  A   |  E   |  I   |  H   |
 * |------+------+------+------+------+------+------+------+------|
 * |  X   |  C   |  L   |  D   |  B   |  U   |  O   |  Y   |  K   |
 * |------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |  /   |  ;   |  ,   |
 * `--------------------------------------------------------------'
 */
[_HANDSDN] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,
    KC_W,    KC_F,    KC_M,    KC_P,    KC_V,    KC_DOT,  KC_Q,    KC_J,    KC_Z,
    KC_R,    KC_S,    KC_N,    KC_T,    KC_G,    KC_A,    KC_E,    KC_I,    KC_H,
    LT_X,    KC_C,    KC_L,    KC_D,    KC_B,    KC_U,    KC_O,    KC_Y,    KC_K,
    _______, _______, _______, _______, _______, _______, KC_SLSH, KC_SCLN, KC_COMM
),

/* Colemanite
 * ,--------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------|
 * |  B   |  L   |  W   |  M   |  Y   |  F   |  O   |  U   |  ;   |
 * |------+------+------+------+------+------+------+------+------|
 * |  N   |  R   |  S   |  T   |  G   |  H   |  E   |  I   |  A   |
 * |------+------+------+------+------+------+------+------+------|
 * |  Z   |  X   |  C   |  D   |  V   |  P   |  Q   |  J   |  K   |
 * |------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |  /   |  .   |  ,   |
 * `--------------------------------------------------------------'
 */
[_COLEMNT] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,
    KC_B,    KC_L,    KC_W,    KC_M,    KC_Y,    KC_F,    KC_O,    KC_U,    KC_SCLN,
    KC_N,    KC_R,    KC_S,    KC_T,    KC_G,    KC_H,    KC_E,    KC_I,    KC_A,
    LT_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_P,    KC_Q,    KC_J,    KC_K,
    _______, _______, _______, _______, _______, _______, KC_SLSH, KC_DOT,  KC_COMM
),

/* Numbers & Symbols
 * ,--------------------------------------------------------------.
 * |      |Zoom- |Zoom+ |      |      |      | Vol- | Vol+ |      |
 * |------+------+------+------+------+------+------+------+------|
 * |  ^   |  %   |  +   |  [   |  7   |  ]   |  !   |  ~   |  `   |
 * |------+------+------+------+------+------+------+------+------|
 * |  9   |  5   |  3   |  1   |  6   |  0   |  2   |  4   |  8   |
 * |------+------+------+------+------+------+------+------+------|
 * |  $   |  =   |  -   |  (   |  .   |  )   |  _   |  "   |  '   |
 * |------+------+------+------+------+------+------+------+------|
 * |  @   |  |   |  &   |  {   |  [   |  }   |  *   |  #   |  \   |
 * |------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | **** |      |      |      |
 * `--------------------------------------------------------------'
 */
 [_RAISE] = LAYOUT(
    _______, M_ZMOUT, M_ZMIN,  _______, _______, _______, KC_VOLD, KC_VOLU, _______,
    KC_CIRC, KC_PERC, KC_PLUS, KC_LBRC, KC_7,    KC_RBRC, KC_EXLM, KC_TILD, KC_GRV,
    KC_9,    KC_5,    KC_3,    KC_1,    KC_6,    KC_0,    KC_2,    KC_4,    KC_8,
    KC_DLR,  KC_EQL,  KC_MINS, KC_LPRN, KC_DOT,  KC_RPRN, KC_UNDS, KC_DQT,  KC_QUOT,
    KC_AT,   KC_PIPE, KC_AMPR, KC_LCBR, KC_LBRC, KC_RCBR, KC_ASTR, KC_HASH, KC_BSLS,
    _______, _______, _______, MODS,    _______, _______, _______, _______, _______
),

/* Navigation & Functions
 * ,--------------------------------------------------------------.
 * |      |      |      | F17  | F18  | F19  |PrScr |ScrLk |Pause |
 * |------+------+------+------+------+------+------+------+------|
 * | F13  | F14  | F15  | F16  | F20  | F21  | F22  | F23  | F24  |
 * |------+------+------+------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  | Ins  | PgUp |  Up  | PgDn | Menu |
 * |------+------+------+------+------+------+------+------+------|
 * |  F5  |  F6  |  F7  |  F8  | Home | Left | Down |Right | End  |
 * |------+------+------+------+------+------+------+------+------|
 * |  F9  | F10  | F11  | F12  | Tab  |BkSpc |Enter | Del  | Esc  |
 * |------+------+------+------+------+------+------+------+------|
 * |      |      |      | **** |      |      |      |      |      |
 * `--------------------------------------------------------------'
 */
 [_LOWER] = LAYOUT(
    _______, _______, _______, KC_F17,  KC_F18,  KC_F19,  KC_PSCR, KC_SCRL, KC_PAUS,
    KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_INS,  KC_PGUP, KC_UP,   KC_PGDN, KC_APP,
    KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,
    KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TAB,  KC_BSPC, KC_ENT,  KC_DEL,  KC_ESC,
    _______, _______, _______, _______, _______, MODS,    _______, _______, _______
),

/* Keypad
 * ,--------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |NumLk |  =   |  /   |  *   |  -   |
 * |------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |  *   |  7   |  8   |  9   |  /   |
 * |------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |  -   |  4   |  5   |  6   |  +   |
 * |------+------+------+------+------+------+------+------+------|
 * | **** |      |      |      |  0   |  1   |  2   |  3   |  .   |
 * |------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |  0   | Ent  |      |      |      |
 * `--------------------------------------------------------------'
 */
[_KEYPD] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, KC_NUM,  KC_PEQL, KC_PSLS, KC_PAST, KC_PMNS,
    _______, _______, _______, _______, KC_PAST, KC_P7,   KC_P8,   KC_P9,   KC_PSLS,
    _______, _______, _______, _______, KC_PMNS, KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
    _______, _______, _______, _______, KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_PDOT,
    _______, _______, _______, _______, KC_P0,   KC_PENT, KC_PCMM, KC_PDOT, KC_PSLS
),

/* Modifiers, Multimedia & Macros
 * ,--------------------------------------------------------------.
 * | Esc  |      |      |      |      |      |      |      |Eject |
 * |------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |ADJST |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------|
 * | Esc  |      |Zoom- |Zoom+ |MOUSE | Vol- | Mute | Vol+ |Eject |
 * |------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  | Cmd  |Shift |CapsWd|Shift | Cmd  | Alt  | Ctrl |
 * |------+------+------+------+------+------+------+------+------|
 * | Undo | Cut  | Copy |Paste |SelAll|Rewind| Play | FFwd |      |
 * |------+------+------+------+------+------+------+------+------|
 * |CapsLk|      |      | **** |      | **** |      |Reset |BootL |
 * `--------------------------------------------------------------'
 */
[_MODS] = LAYOUT(
    KC_ESC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_EJCT,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, ADJST,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_ESC,  XXXXXXX, M_ZMOUT, M_ZMIN,  MOUSE,   KC_VOLD, KC_MUTE, KC_VOLU, KC_EJCT,
    OS_LCTL, OS_LALT, OS_LGUI, OS_LSFT, CW_TOGG, OS_RSFT, OS_RGUI, OS_RALT, OS_RCTL,
    M_UNDO,  M_CUT,   M_COPY,  M_PASTE, M_SELAL, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX,
    KC_CAPS, XXXXXXX, XXXXXXX, _______, XXXXXXX, _______, XXXXXXX, QK_RBT,  QK_BOOT
),

/* Mouse
 * ,--------------------------------------------------------------.
 * | Exit |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------|
 * | Acc2 |WhlUp |  Up  |WhlDn | Exit |WhlUp |  Up  |WhlDn | Acc2 |
 * |------+------+------+------+------+------+------+------+------|
 * |      | Left | Down |Right |WhlLt | Left | Down |Right |WhlRt |
 * |------+------+------+------+------+------+------+------+------|
 * | Acc1 | Btn2 | Btn3 | Btn1 | Acc0 | Btn1 | Btn3 | Btn2 | Acc1 |
 * |------+------+------+------+------+------+------+------+------|
 * |      |      |      | Btn2 | Btn1 | Btn2 |      |      |      |
 * `--------------------------------------------------------------'
 */
[_MOUSE] = LAYOUT(
    MOUSE,   _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,
    KC_ACL2, KC_WH_U, KC_MS_U, KC_WH_D, MOUSE,   KC_WH_U, KC_MS_U, KC_WH_D, KC_ACL2,
    XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_L, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_R,
    KC_ACL1, KC_BTN2, KC_BTN3, KC_BTN1, KC_ACL0, KC_BTN1, KC_BTN3, KC_BTN2, KC_ACL1,
    _______, _______, _______, KC_BTN2, KC_BTN1, KC_BTN2, XXXXXXX, XXXXXXX, XXXXXXX
),

/* Adjust
 * ,--------------------------------------------------------------.
 * | Exit |      |      |      |      |      |      |      |Debug |
 * |------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------|
 * |Brght+| Sat+ | Hue+ |RGBmod|      |Colmnt|      |      |      |
 * |------+------+------+------+------+------+------+------+------|
 * |Brght-| Sat- | Hue- | RGB  |AGnorm|Colemk|Qwerty|HndsDn|      |
 * |------+------+------+------+------+------+------+------+------|
 * |BLbrth|  BL  | BL-  | BL+  |AGswap|      |      |      |      |
 * |------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |Reset |BootL |
 * `--------------------------------------------------------------'
 */
[_ADJST] = LAYOUT(
    ADJST,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DB_TOGG,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    RGB_VAI, RGB_SAI, RGB_HUI, RGB_MOD, XXXXXXX, HANDSDN, XXXXXXX, XXXXXXX, XXXXXXX,
    RGB_VAD, RGB_SAD, RGB_HUD, RGB_TOG, AG_NORM, COLEMAK, QWERTY,  COLEMNT, XXXXXXX,
    BL_BRTG, BL_TOGG, BL_DOWN, BL_UP,   AG_SWAP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_RBT,  QK_BOOT
)

};

void process_osd_keys (uint16_t keycode, keyrecord_t *record, uint8_t os) {
    if (record->event.pressed) {
        register_code16(osd_keys[keycode - M_UNDO][os]);
    } else {
        unregister_code16(osd_keys[keycode - M_UNDO][os]);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    if (record->event.pressed) {
        uprintf("0x%04X,%u,%u,%u\n", keycode, record->event.key.row, record->event.key.col,
                get_highest_layer(layer_state));
    }
#endif

    switch (keycode) {
        case COLEMAK:   /* fall thru */
        case QWERTY:    /* fall thru */
        case HANDSDN:   /* fall thru */
        case COLEMNT:
            if (record->event.pressed) {
                uint16_t layer = keycode - COLEMAK;
                set_single_persistent_default_layer(layer);
                layer_move(layer);
            }
            return false;
        case DB_TOGG:   /* fall thru */
        case AG_NORM:   /* fall thru */
        case AG_SWAP:
            if (!record->event.pressed) {
                layer_off(_ADJST);      /* make ADJST key behaves like one-shot layer */
            }
            break;
        case M_UNDO:    /* fall thru */
        case M_CUT:     /* fall thru */
        case M_COPY:    /* fall thru */
        case M_PASTE:   /* fall thru */
        case M_SELAL:   /* fall thru */
        case M_ZMIN:    /* fall thru */
        case M_ZMOUT:
            switch (detected_host_os()) {
                case OS_LINUX:
                    process_osd_keys(keycode, record, 0);
                    break;
                case OS_IOS:        /* fall thru */
                case OS_MACOS:
                    process_osd_keys(keycode, record, 2);
                    break;
                case OS_WINDOWS:    /* fall thru */
                default:
                    process_osd_keys(keycode, record, 1);
            }
            return false;
    }
    return true;
}
