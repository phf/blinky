#include "sh_led_mmap.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

static uint16_t *mapped; /* mapped LEDs or NULL if not yet mapped */

static uint16_t *try_path(const char *path)
{
	struct fb_fix_screeninfo info;
	uint16_t *p = NULL;

	int fd = open(path, O_RDWR);
	if (fd == -1) {
		return NULL;
	}

	if (ioctl(fd, FBIOGET_FSCREENINFO, &info) == -1) {
		goto out;
	}

	if (strcmp(info.id, "RPi-Sense FB") != 0) {
		goto out;
	}

	p = mmap(NULL, SH_LED_MMAP_SIZE,
			PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if (p == MAP_FAILED) {
		p = NULL;
	}
out:
	close(fd); /* mmap will keep file open */
	return p;
}

/*
 * Somewhat simple-minded compared to scandir() but doesn't allocate extra
 * memory and can't fail in weird ways.
 */
uint16_t *sh_led_mmap_open(void)
{
	if (mapped != NULL) {
		return mapped;
	}

	char path[32];

	/*
	 * FB_MAX is 32 and name implies <= but documentation says 0 to 31
	 * see https://www.kernel.org/doc/Documentation/fb/framebuffer.txt
	 */
	for (int i = 0; i < FB_MAX; i++) {
		snprintf(path, sizeof(path), "/dev/fb%d", i);

		uint16_t *p = try_path(path);
		if (p != NULL) {
			mapped = p;
			return mapped;
		}
	}

	return NULL;
}

void sh_led_mmap_close(uint16_t *p)
{
	if (p != mapped || mapped == NULL) {
		return;
	}

	munmap(mapped, SH_LED_MMAP_SIZE);
	mapped = NULL;
}

void sh_led_mmap_sync(void)
{
	if (mapped == NULL) {
		return;
	}

	msync(mapped, SH_LED_MMAP_SIZE, MS_SYNC);
}
