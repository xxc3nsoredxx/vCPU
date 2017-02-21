// Source code for the vCPU itself

#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include "vcpu.h"

qword_t errors = 0x0000000000000000;
qword_t registers [] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
int ram_size = 4;
int ram_mult = MiB;
void (*op []) (word_t, word_t, word_t) = {
    nop, addr, addi, sri, sli, srr, slr
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

void addi (word_t r_result, word_t low2, word_t low1) {
    *(registers + r_result) += ((((qword_t) low2) << 16) & 0xFFFF0000) | low1;
}

void sri (word_t r_result, word_t low2, word_t low1) {
    *(registers + r_result) >>= ((((qword_t) low2) << 16) & 0xFFFF0000) | low1;
}

void sli (word_t r_result, word_t low2, word_t low1) {
    *(registers + r_result) <<= ((((qword_t) low2) << 16) & 0xFFFF0000) | low1;
}

void srr (word_t r_result, word_t r1, word_t r2) {
    *(registers + r_result) = *(registers + r1) >> *(registers + r2);
}

void slr (word_t r_result, word_t r1, word_t r2) {
    *(registers + r_result) = *(registers + r1) << *(registers + r2);
}
