#include QMK_KEYBOARD_H

#define ______ KC_TRNS
#define TAPPING_TERM 175
#define RGB_DI_PIN E2

#define RGBLED_NUM 16
//Tap Dance Declarations
enum {
  TD_LBRC = 0,
  TD_RBRC,
  TD_CAPS,
};

enum custom_keycodes {
  Q_PLUS = SAFE_RANGE,
  Q_STAR,
};

void dance_lbrc(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
			SEND_STRING("(");
	} else if (state->count == 2) {
			SEND_STRING("[");
	} else {
			SEND_STRING("{");
	}
}

void dance_rbrc(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
			SEND_STRING(")");
	} else if (state->count == 2) {
			SEND_STRING("]");
	} else {
		SEND_STRING("}");
	}
}
// All tap dance functions would go here. Only showing this one.
qk_tap_dance_action_t tap_dance_actions[] = {
		[TD_LBRC] = ACTION_TAP_DANCE_FN(dance_lbrc),
    [TD_RBRC] = ACTION_TAP_DANCE_FN(dance_rbrc),
    [TD_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_CAPS, TG(3))
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case Q_PLUS:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING("+");
        } else {
            // when keycode QMKBEST is released
        }
        break;
    case Q_STAR:
        if (record->event.pressed) {
            SEND_STRING("*");
        } else {

        }
        break;
    }
    return true;
};

// Lighting experiments!

// Light LEDs 6 to 9 and 12 to 15 red when caps lock is active. Hard to ignore!
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    // {8, 3, HSV_RED}       // Light 4 LEDs, starting with LED 6
    // {12, 4, HSV_RED}       // Light 4 LEDs, starting with LED 12
    {0, 1, HSV_RED},
    {1, 1, HSV_CORAL},
    {2, 1, HSV_ORANGE},
    {3, 1, HSV_GOLDENROD},
    {4, 1, HSV_GOLD},
    {5, 1, HSV_YELLOW},
    {6, 1, HSV_CHARTREUSE},
    {7, 1, HSV_GREEN},
    {8, 1, HSV_SPRINGGREEN},
    {9, 1, HSV_TURQUOISE},
    {10, 1, HSV_TEAL},
    {11, 1, HSV_CYAN},
    {12, 1, HSV_AZURE},
    {13, 1, HSV_BLUE},
    {14, 1, HSV_PURPLE},
    {15, 1, HSV_MAGENTA}
);
// Light LEDs 9 & 10 in cyan when keyboard layer 1 is active
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {9, 2, HSV_CYAN}
);
// Light LEDs 11 & 12 in purple when keyboard layer 2 is active
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, 3, HSV_SPRINGGREEN}
);

const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, 3, HSV_RED}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer,
    my_layer1_layer,    // Overrides caps lock layer
    my_layer2_layer,     // Overrides other layers
    my_layer3_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}


layer_state_t layer_state_set_user(layer_state_t state) {
    // Both layers will light up if both kb layers are active
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------------------------------------------------------.
   * | ` ~ |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |   Bkspc   |
   * |-----------------------------------------------------------------------------------------+
   * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |    \   |
   * |-----------------------------------------------------------------------------------------+
   * | Caps    |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
   * |-----------------------------------------------------------------------------------------+
   * | Shift     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  | RSh |  U  | DEL |
   * |-----------------------------------------------------------------------------------------+
   * | Ctrl |  Cmd  |  Alt  |              Space                | RAlt | FN  |  L  |  D  |  R  |
   * `-----------------------------------------------------------------------------------------'
   */

  LAYOUT_directional(
      KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, ______, KC_BSPC,
      KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, TD(TD_LBRC), TD(TD_RBRC), KC_BSLS,
      KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
      KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, TG(2), KC_UP, TG(3),
      KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_SPC, KC_SPC, KC_RALT, MO(1), KC_LEFT, KC_DOWN, KC_RIGHT
      ),

  LAYOUT_directional(
      KC_GRV, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_F11, KC_F12, KC_TRNS, RESET,
      ______, RGB_TOG, RGB_MOD, RGB_VAI, RGB_VAD, RGB_HUI, RGB_HUD, ______, ______, ______, ______, ______, ______, ______,
      ______, RGB_HUI, RGB_HUD, RGB_MODE_PLAIN, ______, ______, ______, ______, ______, ______, ______, ______,
      ______, RGB_SAI, RGB_SAD, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, KC_VOLU, ______,
      ______, ______, ______, ______, ______, ______, ______, ______, ______, KC_VOLD, ______
      ),
  LAYOUT_directional(
      TG(2), ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
      ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
      ______, ______, ______, ______, ______, ______, ______, ______, Q_PLUS, KC_MINS, Q_STAR, KC_SLSH,
      ______, ______, ______, ______, ______, ______, ______, ______, KC_COMM, KC_DOT, KC_1, KC_3, KC_5, KC_7, KC_9,
      ______, ______, ______, ______, ______, ______,                                 KC_2, KC_4, KC_6, KC_8, KC_0
      ),
  LAYOUT_directional(
      TG(3), LCTL(KC_UP), ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
      ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
      ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
      ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, KC_MS_WH_UP, KC_MS_BTN1, KC_MS_UP, KC_MS_BTN2,
      ______, ______, ______, ______, ______, ______,                                 ______, KC_MS_WH_DOWN, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT
      ),
};
