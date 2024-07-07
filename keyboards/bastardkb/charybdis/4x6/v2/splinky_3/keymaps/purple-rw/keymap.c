/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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
#include QMK_KEYBOARD_H
#include "os_detection.h"

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum charybdis_keymap_layers {
    LAYER_COLEMAK = 0,  // Colemak-DH
    LAYER_QWERTY,       // Qwerty
    LAYER_COLENIT,      // Colemanite
    LAYER_HANDSDN,      // Hands Down Neu 30
    LAYER_SEMIMAK,      // Semimak JQ
    LAYER_RAISE,        // Numbers & Symbols
    LAYER_SYMBOL,       // Symbols
    LAYER_LOWER,        // Navigation & Functions
    LAYER_KEYPAD,       // Keypad & Functions2
    LAYER_MODS,         // Modifiers & Multimedia
    LAYER_POINTER,      // Trackball
    LAYER_MACROS,       // Dynamic Macros
    LAYER_PLOVER,       // Plover
    LAYER_ADJUST        // Adjustment
};

enum charybdis_keymap_keycodes {
    COLEMAK = QK_USER,
    QWERTY,
    COLENIT,
    HANDSDN,
    SEMIMAK,
    MACROS,
    PLOVER,
    EXT_PLV,

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
    LAYER_COLEMAK,
    LAYER_QWERTY,
    LAYER_COLENIT,
    LAYER_HANDSDN,
    LAYER_SEMIMAK,
    LAYER_MACROS,
    LAYER_PLOVER
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

/** \brief Automatically enable sniping-mode on the pointer layer. */
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

/* Layer keys */
#define RAISE   QK_TRI_LAYER_LOWER
#define SYMBL   TT(LAYER_SYMBOL)
#define LOWER   QK_TRI_LAYER_UPPER
#define KEYPD   TT(LAYER_KEYPAD)
#define MODS    TT(LAYER_MODS)
#define MACRO   OSL(LAYER_MACROS)
#define PT_Z    LT(LAYER_POINTER, KC_Z)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)
#define PT_X    LT(LAYER_POINTER, KC_X)
#define PT_K    LT(LAYER_POINTER, KC_K)
#define PT_DOT  LT(LAYER_POINTER, KC_DOT)
#define ADJST   TG(LAYER_ADJUST)

/* One-shot modifier keys */
#define OS_LSFT OSM(MOD_LSFT)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_LALT OSM(MOD_LALT)
#define OS_LGUI OSM(MOD_LGUI)
#define OS_RSFT OSM(MOD_RSFT)
#define OS_RCTL OSM(MOD_RCTL)
#define OS_RALT OSM(MOD_RALT)
#define OS_RGUI OSM(MOD_RGUI)

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* HOLD in alpha layer
 * ,-----------------------------------------.      ,-----------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |      |POINTR|      |      |      |      |      |      |      |      |      |POINTR|      |
 * `--------------------+------+------+------|      |------+------+---------------------------'
 *                      | Cmd  |Shift |LOWER |      |RAISE |      |
 *                      `------+------+------|      |------+------'
 *                             | Ctrl | Alt  |      |      |
 *                             `-------------'      `------'
 */

/* Colemak DH
 * ,-----------------------------------------.      ,-----------------------------------------.
 * |  \   |  9   |  5   |  3   |  1   |  7   |      |  6   |  0   |  2   |  4   |  8   |  =   |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * | Tab  |  Q   |  W   |  F   |  P   |  B   |      |  J   |  L   |  U   |  Y   |  ;   |  -   |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * | Esc  |  A   |  R   |  S   |  T   |  G   |      |  M   |  N   |  E   |  I   |  O   |  '   |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |CapsWd|  Z   |  X   |  C   |  D   |  V   |      |  K   |  H   |  ,   |  .   |  /   |Enter |
 * `--------------------+------+------+------|      |------+------+---------------------------'
 *                      |      |      |      |      |      |Space |
 *                      `------+------+------|      |------+------'
 *                             |      |      |      |BkSpc |
 *                             `-------------'      `------'
 */
[LAYER_COLEMAK] = LAYOUT(
    KC_BSLS, KC_9,    KC_5,    KC_3,    KC_1,    KC_7,             KC_6,    KC_0,    KC_2,    KC_4,    KC_8,    KC_EQL,
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,             KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_MINS,
    KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_G,             KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
    CW_TOGG, PT_Z,    KC_X,    KC_C,    KC_D,    KC_V,             KC_K,    KC_H,    KC_COMM, KC_DOT,  PT_SLSH, KC_ENT,
                               KC_LGUI, KC_LSFT, LOWER,            RAISE,   KC_SPC,
                                        KC_LCTL, KC_LALT,          KC_BSPC
//                               KC_LCTL, LOWER,   KC_LSFT,          KC_SPC,  RAISE,
//                                        KC_LALT, KC_LGUI,          KC_BSPC
),

/* Qwerty
 * ,-----------------------------------------.      ,-----------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |      |  Q   |  W   |  E   |  R   |  T   |      |  Y   |  U   |  I   |  O   |  P   |      |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |      |  A   |  S   |  D   |  F   |  G   |      |  H   |  J   |  K   |  L   |  ;   |      |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |      |  Z   |  X   |  C   |  V   |  B   |      |  N   |  M   |  ,   |  .   |  /   |      |
 * `--------------------+------+------+------|      |------+------+---------------------------'
 *                      |      |      |      |      |      |      |
 *                      `------+------+------|      |------+------'
 *                             |      |      |      |      |
 *                             `-------------'      `------'
 */
[LAYER_QWERTY] = LAYOUT(
    _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
    _______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    _______,
    _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, _______,
    _______, PT_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_N,    KC_M,    KC_COMM, KC_DOT,  PT_SLSH, _______,
                               _______, _______, _______,          _______, _______,
                                        _______, _______,          _______
),

/* Colemanite
 * ,-----------------------------------------.      ,-----------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |      |  B   |  L   |  W   |  M   |  Q   |      |  J   |  F   |  O   |  U   |  ;   |      |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |      |  N   |  R   |  S   |  T   |  G   |      |  Y   |  H   |  E   |  I   |  A   |      |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |      |  Z   |  X   |  C   |  D   |  V   |      |  K   |  P   |  /   |  ,   |  .   |      |
 * `--------------------+------+------+------|      |------+------+---------------------------'
 *                      |      |      |      |      |      |      |
 *                      `------+------+------|      |------+------'
 *                             |      |      |      |      |
 *                             `-------------'      `------'
 */
[LAYER_COLENIT] = LAYOUT(
    _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
    _______, KC_B,    KC_L,    KC_W,    KC_M,    KC_Q,             KC_J,    KC_F,    KC_O,    KC_U,    KC_SCLN, _______,
    _______, KC_N,    KC_R,    KC_S,    KC_T,    KC_G,             KC_Y,    KC_H,    KC_E,    KC_I,    KC_A,    _______,
    _______, PT_Z,    KC_X,    KC_C,    KC_D,    KC_V,             KC_K,    KC_P,    KC_SLSH, KC_COMM, PT_DOT,  _______,
                               _______, _______, _______,          _______, _______,
                                        _______, _______,          _______
),

/* Hands Down Neu 30
 * ,-----------------------------------------.      ,-----------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |      |  W   |  F   |  M   |  P   |  V   |      |  /   |  .   |  Q   |  J   |  Z   |      |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |      |  R   |  S   |  N   |  T   |  G   |      |  ,   |  A   |  E   |  I   |  H   |      |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |      |  X   |  C   |  L   |  D   |  B   |      |  ;   |  U   |  O   |  Y   |  K   |      |
 * `--------------------+------+------+------|      |------+------+---------------------------'
 *                      |      |      |      |      |      |      |
 *                      `------+------+------|      |------+------'
 *                             |      |      |      |      |
 *                             `-------------'      `------'
 */
[LAYER_HANDSDN] = LAYOUT(
    _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
    _______, KC_W,    KC_F,    KC_M,    KC_P,    KC_V,             KC_SLSH, KC_DOT,  KC_Q,    KC_J,    KC_Z,    _______,
    _______, KC_R,    KC_S,    KC_N,    KC_T,    KC_G,             KC_COMM, KC_A,    KC_E,    KC_I,    KC_H,    _______,
    _______, PT_X,    KC_C,    KC_L,    KC_D,    KC_B,             KC_SCLN, KC_U,    KC_O,    KC_Y,    PT_K,    _______,
                               _______, _______, _______,          _______, _______,
                                        _______, _______,          _______
),

/* Semimak JQ
 * ,-----------------------------------------.      ,-----------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |      |  F   |  L   |  H   |  V   |  Z   |      |  ;   |  W   |  U   |  O   |  Y   |      |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |      |  S   |  R   |  N   |  T   |  K   |      |  C   |  D   |  E   |  A   |  I   |      |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |      |  X   |  J   |  B   |  M   |  Q   |      |  P   |  G   |  ,   |  .   |  /   |      |
 * `--------------------+------+------+------|      |------+------+---------------------------'
 *                      |      |      |      |      |      |      |
 *                      `------+------+------|      |------+------'
 *                             |      |      |      |      |
 *                             `-------------'      `------'
 */
[LAYER_SEMIMAK] = LAYOUT(
    _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
    _______, KC_F,    KC_L,    KC_H,    KC_V,    KC_Z,             KC_SCLN, KC_W,    KC_U,    KC_O,    KC_Y,    _______,
    _______, KC_S,    KC_R,    KC_N,    KC_T,    KC_K,             KC_C,    KC_D,    KC_E,    KC_A,    KC_I,    _______,
    _______, PT_X,    KC_J,    KC_B,    KC_M,    KC_Q,             KC_P,    KC_G,    KC_COMM, KC_DOT,  PT_SLSH, _______,
                               _______, _______, _______,          _______, _______,
                                        _______, _______,          _______
),

/* Numbers & Symbols (RAISE)
 * ,-----------------------------------------.      ,-----------------------------------------.
 * |      |nonUS#|  /   |  ,   |  <   |      |      |      |  >   |  ;   |  ?   |nonUS\|      |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |  ^   |  9   |  5   |  3   |  1   |  7   |      |  6   |  0   |  2   |  4   |  8   |  `   |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |  +   |  $   |  =   |  -   |  (   |  .   |      |  :   |  )   |  _   |  "   |  '   |  !   |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |  %   |  @   |  |   |  &   |  {   |  [   |      |  ]   |  }   |  *   |  #   |  \   |  ~   |
 * `--------------------+------+------+------|      |------+------+---------------------------'
 *                      |      |SYMBL | MODS |      | **** |      |
 *                      `------+------+------|      |------+------'
 *                             |      |      |      |      |
 *                             `-------------'      `------'
 */
[LAYER_RAISE] = LAYOUT(
    _______, KC_NUHS, KC_SLSH, KC_COMM, KC_LABK, _______,          _______, KC_RABK, KC_SCLN, KC_QUES, KC_NUBS, _______,
    KC_CIRC, KC_9,    KC_5,    KC_3,    KC_1,    KC_7,             KC_6,    KC_0,    KC_2,    KC_4,    KC_8,    KC_GRV,
    KC_PLUS, KC_DLR,  KC_EQL,  KC_MINS, KC_LPRN, KC_DOT,           KC_COLN, KC_RPRN, KC_UNDS, KC_DQT,  KC_QUOT, KC_EXLM,
    KC_PERC, KC_AT,   KC_PIPE, KC_AMPR, KC_LCBR, KC_LBRC,          KC_RBRC, KC_RCBR, KC_ASTR, KC_HASH, KC_BSLS, KC_TILD,
                               _______, SYMBL,   _______,          _______, _______,
                                        _______, _______,          _______
//                               _______, MODS,    SYMBL,            _______, _______,
//                                        _______, _______,          _______
),

/* Symbols
 * ,-----------------------------------------.      ,-----------------------------------------.
 * |      |nonUS#|  /   |  ,   |  <   |      |      |      |  >   |  ;   |  ?   |nonUS\|      |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |  ^   |  ^   |  %   |  +   |  [   |  ,   |      |  ;   |  ]   |  !   |  ~   |  `   |  `   |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |  +   |  $   |  =   |  -   |  (   |  <   |      |  >   |  )   |  _   |  "   |  '   |  !   |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |  %   |  @   |  |   |  &   |  {   |  /   |      |  ?   |  }   |  *   |nonUS#|nonUS\|  ~   |
 * `--------------------+------+------+------|      |------+------+---------------------------'
 *                      |      | **** |      |      | **** |      |
 *                      `------+------+------|      |------+------'
 *                             |      |      |      |      |
 *                             `-------------'      `------'
 */
[LAYER_SYMBOL] = LAYOUT(
    _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
    _______, KC_CIRC, KC_PERC, KC_PLUS, KC_LBRC, KC_COMM,          KC_SCLN, KC_RBRC, KC_EXLM, KC_TILD, KC_GRV,  _______,
    _______, _______, _______, _______, _______, KC_LABK,          KC_RABK, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, KC_SLSH,          KC_QUES, _______, _______, KC_NUHS, KC_NUBS, _______,
                               _______, _______, _______,          _______, _______,
                                        _______, _______,          _______
),

/* Navigation & Functions (LOWER)
 * ,-----------------------------------------.      ,-----------------------------------------.
 * | F17  | F13  | F14  | F15  | F16  |      |      |      | Vol- | Mute | Vol+ |Eject | F21  |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * | F18  |  F1  |  F2  |  F3  |  F4  |Pause |      | Ins  | PgUp |  Up  | PgDn | Menu | F22  |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * | F19  |  F5  |  F6  |  F7  |  F8  |PrScn |      | Home | Left | Down |Right | End  | F23  |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * | F20  |  F9  | F10  | F11  | F12  |ScrLk |      | Tab  |BkSpc |Enter | Del  | Alt  | F24  |
 * `--------------------+------+------+------|      |------+------+---------------------------'
 *                      |      | Alt  | **** |      | MODS |Shift |
 *                      `------+------+------|      |------+------'
 *                             |      |KEYPAD|      | Cmd  |
 *                             `-------------'      `------'
 */
[LAYER_LOWER] = LAYOUT(
    KC_F17,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  _______,          _______, KC_VOLD, KC_MUTE, KC_VOLU, KC_EJCT, KC_F21,
    KC_F18,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_PAUS,          KC_INS,  KC_PGUP, KC_UP,   KC_PGDN, KC_APP,  KC_F22,
    KC_F19,  KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_PSCR,          KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  KC_F23,
    KC_F20,  KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_SCRL,          KC_TAB,  KC_BSPC, KC_ENT,  KC_DEL,  KC_LALT, KC_F24,
                               _______, KC_LALT, _______,          _______, KC_LSFT,
                                        _______, KEYPD,            KC_LGUI
//                               _______, _______, KC_LALT,          KC_LSFT, MODS,
//                                        KEYPD,   _______,          KC_LGUI
),

/* Keypad & Functions2
 * ,-----------------------------------------.      ,-----------------------------------------.
 * | F17  | F13  | F14  | F15  | F16  |      |      |NumLck|      |      |      |      |      |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * | F18  | F13  | F14  | F15  | F16  |Pause |      |  *   |  7   |  8   |  9   |  /   |NumLck|
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * | F19  | F17  | F18  | F19  | F20  |PrScn |      |  -   |  4   |  5   |  6   |  +   |  =   |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * | F20  | F21  | F22  | F23  | F24  |ScrLk |      | Tab  |  1   |  2   |  3   |  .   | Ent  |
 * `--------------------+------+------+------|      |------+------+---------------------------'
 *                      |      |      | **** |      |Space |  0   |
 *                      `------+------+------|      |------+------'
 *                             |      | **** |      |BkSpc |
 *                             `-------------'      `------'
 */
[LAYER_KEYPAD] = LAYOUT(
    _______, _______, _______, _______, _______, _______,          KC_NUM,  _______, _______, _______, _______, _______,
    _______, KC_F13,  KC_F14,  KC_F15,  KC_F16,  _______,          KC_PAST, KC_P7,   KC_P8,   KC_P9,   KC_PSLS, KC_NUM,
    _______, KC_F17,  KC_F18,  KC_F19,  KC_F20,  _______,          KC_PMNS, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, KC_PEQL,
    _______, KC_F21,  KC_F22,  KC_F23,  KC_F24,  _______,          KC_TAB,  KC_P1,   KC_P2,   KC_P3,   KC_PDOT, KC_PENT,
                               _______, _______, _______,          KC_SPC,  KC_P0,
                                        _______, _______,          KC_BSPC
//                               _______, _______, _______,          KC_P0,   KC_SPC,
//                                        _______, _______,          KC_BSPC
),

/* Modifiers & Multimedia
 * ,-----------------------------------------.      ,-----------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |ADJUST| Vol- | Mute | Vol+ |Eject |      |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |MACROS| Ctrl | Alt  | Cmd  |Shift |CapsLk|      |CapsWd|Shift | Cmd  | Alt  | Ctrl |MACROS|
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |      | Undo | Cut  | Copy |Paste |SelAll|      | Prev |Rewind| Play | FFwd | Next |      |
 * `--------------------+------+------+------|      |------+------+---------------------------'
 *                      |      |      | **** |      | **** |      |
 *                      `------+------+------|      |------+------'
 *                             |      |      |      |      |
 *                             `-------------'      `------'
 */
 [LAYER_MODS] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          ADJST,   KC_VOLD, KC_MUTE, KC_VOLU, KC_EJCT, XXXXXXX,
    MACRO,   OS_LCTL, OS_LALT, OS_LGUI, OS_LSFT, KC_CAPS,          CW_TOGG, OS_RSFT, OS_RGUI, OS_RALT, OS_RCTL, MACRO,
    XXXXXXX, M_UNDO,  M_CUT,   M_COPY,  M_PASTE, M_SELAL,          KC_MRWD, KC_MPRV, KC_MPLY, KC_MNXT, KC_MFFD, XXXXXXX,
                               XXXXXXX, XXXXXXX, _______,          _______, XXXXXXX,
                                        XXXXXXX, XXXXXXX,          XXXXXXX
//                               XXXXXXX, _______, XXXXXXX,          XXXXXXX, _______,
//                                        XXXXXXX, XXXXXXX,          XXXXXXX
),

