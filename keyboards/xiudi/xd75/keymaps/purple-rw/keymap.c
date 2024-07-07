/* Copyright 2024 Rhys Wong
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

enum xd75_layers {
    _COLEMAK,   // Colemak-DH
    _QWERTY,    // Qwerty
    _FN,        // Functions for Qwerty
    _RAISE,     // Numbers & Symbols
    _SYMBL,     // Symbols
    _LOWER,     // Navigation & Functions
    _KEYPD,     // Keypad & Functions2
    _MODS,      // Modifiers, Multimedia & Adjustment
};

enum xd75_keycodes {
    M_UNDO = QK_USER,
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

/* Thumb keys */
#define RAISE   QK_TRI_LAYER_LOWER
#define SYMBL   TT(_SYMBL)
#define LOWER   QK_TRI_LAYER_UPPER
#define KEYPD   TT(_KEYPD)

/* Layer keys */
#define FN      TT(_FN)
#define QWERTY  TG(_QWERTY)

/* Mod-Tap keys */
#define ENTERS  RSFT_T(KC_ENT)

/* One-shot modifier keys */
#define OS_LSFT OSM(MOD_LSFT)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_LALT OSM(MOD_LALT)
#define OS_LGUI OSM(MOD_LGUI)
#define OS_RSFT OSM(MOD_RSFT)
#define OS_RCTL OSM(MOD_RCTL)
#define OS_RALT OSM(MOD_RALT)
#define OS_RGUI OSM(MOD_RGUI)

