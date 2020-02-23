#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0
#define _FN1 1
#define _FN2 2

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  M_PASS = SAFE_RANGE,
  M_WORD,
  M_LMASH,
  M_RMASH,
  M_O,
  M_I,
  M_Y,
  M_P,
};

#define KC_FN1 MO(_FN1)
#define KC_FN2 MO(_FN2)
#define SPFN1 LT(_FN1, KC_SPACE)
#define SPFN2 LT(_FN2, KC_SPACE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,  KC_BSPC,
    KC_LCTL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,          KC_ENT,
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_RSFT, KC_RGUI,
    KC_LCTL,  KC_LGUI, KC_LALT, _______, SPFN1,            SPFN2,                     KC_RALT, KC_0,    KC_RGUI, KC_RCTL
  ),

  [_FN1] = LAYOUT(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,     KC_8,    KC_9,    KC_0,    KC_MINS,          KC_EQL,
    RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, KC_VOLD, KC_QUOT,           KC_SLSH, KC_LBRC, KC_RBRC, KC_BSLS, _______, _______,
    RGB_TOG, _______, _______, _______, _______,          KC_ESC,                     _______, _______, _______, _______
  ),

  [_FN2] = LAYOUT(
    KC_TILD, KC_EXLM, M_WORD,  KC_PGUP, KC_PGDN, KC_PERC, M_Y,     KC_AMPR, M_I,     M_O,     M_P,      KC_UNDS, KC_PLUS,
    _______, KC_HOME, M_LMASH, M_RMASH, KC_END,  KC_HOME, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, M_PASS,          _______,
    _______, _______, _______, KC_DEL,  KC_PGDN, KC_END,           KC_BSPC, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, KC_ESC,           _______,                   _______, _______, _______, _______
  )

};

// macro
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case M_PASS:
      if (record->event.pressed) {
        SEND_STRING("ilikemcu7137");
      } else {
      }
      break;

    case M_WORD:
	  // 左の文字の先頭に移動
      if (record->event.pressed) {
		register_code16(LCTL(KC_LEFT));
      } else {
		unregister_code16(LCTL(KC_LEFT));
      }
	  // 1文字分囲む
      if (record->event.pressed) {
		register_code16(LSFT(KC_RGHT));
      } else {
		unregister_code16(LSFT(KC_RGHT));
      }
      break;

    case M_LMASH:
	  tap_code(KC_LEFT);
	  tap_code(KC_LEFT);
	  tap_code(KC_LEFT);
	  tap_code(KC_LEFT);
	  tap_code(KC_LEFT);
      break;

    case M_RMASH:
	  tap_code(KC_RGHT);
	  tap_code(KC_RGHT);
	  tap_code(KC_RGHT);
	  tap_code(KC_RGHT);
	  tap_code(KC_RGHT);
      break;

    case M_O: // 改行
      if (record->event.pressed) {
		register_code(KC_END);
      } else {
		unregister_code(KC_END);
      }
      if (record->event.pressed) {
		register_code(KC_ENT);
      } else {
		unregister_code(KC_ENT);
      }
      break;

    case M_I: // 一行選択
      if (record->event.pressed) {
		register_code(KC_END);
      } else {
		unregister_code(KC_END);
      }
      if (record->event.pressed) {
		register_code16(LSFT(KC_HOME));
      } else {
		unregister_code16(LSFT(KC_HOME));
      }
      break;

    case M_Y: // コピー
      if (record->event.pressed) {
		register_code16(LCTL(KC_C));
      } else {
		unregister_code16(LCTL(KC_C));
      }
	  break;

    case M_P: // ペースト
      if (record->event.pressed) {
		register_code16(LCTL(KC_V));
      } else {
		unregister_code16(LCTL(KC_V));
      }
	  break;
  }
  return true;
};