/* Mouse (POINTER)
 * ,-----------------------------------------.      ,-----------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |      |      |      |      | DPI  |S_DPI+|      |S_DPI+| DPI  |      |      |      |      |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |      | Ctrl | Alt  | Cmd  |Shift |      |      |      |Shift | Cmd  | Alt  | Ctrl |      |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |      |      |DrgScr| Snip | Clr  | Boot |      | Boot | Clr  | Snip |DrgScr|      |      |
 * `--------------------+------+------+------|      |------+------+---------------------------'
 *                      | Btn2 | Btn1 | Btn2 |      | Btn2 | Btn1 |
 *                      `------+------+------|      |------+------'
 *                             |      | Btn3 |      | Btn3 |
 *                             `-------------'      `------'
 */
[LAYER_POINTER] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DPI_MOD, S_D_MOD,          S_D_MOD, DPI_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, KC_LCTL, KC_LALT, KC_LCMD, KC_LSFT, XXXXXXX,          XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, XXXXXXX,
    XXXXXXX, _______, DRGSCRL, SNIPING, EE_CLR,  QK_BOOT,          QK_BOOT, EE_CLR,  SNIPING, DRGSCRL, _______, XXXXXXX,
                               KC_BTN2, KC_BTN1, KC_BTN2,          KC_BTN2, KC_BTN1,
                                        XXXXXXX, KC_BTN3,          KC_BTN3
