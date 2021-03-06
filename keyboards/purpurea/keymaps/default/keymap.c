/* Copyright 2020 Matt3o
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN1,
    _FN2
};

enum {
    TD_DEL = 0
};
enum custom_keycodes {
  Q_OPEN = SAFE_RANGE,
  Q_CLOSE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case Q_OPEN:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING("(");
        } else {
            // when keycode QMKBEST is released
        }
        break;
    case Q_CLOSE:
        if (record->event.pressed) {
            SEND_STRING(")");
        } else {

        }
        break;
    }
    return true;
};

qk_tap_dance_action_t tap_dance_actions[] = {
        [TD_DEL] = ACTION_TAP_DANCE_DOUBLE(KC_BSLS, KC_DEL)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( KC_GESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, \
          KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, \
          KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, \
          KC_LCTL, KC_LGUI, KC_LALT, MO(1), MO(2), MO(3), KC_SPC,       MO(4), KC_ENT \
      ),
  [1] = LAYOUT( KC_TAB, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSPC, \
                _______, _______, _______, _______, _______, _______, _______, _______, Q_OPEN, Q_CLOSE, TD(TD_DEL), \
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
                _______, _______, _______, _______, _______, _______, _______, _______, _______ \
          ),
  [2] = LAYOUT( KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, \
                _______, KC_KP_PLUS, KC_MINS, KC_KP_ASTERISK, KC_KP_SLASH, _______, _______, _______, KC_LBRC, KC_RBRC, KC_QUOT, \
                _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL, \
                _______, _______, _______, _______, _______, _______, _______, _______, _______ \
          ),
  [3] = LAYOUT( _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9 , KC_F10, \
                _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_UP, KC_DOWN, KC_RGHT, \
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSLS, \
                _______, _______, _______, _______, _______, _______, _______, _______, _______ \
          ),
  [4] = LAYOUT( RESET, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
                _______, _______, _______, _______, _______, _______, _______, _______, _______ \
          )
};
