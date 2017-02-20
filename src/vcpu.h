#ifndef VCPU_H_20170216_221210
#define VCPU_H_20170216_221210

#include <inttypes.h>

#define asm __asm__
#define unused __attribute__ ((unused))

#define KiB 1024
#define MiB 1048576
#define GiB 1073741824

// types
typedef uint_fast8_t    byte_t;
typedef uint_fast16_t   word_t;
typedef uint_fast32_t   dword_t ;
typedef uint_fast64_t   qword_t ;

// errors
extern qword_t errors;

// register table (0x30 registers)
extern qword_t registers [0x30];

// opcode table
extern void (*op []) (int, int, int);

// RAM
extern int ram_size;
extern int ram_mult;
qword_t *ram;

void init_cpu ();
void free_cpu ();

void nop (int, int, int);

#endif
