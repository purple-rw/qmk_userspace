/* Copyright 2021 Caleb Lightfoot
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
#pragma once

/* custom pin connections for upside-down Pro Micro */
#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS
#undef UNUSED_PINS
#define MATRIX_ROW_PINS { D1, D0, D4, C6 }
#define MATRIX_COL_PINS { B4, B5, F4, F5, F6, F7, B1, B3, B2, B6 }
#define UNUSED_PINS     { D2, D3, D7, E6 }

/* LEDs on Pro Micro are used as status indicators */
#define LED_NUM_LOCK_PIN  B0
#define LED_CAPS_LOCK_PIN D5
#define LED_PIN_ON_STATE  0

/* Tapping toggle and timeout */
#define TAPPING_TOGGLE 3
#define ONESHOT_TAP_TOGGLE 3  /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 3000  /* Time (in ms) before the one shot key is released */
