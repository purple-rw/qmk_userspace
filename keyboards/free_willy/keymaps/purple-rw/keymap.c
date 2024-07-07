/* Copyright 2022-2023 Rhys Wong
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
#ifdef CONSOLE_enable
#    include "print.h"
#endif

enum free_willy_layers {
    _COLEMAK,	// Colemak-DH
    _QWERTY,    // Qwerty
    _COLENIT,   // Colemanite
    _HANDSDN,   // Hands Down Neu 30
    _SEMIMAK,   // Semimak JQ
    _RAISE,     // Numbers & Symbols
    _SYMBL,     // Symbols
    _LOWER,     // Navigation & Functions
    _KEYPD,     // Keypad & Functions2
    _MODS,      // Modifiers, Multimedia & Macros
    _MOUSE,     // Mouse
    _MACRO,     // Dynamic Macros
    _ADJST      // Adjustment
};

enum free_willy_keycodes {
    COLEMAK = QK_USER,
    QWERTY,
    COLENIT,
    HANDSDN,
    SEMIMAK,

    M_UNDO,
    M_CUT,
    M_COPY,
    M_PASTE,
    M_SELAL,    // select all
    M_ZMIN,     // zoom in
    M_ZMOUT     // zoom out
};

/* Converting keycode to layer enum */
const uint16_t PROGMEM keycode2layer[] = {
    _COLEMAK,
    _QWERTY,
    _COLENIT,
    _HANDSDN,
    _SEMIMAK,
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

/* Try Layers */
#define TRI_LAYER_LOWER_LAYER  _RAISE
#define TRI_LAYER_RAISE_LAYER  _LOWER
#define TRI_LAYER_ADJUST_LAYER _MODS

/* Thumb keys */
#define RAISE   QK_TRI_LAYER_LOWER
#define SYMBL   TT(_SYMBL)
#define LOWER   QK_TRI_LAYER_UPPER
#define KEYPD   TT(_KEYPD)

/* Layer keys */
#define MOUSE   TG(_MOUSE)
#define ADJST   TG(_ADJST)
#define MACRO   OSL(_MACRO)

/* One-shot modifier keys */
#define OS_LSFT OSM(MOD_LSFT)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_LALT OSM(MOD_LALT)
#define OS_LGUI OSM(MOD_LGUI)
#define OS_RSFT OSM(MOD_RSFT)
#define OS_RCTL OSM(MOD_RCTL)
#define OS_RALT OSM(MOD_RALT)
#define OS_RGUI OSM(MOD_RGUI)

/* Mod-tap keys */
#define Cx_ESC  LCTL_T(KC_ESC)
#define Ax_ENT  LALT_T(KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* HOLD in alpha layer
 * ,---------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |
 * `-------------+------+------+------+------+------+------+-------------'
 *               | Ctrl |LOWER |Shift |      |RAISE | Alt  |
 *               `-----------------------------------------'
 */

/* Colemak
 * ,---------------------------------------------------------------------.
 * |  Q   |  W   |  F   |  P   |  B   |  J   |  L   |  U   |  Y   |  ;   |
 * |------+------+------+------+------+------+------+------+------+------|
 * |  A   |  R   |  S   |  T   |  G   |  M   |  N   |  E   |  I   |  O   |
 * |------+------+------+------+------+------+------+------+------+------|
 * |  Z   |  X   |  C   |  D   |  V   |  K   |  H   |  ,   |  .   |  /   |
 * `-------------+------+------+------+------+------+------+-------------'
 *               | Esc  |LOWER |Shift |Space |RAISE |Enter |
 *               `-----------------------------------------'
 */
[_COLEMAK] = LAYOUT(
    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,
    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,
    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH,
                      Cx_ESC,  LOWER,   KC_LSFT, KC_SPC,  RAISE,   Ax_ENT
),

/* Qwerty
 * ,---------------------------------------------------------------------.
 * |  Q   |  W   |  E   |  R   |  T   |  Y   |  U   |  I   |  O   |  P   |
 * |------+------+------+------+------+------+------+------+------+------|
 * |  A   |  S   |  D   |  F   |  G   |  H   |  J   |  K   |  L   |  ;   |
 * |------+------+------+------+------+------+------+------+------+------|
 * |  Z   |  X   |  C   |  V   |  B   |  N   |  M   |  ,   |  .   |  /   |
 * `-------------+------+------+------+------+------+------+-------------'
 *               |      |      |      |      |      |      |
 *               `-----------------------------------------'
 */
[_QWERTY] = LAYOUT(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                      _______, _______, _______, _______, _______, _______
),

/* Colemanite
 * ,---------------------------------------------------------------------.
 * |  B   |  L   |  W   |  M   |  Q   |  J   |  F   |  O   |  U   |  ;   |
 * |------+------+------+------+------+------+------+------+------+------|
 * |  N   |  R   |  S   |  T   |  G   |  Y   |  H   |  E   |  I   |  A   |
 * |------+------+------+------+------+------+------+------+------+------|
 * |  Z   |  X   |  C   |  D   |  V   |  K   |  P   |  /   |  .   |  ,   |
 * `-------------+------+------+------+------+------+------+-------------'
 *               | Esc  |LOWER |Shift |Space |RAISE |Enter |
 *               `-----------------------------------------'
 */
[_COLENIT] = LAYOUT(
    KC_B,    KC_L,    KC_W,    KC_M,    KC_Q,    KC_J,    KC_F,    KC_O,    KC_U,    KC_SCLN,
    KC_N,    KC_R,    KC_S,    KC_T,    KC_G,    KC_Y,    KC_H,    KC_E,    KC_I,    KC_A,
    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_P,    KC_SLSH, KC_DOT,  KC_COMM,
                      _______, _______, _______, _______, _______, _______
),

/* Hands Down Neu 30
 * ,---------------------------------------------------------------------.
 * |  W   |  F   |  M   |  P   |  V   |  /   |  .   |  Q   |  J   |  Z   |
 * |------+------+------+------+------+------+------+------+------+------|
 * |  R   |  S   |  N   |  T   |  G   |  ,   |  A   |  E   |  I   |  H   |
 * |------+------+------+------+------+------+------+------+------+------|
 * |  X   |  C   |  L   |  D   |  B   |  ;   |  U   |  O   |  Y   |  K   |
 * `-------------+------+------+------+------+------+------+-------------'
 *               |      |      |      |      |      |      |
 *               `-----------------------------------------'
 */
[_HANDSDN] = LAYOUT(
    KC_W,    KC_F,    KC_M,    KC_P,    KC_V,    KC_SLSH, KC_DOT,  KC_Q,    KC_J,    KC_Z,
    KC_R,    KC_S,    KC_N,    KC_T,    KC_G,    KC_COMM, KC_A,    KC_E,    KC_I,    KC_H,
    KC_X,    KC_C,    KC_L,    KC_D,    KC_B,    KC_SCLN, KC_U,    KC_O,    KC_Y,    KC_K,
                      _______, _______, _______, _______, _______, _______
),

/* Semimak JQ
 * ,---------------------------------------------------------------------.
 * |  F   |  L   |  H   |  V   |  Z   |  ;   |  W   |  U   |  O   |  Y   |
 * |------+------+------+------+------+------+------+------+------+------|
 * |  S   |  R   |  N   |  T   |  K   |  C   |  D   |  E   |  A   |  I   |
 * |------+------+------+------+------+------+------+------+------+------|
 * |  X   |  J   |  B   |  M   |  Q   |  P   |  G   |  ,   |  .   |  /   |
 * `-------------+------+------+------+------+------+------+-------------'
 *               |      |      |      |      |      |      |
 *               `-----------------------------------------'
 */
[_SEMIMAK] = LAYOUT(
    KC_F,    KC_L,    KC_H,    KC_V,    KC_Z,    KC_SCLN, KC_W,    KC_U,    KC_O,    KC_Y,
    KC_S,    KC_R,    KC_N,    KC_T,    KC_K,    KC_C,    KC_D,    KC_E,    KC_A,    KC_I,
    KC_X,    KC_J,    KC_B,    KC_M,    KC_Q,    KC_P,    KC_G,    KC_COMM, KC_DOT,  KC_SLSH,
                      _______, _______, _______, _______, _______, _______
),

/* Numberd & Symbols
 * ,---------------------------------------------------------------------.
 * |  9   |  5   |  3   |  1   |  7   |  6   |  0   |  2   |  4   |  8   |
 * |------+------+------+------+------+------+------+------+------+------|
 * |  $   |  =   |  -   |  (   |  .   |  :   |  )   |  _   |  "   |  '   |
 * |------+------+------+------+------+------+------+------+------+------|
 * |  @   |  |   |  &   |  {   |  [   |  ]   |  }   |  *   |  #   |  \   |
 * `-------------+------+------+------+------+------+------+-------------'
 *               |      |(MODS)|SYMBL |      | #### |      |
 *               `-----------------------------------------'
 */
 [_RAISE] = LAYOUT(
    KC_9,    KC_5,    KC_3,    KC_1,    KC_7,    KC_6,    KC_0,    KC_2,    KC_4,    KC_8,
    KC_DLR,  KC_EQL,  KC_MINS, KC_LPRN, KC_DOT,  KC_COLN, KC_RPRN, KC_UNDS, KC_DQT,  KC_QUOT,
    KC_AT,   KC_PIPE, KC_AMPR, KC_LCBR, KC_LBRC, KC_RBRC, KC_RCBR, KC_ASTR, KC_HASH, KC_BSLS,
                      _______, _______, SYMBL,   XXXXXXX, _______, _______
),

/* Symbols
 * ,---------------------------------------------------------------------.
 * |  ^   |  %   |  +   |  [   |  ,   |  ;   |  ]   |  !   |  ~   |  `   |
 * |------+------+------+------+------+------+------+------+------+------|
 * |  $   |  =   |  -   |  (   |  <   |  >   |  )   |  _   |  "   |  '   |
 * |------+------+------+------+------+------+------+------+------+------|
 * |  @   |  |   |  &   |  {   |  /   |  ?   |  }   |  *   |nonUS#|nonUS\|
 * `-------------+------+------+------+------+------+------+-------------'
 *               |      | Esc  | Del  | **** |      |      |
 *               `-----------------------------------------'
 */
 [_SYMBL] = LAYOUT(
    KC_CIRC, KC_PERC, KC_PLUS, KC_LBRC, KC_COMM, KC_SCLN, KC_RBRC, KC_EXLM, KC_TILD, KC_GRV,
    _______, _______, _______, _______, KC_LABK, KC_RABK, _______, _______, _______, _______,
    _______, _______, _______, _______, KC_SLSH, KC_QUES, _______, _______, KC_NUHS, KC_NUBS,
                      _______, XXXXXXX, _______, XXXXXXX, _______, _______
),

/* Navigation & Functions
 * ,---------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |Pause | Ins  | PgUp |  Up  | PgDn | Menu |
 * |------+------+------+------+------+------+------+------+------+------|
 * |  F5  |  F6  |  F7  |  F8  |PrScn | Home | Left | Down |Right | End  |
 * |------+------+------+------+------+------+------+------+------+------|
 * |  F9  | F10  | F11  | F12  |ScrLk | Tab  |BkSpc |Enter | Del  | Esc  |
 * `-------------+------+------+------+------+------+------+-------------'
 *               |      | **** |      |KEYPD |(MODS)|      |
 *               `-----------------------------------------'
 */
 [_LOWER] = LAYOUT(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_PAUS, KC_INS,  KC_PGUP, KC_UP,   KC_PGDN, KC_APP,
    KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_PSCR, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,
    KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_SCRL, KC_TAB,  KC_BSPC, KC_ENT,  KC_DEL,  KC_ESC,
                      _______, _______, XXXXXXX, KEYPD,   _______, _______
),

/* Keypad & Functions2
 * ,---------------------------------------------------------------------.
 * | F13  | F14  | F15  | F16  |NumLck|  *   |  7   |  8   |  9   |  /   |
 * |------+------+------+------+------+------+------+------+------+------|
 * | F17  | F18  | F19  | F20  |  =   |  -   |  4   |  5   |  6   |  +   |
 * |------+------+------+------+------+------+------+------+------+------|
 * | F21  | F22  | F23  | F24  | Ent  |  0   |  1   |  2   |  3   |  .   |
 * `-------------+------+------+------+------+------+------+-------------'
 *               |      | **** |      | **** |      |      |
 *               `-----------------------------------------'
 */
[_KEYPD] = LAYOUT(
    KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_NUM,  KC_PAST, KC_P7,   KC_P8,   KC_P9,   KC_PSLS,
    KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_PEQL, KC_PMNS, KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
    KC_F21,  KC_F22,  KC_F23,  KC_F24,  KC_PENT, KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_PDOT,
                      _______, _______, XXXXXXX, _______, XXXXXXX, _______
),

/* Modifiers, Multimedia & Macros
 * ,---------------------------------------------------------------------.
 * | Esc  |      |Zoom- |Zoom+ |MOUSE |ADJST | Vol- | Mute | Vol+ |Eject |
 * |------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  | Cmd  |Shift |CapsLk|CapsWd|Shift | Cmd  | Alt  | Ctrl |
 * |------+------+------+------+------+------+------+------+------+------|
 * | Undo | Cut  | Copy |Paste |SelAll| Prev |Rewind| Play | FFwd | Next |
 * `-------------+------+------+------+------+------+------+-------------'
 *               |      | **** |      |      | **** |MACRO |
 *               `-----------------------------------------'
 */
[_MODS] = LAYOUT(
    KC_ESC,  XXXXXXX, M_ZMOUT, M_ZMIN,  MOUSE,   ADJST,   KC_VOLD, KC_MUTE, KC_VOLU, KC_EJCT,
    OS_LCTL, OS_LALT, OS_LGUI, OS_LSFT, KC_CAPS, CW_TOGG, OS_RSFT, OS_RGUI, OS_RALT, OS_RCTL,
    M_UNDO,  M_CUT,   M_COPY,  M_PASTE, M_SELAL, KC_MRWD, KC_MPRV, KC_MPLY, KC_MNXT, KC_MFFD,
                      _______, _______, XXXXXXX, XXXXXXX, _______, MACRO
),

/* Mouse
 * ,---------------------------------------------------------------------.
 * | Acc2 |WhlUp |  Up  |WhlDn | Acc1 | Acc1 |WhlUp |  Up  |WhlDn | Acc2 |
 * |------+------+------+------+------+------+------+------+------+------|
 * |WhlLt | Left | Down |Right |WhlRt |WhlLt | Left | Down |Right |WhlRt |
 * |------+------+------+------+------+------+------+------+------+------|
 * | Btn4 | Btn2 | Btn3 | Btn1 | Acc0 | Acc0 | Btn1 | Btn3 | Btn2 | Btn4 |
 * `-------------+------+------+------+------+------+------+-------------'
 *               |      | Btn2 | Btn1 | Btn1 | Btn2 |      |
 *               `-----------------------------------------'
 */
[_MOUSE] = LAYOUT(
    KC_ACL2, KC_WH_U, KC_MS_U, KC_WH_D, MOUSE,   MOUSE,   KC_WH_U, KC_MS_U, KC_WH_D, KC_ACL2,
    KC_WH_L, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_R, KC_WH_L, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_R,
    KC_ACL1, KC_BTN2, KC_BTN3, KC_BTN1, KC_ACL0, KC_ACL0, KC_BTN1, KC_BTN3, KC_BTN2, KC_ACL1,
                      XXXXXXX, KC_BTN2, KC_BTN1, KC_BTN1, KC_BTN2, XXXXXXX
),

/* Dynamic Macros
 * ,---------------------------------------------------------------------.
 * |      |      |      |      |      |      |DMrec1|DMrec2|      |      |
 * |------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |DMply1|DMply2|      |      |
 * |------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |
 * `-------------+------+------+------+------+------+------+-------------'
 *               |      |      |      |DMstop|      |      |
 *               `-----------------------------------------'
 */
[_MACRO] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DM_REC1, DM_REC2, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DM_PLY1, DM_PLY2, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                      XXXXXXX, XXXXXXX, XXXXXXX, DM_RSTP, XXXXXXX, XXXXXXX
),

