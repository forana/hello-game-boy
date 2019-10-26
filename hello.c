// I'm sorry

#include <stdio.h>
#include <gb/gb.h>
#include <gb/cgb.h>
#include <gb/font.h>
#include <gb/console.h>
#include <gb/drawing.h>

// pew pew pew
void pew() {
    NR52_REG = 0x80;
    NR51_REG = 0x11;
    NR50_REG = 0x77;

    NR10_REG = 0x1E;
    NR11_REG = 0x10;
    NR12_REG = 0xF3;
    NR13_REG = 0x00;
    NR14_REG = 0x87;
}

void init_sound() {
    NR52_REG = 0x83U;
    NR51_REG = 0x00U;
    NR50_REG = 0x77U;

    NR24_REG = 0x87U;
    NR22_REG = 0xffU;
    NR21_REG = 0xbfU;

    NR14_REG = 0x87U;
    NR12_REG = 0xffU;
    NR11_REG = 0xbfU;
    NR10_REG = 0x04U;
}

void play_pitch(UWORD hz) {
    // why does this need to be done twice?
    NR24_REG = 0x87U;
    // sound on, I guess
    NR51_REG = 0x33U;
    // play this in channel 2?
    NR23_REG = hz;
}

// void stop_sound() {
//     // sound off
//     NR51_REG = 0x00U;
// }

const UWORD NOTES[] = {
    0x10U,
    0x30U,
    0x20U,
    0x40U,
    0x10U,
    0x30U,
    0x20U,
    0x60U,
    0x10U,
    0x30U,
    0x20U,
    0x80U,
    0x10U,
    0x30U,
    0x20U,
    0x60U,
};

const int NOTE_COUNT = 16;

// it's a PUN
void delA(int l) {
    int i;
    i = 0;
    while (i < l) {
        if (joypad() & J_A) {
            printf("A");
            play_pitch(0xCDU);
        }
        delay(10);
        i+=10;
    }
}

void main(void) {
    font_t ibm_font;
    int i, j;

    // cgb_compatibility();
    init_sound();

    font_init();
    ibm_font = font_load(font_ibm);
    font_set(ibm_font);

    printf("\n");
    printf("Let's GO\n\n");
    printf("There are WORDS\n  on the SCREEN\n");
    printf("\nplease don't press A\n");

    delay(1000);
    printf("3 ");
    pew();
    delay(1000);
    printf("2 ");
    pew();
    delay(1000);
    printf("1\n");
    pew();
    delay(1000);

    i = 0;
    while (1) {
        play_pitch(NOTES[i]);
        delA(100);
        if (i % 4 == 0) {
            j = 0;
            while (j < i) {
                printf(" ");
                j++;
            }
            printf("boop\n");
        }
        i++;
        if (i >= NOTE_COUNT) {
            i = 0;
        }
    }
}

