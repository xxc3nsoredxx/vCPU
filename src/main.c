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

void dump (int qwords) {
    for (int cx = 0; cx < qwords; cx++)
        printf ("%016"PRIx64"\n", *(ram + cx));
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
        //*(ram + cx) &= 0xFF00;
        // read second byte
        fread (&temp, 1, 1, in);
        *(ram + cx) |= temp;
        *(ram + cx) = *(ram + cx) << 8;
        //*(ram + cx) &= 0xFFFF00;
        // read third byte
        fread (&temp, 1, 1, in);
        *(ram + cx) |= temp;
        *(ram + cx) = *(ram + cx) << 8;
        //*(ram + cx) &= 0xFFFFFF00;
        // read fourth byte
        fread (&temp, 1, 1, in);
        *(ram + cx) |= temp;
        *(ram + cx) = *(ram + cx) << 8;
        //*(ram + cx) &= 0xFFFFFFFF00;
        // read fifth byte
        fread (&temp, 1, 1, in);
        *(ram + cx) |= temp;
        *(ram + cx) = *(ram + cx) << 8;
        //*(ram + cx) &= 0xFFFFFFFFFF00;
        // read sixth byte
        fread (&temp, 1, 1, in);
        *(ram + cx) |= temp;
        *(ram + cx) = *(ram + cx) << 8;
        //*(ram + cx) &= 0xFFFFFFFFFFFF00;
        // read seventh byte
        fread (&temp, 1, 1, in);
        *(ram + cx) |= temp;
        *(ram + cx) = *(ram + cx) << 8;
        //*(ram + cx) &= 0xFFFFFFFFFFFFFF00;
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

    dump (qwords);

    free_all (in);
    return 0;
}