/* Adjust
 * ,---------------------------------------------------------------------.
 * |Brght+| Sat+ | Hue+ |RGBmod| BL+  |      |HndsDn|Semimk|      |Debug |
 * |------+------+------+------+------+------+------+------+------+------|
 * |Brght-| Sat- | Hue- | RGB  | BL-  |AGnorm|Colemk|Qwerty|Colnit|      |
 * |------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |  BL  |BLbrth|AGswap|      |      |Reset |BootL |
 * `-------------+------+------+------+------+------+------+-------------'
 *               |      |      | Exit | Exit |      |      |
 *               `-----------------------------------------'
 */
[_ADJST] = LAYOUT(
    RGB_VAI, RGB_SAI, RGB_HUI, RGB_MOD, BL_UP,   XXXXXXX, HANDSDN, SEMIMAK, XXXXXXX, DB_TOGG,
    RGB_VAD, RGB_SAD, RGB_HUD, RGB_TOG, BL_DOWN, AG_NORM, COLEMAK, QWERTY,  COLENIT, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, BL_TOGG, BL_BRTG, AG_SWAP, XXXXXXX, XXXXXXX, QK_RBT,  QK_BOOT,
                      XXXXXXX, XXXXXXX, ADJST,   ADJST,   XXXXXXX, XXXXXXX
)

};

void keyboard_post_init_user(void) {
    set_tri_layer_layers(_RAISE, _LOWER, _MODS);
}

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
        case COLENIT:   /* fall thru */
        case HANDSDN:   /* fall thru */
        case SEMIMAK:
            if (record->event.pressed) {
                uint16_t layer = keycode2layer[keycode - QK_USER];
                set_single_persistent_default_layer(layer);
                layer_move(layer);
            }
            return false;
        case DB_TOGG:   /* fall thru */
        case AG_NORM:   /* fall thru */
        case AG_SWAP:   /* fall thru */
        case AU_ON:     /* fall thru */
        case AU_OFF:
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
