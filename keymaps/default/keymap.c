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
#include "3x5_4.h"

enum layout {
    QWE = 0,
    NAV,
    SYM
};

enum key {
    PREV_APP = QK_KB_0,
    NEXT_APP,
    T_BASE_H_NAV,
    T_MEDIA_H_SYM
};
bool is_select_prev_app_active = false;
bool is_select_next_app_active = false;
bool esc_and_enter_handle = true;

uint16_t timer_base_nav;
uint16_t timer_media_sym;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [QWE] = LAYOUT_split(\
    KC_Q, KC_W,   KC_E,     KC_R,   KC_T,     KC_Y,   KC_U,    KC_I,    KC_O,   KC_P, \
    KC_A, KC_S,   KC_D,     KC_F,   KC_G,     KC_H,   KC_J,    KC_K,    KC_L,   KC_L, \
    KC_Z, KC_X,   KC_C,     KC_V,   KC_B,     KC_N,   KC_M,    KC_COMM, KC_DOT, KC_SLSH,\
          KC_ESC, KC_SPACE, KC_DOT, KC_ENT,   KC_SPC, KC_COMM, KC_BSPC, KC_ESC\
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
        default:
            return true;
    }
}