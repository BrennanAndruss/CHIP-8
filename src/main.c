#include <stdio.h>
#include <stdlib.h>

#include "chip8.h"
#include "platform.h"

int main(int argc, char *argv[])
{
    if (argv[1] == NULL)
    {
        printf("Usage: ./chip8 path/to/rom\n");
        exit(EXIT_FAILURE);
    }

    Chip8 chip8;

    // Initialize the emulator and load ROM into memory
    chip8_init(&chip8);
    chip8_load_rom(&chip8, argv[1]);

    printf("ROM Loaded\n");
    return 0;
}