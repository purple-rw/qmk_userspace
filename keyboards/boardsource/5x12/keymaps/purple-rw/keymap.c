#include QMK_KEYBOARD_H

enum layers {
    _MAIN,
    _RAISE,
    _LOWER,
    _FUNC,
    _NAV,
    _ADJST,
};

// Thumb keys
#define Sx_SPC  LSFT_T(KC_SPC)
#define LOWER   LT(_LOWER, KC_BSPC)
#define RAISE   LT(_RAISE, KC_ENT)
#define SYMBL   MO(_RAISE)
#define FUNC    LT(_FUNC,  KC_DEL)
#define NAV     LT(_NAV,   KC_TAB)
#define ADJST   MO(_ADJST)

// Special keys
#define ZOOMOUT A(G(KC_MINS))
#define ZOOMIN  A(G(KC_EQL))
#define M_UNDO  G(KC_Z)
#define M_CUT   G(KC_X)
#define M_COPY  G(KC_C)
#define M_PASTE G(KC_V)
#define M_SELAL G(KC_A)

// Combos
enum combos {
    // horizontal
    CH_BSSP,
};

#define COMBO_ONLY_FROM_LAYER _MAIN

const uint16_t PROGMEM combo_bssp[] = {LOWER, Sx_SPC, COMBO_END};
combo_t key_combos[] = {
    [CH_BSSP] = COMBO(combo_bssp, ADJST)
};
uint16_t COMBO_LEN = sizeof(key_combos) / sizeof(key_combos[0]);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* (Hold)
 * -------------------------------------------------------------------------
 * |     |     |     |     |     |     |     |     | RAlt|     |     |     |
 * |     |     |     |     |     |     |     |     |RAISE|     |     |     |
 * |     |     |     |     |     |     |     |     | RGui|     |     |     |
 * |     |     |     |     |     |     |     |     |RCtrl|     |     |     |
 * |     |LCtrl| LAlt| LGui| NAV |LOWER|LShft|RAISE| FUNC|     |     |     |
 * -------------------------------------------------------------------------
 */

/*
 * MAIN (Colemak-DH)
 * -------------------------------------------------------------------------
 * | Esc |  Q  |  M  |  L  |  U  |  P  |  B  |  J  |     |  7  |  8  |  9  |
 * |  X  |  ;  |  O  |  N  |  I  |  S  |  F  |  K  |     |  4  |  5  |  6  |
 * |  '  |  .  |  A  |  R  |  E  |  T  |  C  |  G  |     |  1  |  2  |  3  |
 * |  Z  |  /  |  ,  |  H  |  Y  |  D  |  W  |  V  |     |  0  |  Up |  .  | 
 * |CapLk|     |     |     | Tab |BkSpc|Space|Enter| Del | Left| Down|Right|
 * -------------------------------------------------------------------------
 */
[_MAIN] = LAYOUT_ortho_5x12(
    KC_ESC,  KC_Q,    KC_M,    KC_L,    KC_U,    KC_P,    KC_B,    KC_J,    KC_RALT, KC_7,    KC_8,    KC_9,
    KC_X,    KC_SCLN, KC_O,    KC_N,    KC_I,    KC_S,    KC_F,    KC_K,    SYMBL,   KC_4,    KC_5,    KC_6,
    KC_QUOT, KC_DOT,  KC_A,    KC_R,    KC_E,    KC_T,    KC_C,    KC_G,    KC_RGUI, KC_1,    KC_2,    KC_3,
    KC_Z,    KC_SLSH, KC_COMM, KC_H,    KC_Y,    KC_D,    KC_W,    KC_V,    KC_RCTL, KC_DOT,  KC_SLSH, KC_0,
    KC_CAPS, KC_LCTL, KC_LALT, KC_LGUI, NAV,     LOWER,   Sx_SPC,  RAISE,   FUNC,    KC_LEFT, KC_DOWN, KC_RGHT
),

/* RAISE (Symbols)
 * -------------------------------------------------------------------------
 * |     |     |     |  ~  |  `  |  ^  |  {  |  }  |     |  =  |  *  |  /  |
 * |     |  :  |  %  |  |  |  &  |  $  |  [  |  ]  |     |  ,  |  +  |  -  |
 * |  "  |  !  |  *  |  =  |  -  |  _  |  (  |  )  |     |     |  :  |  ;  |
 * |     |  ?  |  @  |  \  |  +  |  #  |  <  |  >  |     |     | Vol+|     |
 * | Menu|     |     |     |     |     |     | *** |     |Zoom-| Vol-|Zoom+|
 * -------------------------------------------------------------------------
 */
