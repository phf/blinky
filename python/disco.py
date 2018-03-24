"""
Light up frames randomly in a Disco style.
"""

import sense_hat as S
import random as R

s = S.SenseHat()

def clear():
    for x in range(8):
        for y in range(8):
            s.set_pixel(x, y, 0, 0, 0)

def frame():
    for x in range(8):
        for y in range(8):
            r = R.randint(0, 255)
            g = R.randint(0, 255)
            b = R.randint(0, 255)
            s.set_pixel(x, y, r, g, b)

def main():
    try:
        print("Blinking...")
        while True:
            frame()
    except KeyboardInterrupt:
        clear()
        print("Stopped...")

if __name__ == "__main__":
    main()
