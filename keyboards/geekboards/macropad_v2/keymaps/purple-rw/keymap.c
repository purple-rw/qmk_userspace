/* Copyright 2020 Geekboards ltd. (geekboards.ru / geekboards.de)
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
#include "keys.h"
#include "g/keymap_combo.h"

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_ALPHAS] = LAYOUT_ortho_2x4(
        KEY_T4,  KEY_T3,  KEY_T2,  KEY_T1,
        KEY_B4,  KEY_B3,  KEY_B2,  KEY_B1
    ),

    [LAYER_NUMBERS] = LAYOUT_ortho_2x4(
        KNUM_T4, KNUM_T3, KNUM_T2, KNUM_T1,
        KNUM_B4, KNUM_B3, KNUM_B2, KNUM_B1
    ),

    [LAYER_SYMBOLS] = LAYOUT_ortho_2x4(
        KSYM_T4, KSYM_T3, KSYM_T2, KSYM_T1,
        KSYM_B4, KSYM_B3, KSYM_B2, KSYM_B1
    ),

    [LAYER_PARENS] = LAYOUT_ortho_2x4(
        KPRN_T4, KPRN_T3, KPRN_T2, KPRN_T1,
        KPRN_B4, KPRN_B3, KPRN_B2, KPRN_B1
    ),

    [LAYER_MEDIA] = LAYOUT_ortho_2x4(
        KMDA_T4, KMDA_T3, KMDA_T2, KMDA_T1,
        KMDA_B4, KMDA_B3, KMDA_B2, KMDA_B1
    ),

    [LAYER_ARROWS] = LAYOUT_ortho_2x4(
        KARR_T4, KARR_T3, KARR_T2, KARR_T1,
        KARR_B4, KARR_B3, KARR_B2, KARR_B1
    ),

    [LAYER_NAV] = LAYOUT_ortho_2x4(
        KNAV_T4, KNAV_T3, KNAV_T2, KNAV_T1,
        KNAV_B4, KNAV_B3, KNAV_B2, KNAV_B1
    ),

    [LAYER_MOUSE] = LAYOUT_ortho_2x4(
        KMSE_T4, KMSE_T3, KMSE_T2, KMSE_T1,
        KMSE_B4, KMSE_B3, KMSE_B2, KMSE_B1
    ),
    [LAYER_MOUSE_SCROLL] = LAYOUT_ortho_2x4(
        KMSS_T4, KMSS_T3, KMSS_T2, KMSS_T1,
        KMSS_B4, KMSS_B3, KMSS_B2, KMSS_B1
    ),

    [LAYER_FUNCS] = LAYOUT_ortho_2x4(
        KFUN_T4, KFUN_T3, KFUN_T2, KFUN_T1,
        KFUN_B4, KFUN_B3, KFUN_B2, KFUN_B1
    ),

    [LAYER_RGB] = LAYOUT_ortho_2x4(
        KRGB_T4, KRGB_T3, KRGB_T2, KRGB_T1,
        KRGB_B4, KRGB_B3, KRGB_B2, KRGB_B1
    )
};

uint8_t mod_hand = 0;       // 0=left, 1=right
uint8_t mod_hand_os = 0;    // 1=pressed

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case OSM_HND:
            if (record->event.pressed) {
                mod_hand ^= (mod_hand_os ^ 1);  // switch hand if osm NOT pressed previously
                mod_hand_os = 1;                // remember to switch again after a key press
            }
            break;
        case LCK_HND:
            if (record->event.pressed) {
                mod_hand ^= (mod_hand_os ^ 1);  // switch hand if osm NOT pressed previously
                mod_hand_os = 0;                // cancel osm
            }
            break;
        case LCK_SFT:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(mod_hand ? KC_RSFT : KC_LSFT)) {
                    unregister_mods(MOD_BIT(mod_hand ? KC_RSFT : KC_LSFT));
                }
                else {
                    register_mods(MOD_BIT(mod_hand ? KC_RSFT : KC_LSFT));
                }
            } else {
                mod_hand ^= mod_hand_os;        // switch hand is osm pressed
                mod_hand_os = 0;                // cancel osm
            }
            break;
        case OSM_CTL:
            if (record->event.pressed) {
                add_oneshot_mods(MOD_BIT(mod_hand ? KC_RCTL : KC_LCTL));
            } else {
                mod_hand ^= mod_hand_os;        // switch hand if osm pressed
                mod_hand_os = 0;                // cancel osm
            }
            break;
        case OSM_GUI:
            if (record->event.pressed) {
                add_oneshot_mods(MOD_BIT(mod_hand ? KC_RGUI : KC_LGUI));
            } else {
                mod_hand ^= mod_hand_os;        // switch hand if osm pressed
                mod_hand_os = 0;                // cancel osm
            }
            break;
        case OSM_ALT:
            if (record->event.pressed) {
                add_oneshot_mods(MOD_BIT(mod_hand ? KC_RALT : KC_LALT));
            } else {
                mod_hand ^= mod_hand_os;        // switch hand if osm pressed
                mod_hand_os = 0;                // cancel osm
            }
            break;
        case OSM_SFT:
            if (record->event.pressed) {
                add_oneshot_mods(MOD_BIT(mod_hand ? KC_RSFT : KC_LSFT));
            } else {
                mod_hand ^= mod_hand_os;        // switch hand if osm pressed
                mod_hand_os = 0;                // cancel osm
            }
            break;
        default:
            if (record->event.pressed) {
                mod_hand ^= mod_hand_os;        // switch hand if osm pressd
                mod_hand_os = 0;                // cancel osm
            }
    }
    return true;
}