//                               XXXXXXX, KC_BTN2, KC_BTN1,          KC_BTN1, KC_BTN2,
//                                        XXXXXXX, KC_BTN3,          KC_BTN3
),

/* Dynamic Macros
 * ,-----------------------------------------.      ,-----------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |      |      |      |DMrec2|DMrec1|      |      |      |DMrec1|DMrec2|      |      |      |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |      |      |      |DMply2|DMply1|      |      |      |DMply1|DMply2|      |      |      |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * `--------------------+------+------+------|      |------+------+---------------------------'
 *                      |      |DMstop|      |      |      |DMstop|
 *                      `------+------+------|      |------+------'
 *                             |      |      |      |      |
 *                             `-------------'      `------'
 */
 [LAYER_MACROS] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, DM_REC2, DM_REC1, XXXXXXX,          XXXXXXX, DM_REC1, DM_REC2, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, DM_PLY2, DM_PLY1, XXXXXXX,          XXXXXXX, DM_PLY1, DM_PLY2, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                               XXXXXXX, DM_RSTP, XXXXXXX,          XXXXXXX, DM_RSTP,
                                        XXXXXXX, XXXXXXX,          XXXXXXX
//                               XXXXXXX, XXXXXXX, DM_RSTP,        DM_RSTP, XXXXXXX,
//                                        XXXXXXX, XXXXXXX,          XXXXXXX
),