/* Macros */
#define M_UNDO  C(KC_Z)
#define M_CUT   C(KC_X)
#define M_COPY  C(KC_C)
#define M_PASTE C(KC_V)
#define M_SELAL C(KC_A)
#define M_ZMIN  A(KC_WH_D)
#define M_ZMOUT A(KC_WH_U)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Qwerty
     * .--------------------------------------------------------------------------------------------------------------------------------------.
     * |  esc   |   1    |   2    |   3    |   4    |   5    |   [    |   \    |   ]    |   6    |   7    |   8    |   9    |   0    |  bksp  |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |  tab   |   Q    |   W    |   E    |   R    |   T    |   -    |   `    |   =    |   Y    |   U    |   I    |   O    |   P    |  del   |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |  caps  |   A    |   S    |   D    |   F    |   G    |  home  | prscr  |  pgup  |   H    |   J    |   K    |   L    |   ;    |   '    |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * | LSHIFT |   Z    |   X    |   C    |   V    |   B    |  end   |   up   |  pgdn  |   N    |   M    |   ,    |   .    |   /    | enter  |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |   FN   | LCTRL  | LALT   | LGUI   | LOWER  | LSHIFT |  left  |  down  | right  | space  | RAISE  |  RGUI  |  RALT  | RCTRL  |  menu  |
     * '--------------------------------------------------------------------------------------------------------------------------------------'
     */
    [_COLEMAK] = LAYOUT_ortho_5x15(
        KC_ESC,  KC_9,    KC_5,    KC_3,    KC_1,    KC_7,    KC_LBRC, KC_BSLS, KC_RBRC, KC_6,    KC_0,    KC_2,    KC_4,    KC_8,    KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_MINS, KC_GRV,  KC_EQL,  KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_DEL,
        KC_CAPS, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_HOME, KC_PSCR, KC_PGUP, KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_END,  KC_UP,   KC_PGDN, KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, ENTERS,
        FN,      KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_LSFT, KC_LEFT, KC_DOWN, KC_RGHT, KC_SPC,  RAISE,   KC_RGUI, KC_RALT, KC_RCTL, KC_APP
    ),

    /* Colemak DH
     * .--------------------------------------------------------------------------------------------------------------------------------------.
     * |        |   9    |   5    |   3    |   1    |   7    |        |        |        |   6    |   0    |   2    |   4    |   8    |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |   Q    |   W    |   F    |   P    |   B    |        |        |        |   J    |   L    |   U    |   Y    |   ;    |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |   A    |   R    |   S    |   T    |   G    |        |        |        |   M    |   N    |   E    |   I    |   O    |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |   Z    |   X    |   C    |   D    |   V    |        |        |        |   K    |   H    |   ,    |   .    |   /    |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
     * '--------------------------------------------------------------------------------------------------------------------------------------'
     */
    [_QWERTY] = LAYOUT_ortho_5x15(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______, _______, _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        _______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    _______, _______, _______, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
        _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    _______, _______, _______, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    _______, _______, _______, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, ENTERS,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /* Fn
     * .--------------------------------------------------------------------------------------------------------------------------------------.
     * | reset  |   F1   |   F2   |   F3   |   F4   |   F5   | numlk  |   P/   |   P*   |   F6   |   F7   |   F8   |   F9   |  F10   |  F11   |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        | Bright+|  Sat+  |  Hue+  | RGBmod+| RGBpln |   P7   |   P8   |   P9   |   -    | prscr  | scrlk  | pause  |  ins   |  F12   |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * | QWERTY | Bright-|  Sat-  |  Hue-  | RGBmod-| RGBtog |   P4   |   P5   |   P6   |   +    |  prev  |  play  |  next  |  stop  | power  |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        | mycomp |  mail  |  calc  |        |        |   P1   |   P2   |   P3   |  PENT  |  mute  |  vol-  |  vol+  | media  | wake   |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |        |        |        |        |   P0   |   P0   |        |   P.   |  PENT  |        |        |        |        | bootL  |
     * '--------------------------------------------------------------------------------------------------------------------------------------'
     */
    [_FN] = LAYOUT_ortho_5x15(
        QK_RBT,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_NUM,  KC_PSLS, KC_PAST, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        XXXXXXX, RGB_VAI, RGB_SAI, RGB_HUI, RGB_MOD, RGB_M_P, KC_P7,   KC_P8,   KC_P9,   KC_MINS, KC_PSCR, KC_SCRL, KC_PAUS, KC_INS,  KC_F12,
        QWERTY,  RGB_VAD, RGB_SAD, RGB_HUD, RGB_RMOD,RGB_TOG, KC_P4,   KC_P5,   KC_P6,   KC_PLUS, KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP, KC_PWR,
        _______, KC_MYCM, KC_MAIL, KC_CALC, XXXXXXX, XXXXXXX, KC_P1,   KC_P2,   KC_P3,   KC_PENT, KC_MUTE, KC_VOLD, KC_VOLU, KC_MSEL, KC_WAKE,
        _______, _______, _______, _______, XXXXXXX, KC_P0,   KC_P0,   XXXXXXX, KC_PDOT, KC_PENT, XXXXXXX, _______, _______, _______, QK_BOOT
    ),

    /* Numberd & Symbols (RAISE)
     * .--------------------------------------------------------------------------------------------------------------------------------------.
     * |        | nonUS# |   /    |   ,    |   <    |        |        |        |        |        |   >    |   ;    |   ?    | nonUS\ |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |   ^    |   9    |   5    |   3    |   1    |   7    |        |        |        |   6    |   0    |   2    |   4    |   8    |   `    |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |   +    |   $    |   =    |   -    |   (    |   .    |        |        |        |   :    |   )    |   _    |   "    |   '    |   !    |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |   %    |   @    |   |    |   &    |   {    |   [    |        |        |        |   ]    |   }    |   *    |   #    |   \    |   ~    |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |        |        |        |        | SYMBL  |        |        |        |        |        |        |        |        |        |
     * '--------------------------------------------------------------------------------------------------------------------------------------'
     */
    [_RAISE] = LAYOUT_ortho_5x15(
        XXXXXXX, KC_NUHS, KC_SLSH, KC_COMM, KC_LABK, XXXXXXX, _______, _______, _______, XXXXXXX, KC_RABK, KC_SCLN, KC_QUES, KC_NUBS, XXXXXXX,
        KC_CIRC, KC_9,    KC_5,    KC_3,    KC_1,    KC_7,    _______, _______, _______, KC_6,    KC_0,    KC_2,    KC_4,    KC_8,    KC_GRV,
        KC_PLUS, KC_DLR,  KC_EQL,  KC_MINS, KC_LPRN, KC_DOT,  _______, _______, _______, KC_COLN, KC_RPRN, KC_UNDS, KC_DQT,  KC_QUOT, KC_EXLM,
        KC_PERC, KC_AT,   KC_PIPE, KC_AMPR, KC_LCBR, KC_LBRC, _______, _______, _______, KC_RBRC, KC_RCBR, KC_ASTR, KC_HASH, KC_BSLS, KC_TILD,
        _______, _______, _______, _______, _______, SYMBL,   _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /* Symbols
     * .--------------------------------------------------------------------------------------------------------------------------------------.
     * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |   ^    |   %    |   +    |   [    |   ,    |        |        |        |   ;    |   ]    |   !    |   ~    |   `    |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |        |        |        |        |   <    |        |        |        |   >    |        |        |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |        |        |        |        |   /    |        |        |        |   ?    |        |        | nonUS# | nonUS\ |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
     * '--------------------------------------------------------------------------------------------------------------------------------------'
     */
    [_SYMBL] = LAYOUT_ortho_5x15(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_CIRC, KC_PERC, KC_PLUS, KC_LBRC, KC_COMM, _______, _______, _______, KC_SCLN, KC_RBRC, KC_EXLM, KC_TILD, KC_GRV,  _______,
        _______, _______, _______, _______, _______, KC_LABK, _______, _______, _______, KC_RABK, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, KC_SLSH, _______, _______, _______, KC_QUES, _______, _______, KC_NUHS, KC_NUBS, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /* Navigation & Functions (LOWER)
     * .--------------------------------------------------------------------------------------------------------------------------------------.
     * |  F17   |  F13   |  F14   |  F15   |  F16   |        |        |        |        |        |  Vol-  |  Mute  |  Vol+  | Eject  |  F21   |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |  F18   |   F1   |   F2   |   F3   |   F4   | Pause  |        |        |        |  Ins   |  PgUp  |   Up   |  PgDn  |  Menu  |  F22   |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |  F19   |   F5   |   F6   |   F7   |   F8   | PrScn  |        |        |        |  Home  |  Left  |  Down  | Right  |  End   |  F23   |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |  F20   |   F9   |  F10   |  F11   |  F12   | ScrLk  |        |        |        |  Tab   | BkSpc  | Enter  |  Del   |        |  F24   |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |        |        |        |        |        |        |        |        | KEYPD  |        |        |        |        |        |
     * '--------------------------------------------------------------------------------------------------------------------------------------'
     */
    [_LOWER] = LAYOUT_ortho_5x15(
        KC_F17,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  XXXXXXX, _______, _______, _______, XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, KC_EJCT, KC_F21,
        KC_F18,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_PAUS, _______, _______, _______, KC_INS,  KC_PGUP, KC_UP,   KC_PGDN, KC_APP,  KC_F22,
        KC_F19,  KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_PSCR, _______, _______, _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  KC_F23,
        KC_F20,  KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_SCRL, _______, _______, _______, KC_TAB,  KC_BSPC, KC_ENT,  KC_DEL,  XXXXXXX, KC_F24,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KEYPD,   _______, _______, _______, _______, _______
    ),

    /* Keypad & Functions2
     * .--------------------------------------------------------------------------------------------------------------------------------------.
     * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |  F13   |  F14   |  F15   |  F16   |        |        |        |        |   *    |   7    |   8    |   9    |   /    | NumLk  |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |  F17   |  F18   |  F19   |  F20   |        |        |        |        |   -    |   4    |   5    |   6    |   +    |   =    |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |  F21   |  F22   |  F23   |  F24   |        |        |        |        |   0    |   1    |   2    |   3    |   .    |  Ent   |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
     * '--------------------------------------------------------------------------------------------------------------------------------------'
     */
    [_KEYPD] = LAYOUT_ortho_5x15(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_F13,  KC_F14,  KC_F15,  KC_F16,  _______, _______, _______, _______, KC_PAST, KC_P7,   KC_P8,   KC_P9,   KC_PSLS, KC_NUM,
        _______, KC_F17,  KC_F18,  KC_F19,  KC_F20,  _______, _______, _______, _______, KC_PMNS, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, KC_PEQL,
        _______, KC_F21,  KC_F22,  KC_F23,  KC_F24,  _______, _______, _______, _______, KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_PDOT, KC_PENT,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /* Modifiers, Multimedia, & Adjustment
     * .--------------------------------------------------------------------------------------------------------------------------------------.
     * | reset  | Bright+|  Sat+  |  Hue+  | RGBmod+| RGBpln | mycomp |  calc  |  mail  |        |        |        |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        | Bright-|  Sat-  |  Hue-  | RGBmod-| RGBtog |        |        |        |        |  Vol-  |  Mute  |  Vol+  | Eject  |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |  Ctrl  |  Alt   |  Cmd   | Shift  | CapsLk |        |        |        | CapsWd | Shift  |  Cmd   |  Alt   |  Ctrl  | power  |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |  Undo  |  Cut   |  Copy  | Paste  | SelAll |        |        |        |  Prev  | Rewind |  Play  |  FFwd  |  Next  |  wake  |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |        |        |        |        |        |        |        |        |        |        |        |        |        | bootL  |
     * '--------------------------------------------------------------------------------------------------------------------------------------'
     */
    [_MODS] = LAYOUT_ortho_5x15(
        QK_RBT,  RGB_VAI, RGB_SAI, RGB_HUI, RGB_MOD, RGB_M_P, KC_MYCM, KC_CALC, KC_MAIL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, RGB_VAD, RGB_SAD, RGB_HUD, RGB_RMOD,RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, KC_EJCT, XXXXXXX,
        XXXXXXX, OS_LCTL, OS_LALT, OS_LGUI, OS_LSFT, KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, CW_TOGG, OS_RSFT, OS_RGUI, OS_RALT, OS_RCTL, KC_PWR,
        XXXXXXX, M_UNDO,  M_CUT,   M_COPY,  M_PASTE, M_SELAL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP, KC_WAKE,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT
    ),
};

void process_osd_keys (uint16_t keycode, keyrecord_t *record, uint8_t os) {
    if (record->event.pressed) {
        register_code16(osd_keys[keycode - M_UNDO][os]);
    } else {
        unregister_code16(osd_keys[keycode - M_UNDO][os]);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
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
