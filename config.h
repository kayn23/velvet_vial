#pragma once

#define EE_HANDS
/* RGB matrix support. */
#ifdef RGB_MATRIX_ENABLE
#define SPLIT_TRANSPORT_MIRROR
#define RGB_MATRIX_LED_COUNT 38
#define RGB_MATRIX_SPLIT { 19, 19 }
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
#define RGB_DISABLE_WHEN_USB_SUSPENDED
#define RGB_MATRIX_KEYPRESSES
#endif

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

#define XXX KC_NO

#define LAYOUT_split( \
    L00, L01, L02, L03, L04,     R04, R03, R02, R01, R00, \
    L10, L11, L12, L13, L14,     R14, R13, R12, R11, R10, \
    L20, L21, L22, L23, L24,     R24, R23, R22, R21, R20, \
         L31, L32, L33, L34,     R34, R33, R32, R31 \
) { \
    { L00, L01, L02, L03, L04 }, \
    { L10, L11, L12, L13, L14 }, \
    { L20, L21, L22, L23, L24 }, \
    { XXX, L31, L32, L33, L34 }, \
    { R00, R01, R02, R03, R04 }, \
    { R10, R11, R12, R13, R14 }, \
    { R20, R21, R22, R23, R24 }, \
    { XXX, R31, R32, R33, R34 } \
}

