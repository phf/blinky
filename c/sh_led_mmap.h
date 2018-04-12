#ifndef SH_LED_MMAP
#define SH_LED_MMAP

/*
 * Low-level mmap-style access to Sense HAT LEDs. There are 64 LEDs in an 8x8
 * matrix. Each LED's color is a uint16_t in RGB 565 format. See sh_led.h for
 * a more high-level interface.
 */

#include <stdint.h>

#define SH_LED_MMAP_SIZE (64*sizeof(uint16_t))

/*
 * Open the LEDs. Returns pointer to uint16_t[64] or NULL on error. Opening
 * more than once will return the existing mapping.
 */
uint16_t *sh_led_mmap_open(void);

/*
 * Close the LEDs. Closing the wrong mapping or closing a mapping more than
 * once will be ignored.
 */
void sh_led_mmap_close(uint16_t *);

/*
 * Sync the LEDs. EXPERIMENTAL! This might wait until updates to the mapping
 * have made it to the actual display. Or it might not. EXPERIMENTAL!
 */
void sh_led_mmap_sync(void);

#endif
