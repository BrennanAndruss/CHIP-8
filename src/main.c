#include <stdio.h>
#include <stdlib.h>

#include "chip8.h"
#include "platform.h"

int main(int argc, char *argv[])
{
    // Validate and process arguments
    if (argc != 3)
    {
        printf("Usage: %s <scale> <rom>\n", argv[0]);
        return 1;
    }

    char *endptr;
    int screenScale = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0')
    {
        printf("Invalid character in scale value: %c\n", *endptr);
        return 1;
    }

    const char *rom_filename = argv[2];

    // Set up the window
    Platform platform;
    if (!platform_init(&platform, SCREEN_WIDTH * screenScale, SCREEN_HEIGHT * screenScale))
        return 1;

    // Initialize the emulator and load ROM into memory
    Chip8 chip8;
    chip8_init(&chip8);
    chip8_load_rom(&chip8, rom_filename);

    int pitch = sizeof(chip8.screen[0]) * SCREEN_WIDTH;

    // Main loop
    while (chip8.is_running)
    {
        platform_process_input(&chip8);

        chip8_cycle(&chip8);
        platform_update(&platform, &chip8, pitch);

        SDL_Delay(2);
    }

    platform_cleanup(&platform);
    return 0;
}