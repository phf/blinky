CFLAGS=-std=c11 -Wall -Wextra -pedantic -O2 -D_POSIX_C_SOURCE=199309L
ALL=test_sh_led_mmap

all: $(ALL)

test_sh_led_mmap: test_sh_led_mmap.c sh_led_mmap.o

sh_led_mmap.o: sh_led_mmap.c sh_led_mmap.h

.PHONY: clean
clean:
	rm -rf *.o $(ALL)