/* Plover
 * ,-----------------------------------------.      ,-----------------------------------------.
 * |      | 1 #  | 1 #  | 1 #  | 1 #  | 1 #  |      | 1 #  | 1 #  | 1 #  | 1 #  | 1 #  | 1 #  |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |      | q S- | w T- | s P- | r H- | t *  |      | y *  | u -F | i -P | o -L | p -T | [ -D |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |      | a S- | s K- | d W- | f R- | g *  |      | h *  | j -R | k -B | l -G | ; -S | ' -Z |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * | Exit |      |      |      |      |      |      |      |      |      |      |      |      |
 * `--------------------+------+------+------|      |------+------+---------------------------'
 *                      | 1 #  | c A- | v O- |      | n -E | m -U |
 *                      `------+------+------|      |------+------'
 *                             |      |      |      |      |
 *                             `-------------'      `------'
 */
 [LAYER_PLOVER] = LAYOUT(
    XXXXXXX, KC_1,    KC_1,    KC_1,    KC_1,    KC_1,             KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,
    XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
    XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    EXT_PLV, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                               KC_1,    KC_C,    KC_V,             KC_N,    KC_M,
                                        XXXXXXX, XXXXXXX,          XXXXXXX
),

/* Adjustment
 * ,-----------------------------------------.      ,-----------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |      |Brght+| Sat+ | Hue+ |RGBmod| BL+  |      |      |HndsDn|Semimk|      |      |      |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * | Exit |Brght-| Sat- | Hue- | RGB  | BL-  |      |AGnorm|Colemk|Qwerty|Colnit|      |Plover|
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |      |      |      |      |  BL  |BLbrth|      |AGswap|      |      |      |Reset |BootL |
 * `--------------------+------+------+------|      |------+------+---------------------------'
 *                      |      | Exit |      |      |      | Exit |
 *                      `------+------+------|      |------+------'
 *                             |      |      |      |      |
 *                             `-------------'      `------'
 */
 [LAYER_ADJUST] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, RGB_VAI, RGB_SAI, RGB_HUI, RGB_MOD, BL_UP,            XXXXXXX, HANDSDN, SEMIMAK, XXXXXXX, XXXXXXX, XXXXXXX,
    ADJST,   RGB_VAD, RGB_SAD, RGB_HUD, RGB_TOG, BL_DOWN,          AG_NORM, COLEMAK, QWERTY,  COLENIT, XXXXXXX, PLOVER,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, BL_TOGG, BL_BRTG,          AG_SWAP, XXXXXXX, XXXXXXX, XXXXXXX, QK_RBT,  QK_BOOT,
                               XXXXXXX, ADJST,   XXXXXXX,          XXXXXXX, ADJST,
                                        XXXXXXX, XXXXXXX,          XXXXXXX
