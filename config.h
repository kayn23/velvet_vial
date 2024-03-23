#pragma once

/* RGB matrix support. */
#ifdef RGB_MATRIX_ENABLE
#define SPLIT_TRANSPORT_MIRROR
#define RGB_MATRIX_LED_COUNT 38
#define RGB_MATRIX_SPLIT { 19, 19 }
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
#define RGB_DISABLE_WHEN_USB_SUSPENDED
#define RGB_MATRIX_KEYPRESSES
#endif
