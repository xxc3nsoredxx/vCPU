// Source code for the vCPU itself

#include <stdlib.h>
#include "vcpu.h"

qword_t errors = 0x0000000000000000;
qword_t registers [0x30] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
int ram_size = 4;
int ram_mult = MiB;
void (*op []) (int, int, int) = {
    nop
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

void nop (int a unused, int b unused, int c unused) {
    asm volatile ("nop");
}
