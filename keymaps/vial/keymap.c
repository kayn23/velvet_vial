/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#define KC_LANG LCTL(KC_SPC)

enum layout {
    QWE = 0,
    DVO,
    NAV,
    SYM,
};

enum key {
    PREV_APP = QK_KB_0,
    NEXT_APP,
    DVO_QWE,
    T_BASE_H_NAV,
    T_MEDIA_H_SYM,
    LANG,
};
bool is_select_prev_app_active = false;
bool is_select_next_app_active = false;
bool esc_and_enter_handle = true;

uint16_t timer_base_nav;
uint16_t timer_media_sym;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [QWE] = LAYOUT_split(\
    KC_Q,          KC_W,         KC_E,         KC_R,             KC_T,           KC_Y,    KC_U,             KC_I,         KC_O,         KC_P, \
    LCTL_T(KC_A),  LOPT_T(KC_S), LSFT_T(KC_D), LCMD_T(KC_F),     KC_G,           KC_H,     LCMD_T(KC_J),    RSFT_T(KC_K), LOPT_T(KC_L), LCTL_T(KC_SCLN), \
    KC_Z,          KC_X,         KC_C,         KC_V,             KC_B,           KC_N,    KC_M,             KC_COMM,      KC_DOT,       KC_SLSH,\
                   DVO_QWE,      KC_RBRC,      LT(NAV, KC_ESC),  KC_ENT,         KC_SPC,  LT(SYM, KC_BSPC), KC_LBRC,      KC_QUOT \
    ),
    [DVO] = LAYOUT_split(\
    KC_QUOTE,     KC_COMM,      KC_DOT,       KC_P,             KC_Y,           KC_F,    KC_G,             KC_C,         KC_R,         KC_L, \
    LCTL_T(KC_A), LALT_T(KC_O), LSFT_T(KC_E), LCMD_T(KC_U),     KC_I,           KC_D,    LCMD_T(KC_H),     RSFT_T(KC_T), LOPT_T(KC_N), RCTL_T(KC_S),  \
    KC_SCLN,      KC_Q,         KC_J,         KC_K,             KC_X,           KC_B,    KC_M,             KC_W,         KC_V,         KC_Z,  \
                  DVO_QWE,      KC_TAB,       LT(NAV, KC_ESC),  KC_ENT,         KC_SPC,  LT(SYM, KC_BSPC), KC_SLSH,      KC_MINS \
    ),
    [NAV] = LAYOUT_split(\
    LGUI(KC_LBRC),  LGUI(KC_RBRC), LCTL(KC_TAB),  RCS(KC_TAB),    LGUI(KC_BSPC),        KC_TAB,         KC_MPLY,          KC_MUTE,          KC_VOLD,        KC_VOLU, \
	LCTL_T(KC_TAB), KC_LOPT,       KC_LSFT,       KC_LCMD,        LOPT(KC_BSPC),        RCMD(KC_LEFT),  KC_LEFT,          KC_DOWN,          KC_UP,          KC_RGHT, \
	SGUI(KC_6),       SGUI(KC_Q),    LCTL(KC_LEFT), LCTL(KC_RIGHT), KC_F12,               RCMD(KC_RIGHT), LALT(KC_LEFT),    LALT(KC_RIGHT),   LSA(KC_LEFT),   LSA(KC_RIGHT), \
                    KC_TAB,        KC_RBRC,       KC_NO,          KC_ENT,               KC_SPC,         KC_NO,          KC_LBRC,          KC_QUOT \
    ),
    [SYM] = LAYOUT_split(\
    KC_EXLM,        KC_AT,         KC_HASH,       KC_DLR,         KC_PERC,              KC_CIRC,       KC_AMPR,       KC_ASTR,       KC_LPRN,        KC_RPRN, \
    LCTL_T(KC_P1),  LOPT_T(KC_P2), LSFT_T(KC_P3), LCMD_T(KC_P4),  KC_P5,                KC_P6,         RCMD_T(KC_P7), RSFT_T(KC_P8), ROPT_T(KC_P9),  RCTL_T(KC_P0), \
    KC_LCBR,        KC_RCBR,       KC_MINS,       KC_EQL,         KC_GRV,               KC_TILD,       KC_GT,         KC_DQT,        KC_NUBS,        KC_PIPE, \
                    KC_LBRC,       KC_RBRC,       RGB_TOG,          KC_ENT,               KC_SPC,        KC_NO,         KC_LBRC,       KC_QUOT \
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return state;
};


void unselect_app_selection(void) {
	esc_and_enter_handle = true;
    if (is_select_prev_app_active == true) {
        is_select_prev_app_active = false;
		esc_and_enter_handle = false;
		unregister_mods(MOD_MASK_SG);
    }
    if (is_select_next_app_active == true) {
        is_select_next_app_active = false;
		esc_and_enter_handle = false;
		unregister_mods(MOD_MASK_GUI);
    }
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case T_BASE_H_NAV:
            if (record->event.pressed) {
                timer_base_nav = timer_read();
                if (IS_LAYER_OFF(NAV)) layer_on(NAV);
            } else {
                if (IS_LAYER_ON(NAV)) {
					unselect_app_selection();
                	layer_off(NAV);
				}
                // if (timer_elapsed(timer_base_nav) < TAPPING_TERM) {
                //     default_layer_xor((DVO + 1) | (QWE + 1));
				// 	register_mods(MOD_MASK_CSAG);
				// 	register_code(KC_SPC);
                //     clear_keyboard();
                // }
            }
            return false;
        case T_MEDIA_H_SYM:
            if (record->event.pressed) {
                timer_media_sym = timer_read();
                if (IS_LAYER_OFF(SYM)) layer_on(SYM);
            } else {
                if (IS_LAYER_ON(SYM)) {
                	layer_off(SYM);
				}
                // if (timer_elapsed(timer_media_sym) < TAPPING_TERM) {
                //     layer_on(MEDIA);
                // }
            }
            return false;

        case PREV_APP:
            if (record->event.pressed) {
                if (is_select_prev_app_active == false) {
                    if (is_select_next_app_active == true) {
                        is_select_next_app_active = false;
                        clear_mods();
                    }
                    register_mods(MOD_MASK_SG);
                    tap_code(KC_TAB);
                    is_select_prev_app_active = true;
                } else {
                    tap_code(KC_TAB);
                }
            }
            return false;
        case NEXT_APP:
            if (record->event.pressed) {
                if (is_select_next_app_active == false) {
                    if (is_select_prev_app_active == true) {
                        is_select_prev_app_active = false;
                        clear_mods();
                    }
                    register_mods(MOD_MASK_GUI);
                    tap_code(KC_TAB);
                    is_select_next_app_active = true;
                } else {
                    tap_code(KC_TAB);
                }
            }
            return false;
        case KC_ENT:
            if (record->event.pressed) {
                unselect_app_selection();
            }
            return esc_and_enter_handle;
        case KC_ESC:
            if (record->event.pressed) {
                unselect_app_selection();
            }
            return esc_and_enter_handle;
        case DVO_QWE:
            if (record->event.pressed) {
                register_mods(MOD_MASK_CTRL);
                tap_code(KC_SPC);
                unregister_mods(MOD_MASK_CTRL);
                default_layer_xor((DVO + 1) | (QWE + 1));
                clear_keyboard();
            }
            return false;
        case LANG:
            if (record->event.pressed) {
				register_mods(MOD_MASK_CTRL);
                tap_code(KC_SPC);
            } else {
                clear_keyboard();
            }
            return false;
        default:
            return true;
    }
}