[_RAISE] = LAYOUT_ortho_5x12(
    _______, _______, _______, KC_TILD, KC_GRV,  KC_CIRC, KC_LCBR, KC_RCBR, _______, KC_EQL,  KC_ASTR, KC_SLSH,
    _______, KC_COLN, KC_PERC, KC_PIPE, KC_AMPR, KC_DLR,  KC_LBRC, KC_RBRC, _______, KC_COMM, KC_PLUS, KC_MINS,
    KC_DQT,  KC_EXLM, KC_ASTR, KC_EQL,  KC_MINS, KC_UNDS, KC_LPRN, KC_RPRN, _______, _______, KC_COLN, KC_SCLN,
    _______, KC_QUES, KC_AT,   KC_BSLS, KC_PLUS, KC_HASH, KC_LABK, KC_RABK, _______, _______, KC_VOLU, _______,
    KC_APP,  _______, _______, _______, _______, _______, _______, _______, _______, ZOOMOUT, KC_VOLD, ZOOMIN
),

/* LOWER (Numbers)
 * -------------------------------------------------------------------------
 * |     |  =  |  *  |  7  |  8  |  9  |  /  |     |     |     |     |     |
 * | Next|  ,  |  +  |  4  |  5  |  6  |  -  |     |     |     |     |     |
 * | Play|  .  |  :  |  1  |  2  |  3  |  ;  |     |     |     |     |     |
 * | Prev|  /  |  ,  |  .  |Enter|  0  |NmLck|     |     |     | Vol+|     |
 * | Menu|     |     |     |     | *** |ADJST|     |     |Zoom-| Vol-|Zoom+|
 * -------------------------------------------------------------------------
 */
[_LOWER] = LAYOUT_ortho_5x12(
    _______, KC_PEQL, KC_PAST, KC_P7,   KC_P8,   KC_P9,   KC_PSLS, _______, _______, _______, _______, _______,
    KC_MNXT, KC_PCMM, KC_PPLS, KC_P4,   KC_P5,   KC_P6,   KC_PMNS, _______, _______, _______, _______, _______,
    KC_MPLY, KC_PDOT, KC_COLN, KC_P1,   KC_P2,   KC_P3,   KC_SCLN, _______, _______, _______, _______, _______,
    KC_MPRV, KC_PSLS, KC_PCMM, KC_PDOT, KC_ENT,  KC_P0,   KC_NUM,  _______, _______, _______, KC_VOLU, _______,
    KC_APP,  _______, _______, _______, _______, _______, ADJST,   _______, _______, ZOOMOUT, KC_VOLD, ZOOMIN
),

/* Functions
 * -------------------------------------------------------------------------
 * |Power|     | F1  | F2  | F3  | F4  | F5  | F6  |     |     |     |     |
 * |Sleep|Pause| F7  | F8  | F9  | F10 | F11 | F12 |     |     |     |     |
 * |     |PrScr| F13 | F14 | F15 | F16 | F17 | F18 |     |     |     |     |
 * |     |ScLck| F19 | F20 | F21 | F22 | F23 | F24 |     |     |PgUp |     |
 * |     |     |     |     |     |     |     |     | *** | Home|PgDn | End |
 * -------------------------------------------------------------------------
 */
[_FUNC] = LAYOUT_ortho_5x12(
  KC_PWR,  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______, _______, _______, _______,
  KC_SLEP, KC_PAUS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______,
  _______, KC_PSCR, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  _______, _______, _______, _______,
  _______, KC_SCRL, KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,  _______, _______, KC_PGUP, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_END
),

/* Navigation and Multimedia
 * -------------------------------------------------------------------------
 * |     |     |     |     |     |     |     |     |     |     |     |     |
 * |     |     | Ins |PgUp | Up  |PgDn | Del |     |     |     |     |     |
 * |     |     |Home |Left |Down |Right| End |     |     |     |     |     |
 * |     |SeAll|Undo | Cut |Copy |Paste|     |     |     |     |     |     |
 * |     |     |     |     | *** |     |     |     |     |     |     |     |
 * -------------------------------------------------------------------------
 */
[_NAV] = LAYOUT_ortho_5x12(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, KC_INS,  KC_PGUP, KC_UP,   KC_PGDN, KC_DEL,  _______, _______, _______, _______, _______,
  _______, _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  _______, _______, _______, _______, _______,
  _______, M_SELAL, M_UNDO,  M_CUT,   M_COPY,  M_PASTE, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Adjustment
 * -------------------------------------------------------------------------
 * |BootL|Reset|     |     |     |     |     |     |     |     |     |     |
 * |AGswp|AGnrm|     |     |     |     |     |     |     |     |     |     |
 * |     |     |     |     |     |     |     |     |     |     |     |     |
 * |     |     |     |     |     |     |     |     |     |     |     |     |
 * |     |     |     |     |     | *** | *** |     |     |     |Reset|BootL|
 * -------------------------------------------------------------------------
 */
[_ADJST] = LAYOUT_ortho_5x12(
  QK_BOOT, QK_RBT,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  AG_SWAP, AG_NORM, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_RBT,  QK_BOOT
)

};
