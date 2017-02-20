// Main driver for the cpu emulator

#include <inttypes.h>
#include <stdio.h>
#include "vcpu.h"

void print_help () {
    printf ("Usage: \n");
    printf ("    vcpu.exe [executable name]\n");
}

void free_all (FILE *input) {
    printf ("Error Flags: 0x%016lX\n", (long unsigned int) errors);
    free_cpu ();
    fclose (input);
}

void dump_ram (int qwords) {
    for (int cx = 0; cx < qwords; cx++)
        printf ("%016"PRIx64"\n", *(ram + cx));
}

void dump_registers () {
    char separator;
    for (int cx = 0; cx < 0x30; cx++) {
        if (cx % 4 == 3)
            separator = '\n';
        else
            separator = ' ';
        printf ("r%02d: 0x%016"PRIx64"%c", cx, *(registers + cx), separator);
    }
}

int main (int argc, char **argv) {
    // check args
    if (argc != 2) {
        print_help ();
        return -1;
    }

    FILE *in = fopen (*(argv + 1), "r");
    if (!in) {
        printf ("[-] Error opening file: %s\n", *(argv + 1));
        return -1;
    }

    init_cpu ();

    // test for errors
    if (errors) {
        if (errors ^ 0x0000000000000001)
            printf ("[-] Error initializing RAM\n");

        free_all (in);
        return -1;
    }

    // read file into RAM
    char temp;
    int qwords = 0;
    for (int cx = 0; ; cx++) {
        // read first byte
        fread (&temp, 1, 1, in);
        // if EOF or error, break
        if (feof (in) || ferror (in))
            break;
        *(ram + cx) |= temp;
        *(ram + cx) = *(ram + cx) << 8;
        // read second byte
        fread (&temp, 1, 1, in);
        *(ram + cx) |= temp;
        *(ram + cx) = *(ram + cx) << 8;
        // read third byte
        fread (&temp, 1, 1, in);
        *(ram + cx) |= temp;
        *(ram + cx) = *(ram + cx) << 8;
        // read fourth byte
        fread (&temp, 1, 1, in);
        *(ram + cx) |= temp;
        *(ram + cx) = *(ram + cx) << 8;
        // read fifth byte
        fread (&temp, 1, 1, in);
        *(ram + cx) |= temp;
        *(ram + cx) = *(ram + cx) << 8;
        // read sixth byte
        fread (&temp, 1, 1, in);
        *(ram + cx) |= temp;
        *(ram + cx) = *(ram + cx) << 8;
        // read seventh byte
        fread (&temp, 1, 1, in);
        *(ram + cx) |= temp;
        *(ram + cx) = *(ram + cx) << 8;
        // read eighth byte
        fread (&temp, 1, 1, in);
        *(ram + cx) |= temp;
        qwords++;
    }

    // test if file errored while being read
    if (ferror (in)) {
        printf ("[-] Error reading file into RAM\n");

        free_all (in);
        return -1;
    }

    qword_t inst;       // Stores the instruction from RAM
    int op_index;       // Stores the index into the opcode array
    word_t p1, p2, p3;  // Stores parameters
    printf ("RAM: %d bytes\n", ram_size * ram_mult);
    printf ("Max instrutions: %d\n", (ram_size * ram_mult) / 8);

    // Loop through the RAM, executing instructions as we go
    for (int ram_index = 0; ram_index < (ram_size * ram_mult) / 8; ram_index++) {
        inst = *(ram + ram_index);
        p3 = inst & 0xFFFF;                 // Extract parameter 1
        inst >>= 16;
        p2 = inst & 0xFFFF;                 // Extract parameter 2
        inst >>= 16;
        p1 = inst & 0xFFFF;                 // Extract parameter 3
        inst >>= 16;
        op_index = inst & 0xFFFF;           // Extract the index
        (*(op + op_index)) (p1, p2, p3);    // Execute instruction
    }

    printf ("Registers:\n");
    dump_registers ();

    free_all (in);
    return 0;
}
