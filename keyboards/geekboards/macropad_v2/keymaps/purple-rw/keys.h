// Copyright (c) 2024 purple-rw
// SPDX-License-Identifier: Apache-2.0
#pragma once

/*
 *        Left Hand                          Right Hand
 *  ,-------------------.              ,-------------------.
 *  | T4 | T3 | T2 | T1 |   Top row    | T1 | T2 | T3 | T4 |
 *  |----+----+----+----|              |----+----+----+----|
 *  | B4 | B3 | B2 | B1 |  Bottom row  | B1 | B2 | B3 | B4 | 
 *  `-------------------'              `-------------------'
 */

enum Layers {
    LAYER_ALPHAS,
    LAYER_NUMBERS,
    LAYER_KEYPAD,
    LAYER_KP_SYMBOLS,
    LAYER_SYMBOLS,
    LAYER_PARENS,
    LAYER_MEDIA,
    LAYER_ARROWS,
    LAYER_NAV,
    LAYER_FUNCS,
    LAYER_RGB,
    LAYER_MOUSE,
    LAYER_MOUSE_SCROLL
};

enum custom_keycodes {
    OSM_SFT = SAFE_RANGE,
    OSM_GUI,
    OSM_ALT,
    OSM_CTL,
    OSM_HND,    // one-shot to switching hand for modifiers
    LCK_SFT,
    LCK_GUI,
    LCK_ALT,
    LCK_CTL,
    LCK_HND,    // lock switching hand for modifiers
};

// Base layer
#define KEY_T1 LT(LAYER_PARENS,  KC_S)
#define KEY_T2 KC_I
#define KEY_T3 KC_N
#define KEY_T4 LT(LAYER_MEDIA,   KC_O)
#define KEY_B1 LT(LAYER_SYMBOLS, KC_T)
#define KEY_B2 KC_E
#define KEY_B3 KC_R
#define KEY_B4 LT(LAYER_NUMBERS, KC_A)

// Number layer (Left Hand)
#define KNUM_T1 KC_6
#define KNUM_T2 KC_5
#define KNUM_T3 KC_4
#define KNUM_T4 KC_0
#define KNUM_B1 KC_3
#define KNUM_B2 KC_2
#define KNUM_B3 KC_1
#define KNUM_B4 _______

// Keypad layer (Left Hand)
#define KPAD_T1 LT(LAYER_PARENS,     KC_P6)
#define KPAD_T2 KC_P5
#define KPAD_T3 KC_P4
#define KPAD_T4 LT(LAYER_MEDIA,      KC_P0)
#define KPAD_B1 LT(LAYER_SYMBOLS,    KC_P3)
#define KPAD_B2 KC_P2
#define KPAD_B3 KC_P1
#define KPAD_B4 LT(LAYER_KP_SYMBOLS, KC_PDOT)

// Keypad Symbols layer
#define KPDS_T1 KC_PAST
#define KPDS_T2 KC_PSLS
#define KPDS_T3 KC_PEQL
#define KPDS_T4 KC_NUM
#define KPDS_B1 KC_PPLS
#define KPDS_B2 KC_PMNS
#define KPDS_B3 XXXXXXX
#define KPDS_B4 _______

// Symbols layer
#define KSYM_T1 KC_EXLM
#define KSYM_T2 KC_UNDS
#define KSYM_T3 KC_ASTR
#define KSYM_T4 KC_HASH
#define KSYM_B1 KC_TRNS
#define KSYM_B2 KC_MINS
#define KSYM_B3 KC_EQL
#define KSYM_B4 KC_DLR

// Parenthesis layer (Left Hand)
#define KPRN_T1 _______
#define KPRN_T2 KC_RPRN
#define KPRN_T3 KC_LPRN
#define KPRN_T4 KC_LCBR
#define KPRN_B1 XXXXXXX
#define KPRN_B2 KC_RBRC
#define KPRN_B3 KC_LBRC
#define KPRN_B4 KC_RCBR

// Multimedia layer (Left Hand)
#define KMDA_T1 KC_VOLU
#define KMDA_T2 KC_MUTE
#define KMDA_T3 KC_VOLD
#define KMDA_T4 _______
#define KMDA_B1 KC_PSCR
#define KMDA_B2 KC_SCRL
#define KMDA_B3 KC_PAUS
#define KMDA_B4 XXXXXXX

// Navigation layer (Left Hand)
#define KNAV_T1 KC_PGUP
#define KNAV_T2 KC_PGDN
#define KNAV_T3 _______
#define KNAV_T4 XXXXXXX
#define KNAV_B1 KC_END
#define KNAV_B2 KC_HOME
#define KNAV_B3 KC_APP
#define KNAV_B4 _______

// Arrow layer (Left Hand)
#define KARR_T1 KC_UP
#define KARR_T2 KC_DOWN
#define KARR_T3 XXXXXXX
#define KARR_T4 XXXXXXX
#define KARR_B1 KC_RIGHT
#define KARR_B2 KC_LEFT
#define KARR_B3 _______
#define KARR_B4 _______

// Functions layer (Left Hand)
#define KFUN_T1 KC_F4
#define KFUN_T2 KC_F3
#define KFUN_T3 KC_F2
#define KFUN_T4 KC_F1
#define KFUN_B1 KC_F8
#define KFUN_B2 KC_F7
#define KFUN_B3 KC_F6
#define KFUN_B4 KC_F5

// Functions layer
#define KRGB_T1 RGB_MOD
#define KRGB_T2 RGB_VAI
#define KRGB_T3 RGB_HUI
#define KRGB_T4 RGB_SPI
#define KRGB_B1 RGB_RMOD
#define KRGB_B2 RGB_VAD
#define KRGB_B3 RGB_HUD
#define KRGB_B4 RGB_SPD

// Mouse layer (Left Hand)
#define KMSE_T1 KC_BTN1
#define KMSE_T2 KC_MS_U
#define KMSE_T3 KC_BTN2
#define KMSE_T4 KC_BTN3
#define KMSE_B1 KC_MS_R
#define KMSE_B2 KC_MS_D
#define KMSE_B3 KC_MS_L
#define KMSE_B4 MO(LAYER_MOUSE_SCROLL)

// Mouse Scroll layer (Left Hand)
#define KMSS_T1 _______
#define KMSS_T2 KC_WH_U
#define KMSS_T3 _______
#define KMSS_T4 _______
#define KMSS_B1 KC_WH_R
#define KMSS_B2 KC_WH_D
#define KMSS_B3 KC_WH_L
#define KMSS_B4 _______