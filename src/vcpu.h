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
typedef int_fast8_t    s_byte_t;
typedef int_fast16_t   s_word_t;
typedef int_fast32_t   s_dword_t ;
typedef int_fast64_t   s_qword_t ;

// errors
extern qword_t errors;

// register table (0x30 registers)
extern qword_t registers [];

// opcode table
extern void (*op []) (word_t, word_t, word_t);

// RAM
extern int ram_size;
extern int ram_mult;
qword_t *ram;

void init_cpu ();
void free_cpu ();

void nop    (word_t, word_t, word_t);
void addr   (word_t, word_t, word_t);
void addi   (word_t, word_t, word_t);
void sri    (word_t, word_t, word_t);
void sli    (word_t, word_t, word_t);
void srr    (word_t, word_t, word_t);
void slr    (word_t, word_t, word_t);

#endif
