/* Copyright 2022 DOIO
 * Copyright 2022 HorrorTroll <https://github.com/HorrorTroll>
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

// OLED animation
#include "./lib/layer_status/layer_status.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_names {
    _BASE,
    _CHORD,
    _LAYER3,
    _TUPLET
};

#define DIAG_UP A(S(KC_UP))
#define DIAG_DN A(S(KC_DOWN))
#define OCTV_UP G(KC_UP)
#define OCTV_DN G(KC_DOWN)

// enum layer_keycodes { };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
       ┌─────┬─────┬─────┬─────┐   ┌─────┐ ┌─────┐
       │  2  │  .  │  0  │  7  │   │Space│ │Enter│
       ├─────┼─────┼─────┼─────┤   └─────┘ └─────┘
       │  3  │  4  │  5  │  6  │
       ├─────┼─────┼─────┼─────┤
       │  a  │  b  │  c  │  d  │       ┌─────┐
       ├─────┼─────┼─────┼─────┤       │ Mute│
       │BkSpc│  e  │  f  │  g  │       └─────┘
       └─────┴─────┴─────┴─────┘

*/
    [_BASE]   = LAYOUT(
                  KC_2,                KC_DOT,  KC_0,    KC_7,     KC_SPC,
                  KC_3,                KC_4,    KC_5,    KC_6,     KC_ENT,
                  LT(_LAYER3, KC_A),   KC_B,    KC_C,    KC_D,     KC_MUTE,
                  LT(_CHORD, KC_BSPC), KC_E,    KC_F,    LT(_TUPLET, KC_G)
                ),

/*
       ┌─────┬─────┬─────┬─────┐   ┌─────┐ ┌─────┐
       │+2nd │+9th │+8th │+7th │   │     │ │     │
       ├─────┼─────┼─────┼─────┤   └─────┘ └─────┘
       │+3rd │+4th │+5th │+6th │
       ├─────┼─────┼─────┼─────┤
       │ +A  │ +B  │ +C  │ +D  │       ┌─────┐
       ├─────┼─────┼─────┼─────┤       │     │
       │ XXX │ +E  │ +F  │ +G  │       └─────┘
       └─────┴─────┴─────┴─────┘
*/
    [_CHORD]  = LAYOUT(
                  A(KC_2), A(KC_9), A(KC_8), A(KC_7), _______,
                  A(KC_3), A(KC_4), A(KC_5), A(KC_6), _______,
                  S(KC_A), S(KC_B), S(KC_C), S(KC_D), _______,
                  _______, S(KC_E), S(KC_F), S(KC_G)
                ),

/*
       ┌─────┬─────┬─────┬─────┐   ┌─────┐ ┌─────┐
       │  Q  │  W  │  x  │  j  │   │     │ │     │
       ├─────┼─────┼─────┼─────┤   └─────┘ └─────┘
       │  q  │  w  │  s  │  t  │
       ├─────┼─────┼─────┼─────┤
       │ XXX │diag+│semi+│ oct+│       ┌─────┐
       ├─────┼─────┼─────┼─────┤       │     │
       │     │diag-│semi-│ oct-│       └─────┘
       └─────┴─────┴─────┴─────┘
*/
    [_LAYER3] = LAYOUT(
                  S(KC_Q), S(KC_W), KC_X,    KC_J,    _______,
                  KC_Q,    KC_W,    KC_S,    KC_T,    _______,
                  _______, DIAG_UP, KC_UP,   OCTV_UP, _______,
                  _______, DIAG_DN, KC_DOWN, OCTV_DN
                ),

/*
       ┌─────┬─────┬─────┬─────┐   ┌─────┐ ┌─────┐
       │2plet│9plet|8plet|7plet│   │     │ │     │
       ├─────┼─────┼─────┼─────┤   └─────┘ └─────┘
       │3plet|4plet|5plet|6plet│
       ├─────┼─────┼─────┼─────┤
       │     |     |     |     │       ┌─────┐
       ├─────┼─────┼─────┼─────┤       │     │
       │     │     |     │ XXX │       └─────┘
       └─────┴─────┴─────┴─────┘
*/
    [_TUPLET] = LAYOUT(
                  G(KC_2), G(KC_9), G(KC_8), G(KC_7), _______,
                  G(KC_3), G(KC_4), G(KC_5), G(KC_6), _______,
                  _______, _______, _______, _______, _______,
                  _______, _______, _______, _______
                ),
};

#ifdef OLED_ENABLE
    bool oled_task_user(void) {
        render_layer_status();

        return true;
    }
#endif

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE]   = { ENCODER_CCW_CW(KC_LEFT, KC_RGHT), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_CHORD]  = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [_LAYER3] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [_TUPLET] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
};
#endif
