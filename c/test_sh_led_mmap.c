#include "sh_led_mmap.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void)
{
	struct timespec delay = {0, 4040000};

	uint16_t *leds = sh_led_mmap_open();
	if (leds == NULL) {
		exit(1);
	}

	for (int i = 0; i < 256; i++) {
		memset(leds, 0xff, SH_LED_MMAP_SIZE);
		nanosleep(&delay, NULL);
		memset(leds, 0x00, SH_LED_MMAP_SIZE);
		nanosleep(&delay, NULL);
	}

	sh_led_mmap_close(leds);
	exit(0);
}