//                               XXXXXXX, XXXXXXX, ADJST,          ADJST,   XXXXXXX,
//                                        XXXXXXX, XXXXXXX,          XXXXXXX
),

};
// clang-format on

void keyboard_post_init_user(void) {
    set_tri_layer_layers(LAYER_RAISE, LAYER_LOWER, LAYER_MODS);
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
        case PLOVER:
            if (record->event.pressed) {
                #ifdef AUDIO_ENABLE
                    stop_all_notes();
                    PLAY_SONG(plover_song);
                #endif
                layer_move(LAYER_PLOVER);
                if (!eeconfig_is_enabled()) {
                    eeconfig_init();
                }
                keymap_config.raw = eeconfig_read_keymap();
                keymap_config.nkro = 1;
                eeconfig_update_keymap(keymap_config.raw);
            }
            return false;
        case EXT_PLV:
            if (record->event.pressed) {
                #ifdef AUDIO_ENABLE
                    PLAY_SONG(plover_gb_song);
                #endif
                layer_move(get_highest_layer(default_layer_state));
            }
            return false;
        case DB_TOGG:   /* fall thru */
        case AG_NORM:   /* fall thru */
        case AG_SWAP:   /* fall thru */
        case AU_ON:     /* fall thru */
        case AU_OFF:
            if (!record->event.pressed) {
                layer_off(LAYER_ADJUST);        /* make ADJST key behaves like one-shot layer */
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

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif // RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#        endif // RGB_MATRIX_ENABLE
    }
}
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif
