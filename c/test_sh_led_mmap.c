#include "sh_led_mmap.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SECOND (1000 * 1000 * 1000)

int main(void)
{
	/* without sync() RPi 2 can do at most 81 before LEDs stall */
	struct timespec delay = {0, (long) (SECOND / 30)};

	uint16_t *leds = sh_led_mmap_open();
	if (leds == NULL) {
		exit(1);
	}

	/* flash using sync() */
	for (int i = 0; i < 15; i++) {
		memset(leds, 0xFF, SH_LED_MMAP_SIZE);
		sh_led_mmap_sync();
		memset(leds, 0x00, SH_LED_MMAP_SIZE);
		sh_led_mmap_sync();
	}

	/* flash using sleep() */
	for (int i = 0; i < 15; i++) {
		memset(leds, 0xFF, SH_LED_MMAP_SIZE);
		nanosleep(&delay, NULL);
		memset(leds, 0x00, SH_LED_MMAP_SIZE);
		nanosleep(&delay, NULL);
	}

	sh_led_mmap_close(leds);
	exit(0);
}
