// Source code for the vCPU itself

#include <stdlib.h>
#include <stdio.h>
#include "vcpu.h"

qword_t errors = 0x0000000000000000;
qword_t registers [] = {
    0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
int ram_size = 4;
int ram_mult = MiB;
void (*op []) (word_t, word_t, word_t) = {
    nop, addr
};

void init_cpu () {
    // init RAM
    ram = (qword_t *) calloc (ram_size * ram_mult, sizeof (qword_t));
    if (!ram)
        errors |= 0x0000000000000001;
}

void free_cpu () {
    if (errors ^ 0x0000000000000001)
        free (ram);
}

void nop (word_t a unused, word_t b unused, word_t c unused) {
    asm volatile ("nop");
}

void addr (word_t r_result, word_t r1, word_t r2) {
    *(registers + r_result) = *(registers + r1) + *(registers + r2);
}
