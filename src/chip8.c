#include "chip8.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Initialize the system to the startup state
 */
void chip8_init(Chip8 *chip8)
{
    // Initialize special registers
    chip8->PC = START_ADDRESS;
    chip8->SP = 0;
    chip8->I = 0;

    // Clear display
    memset(chip8->screen, 0, sizeof(chip8->screen));

    // Clear stack
    memset(chip8->stack, 0, sizeof(chip8->stack));

    // Clear memory
    memset(chip8->memory, 0, sizeof(chip8->memory));

    // Clear registers
    memset(chip8->V, 0, sizeof(chip8->V));

    // Load fonts into memory
    for (int i = 0; i < FONTSET_SIZE; ++i)
    {
        chip8->memory[i] = FONTSET[i];
    }

    // Initialize timers
    chip8->delay_timer = 0;
    chip8->sound_timer = 0;

    // Set up keyboard
    memset(chip8->keypad, FALSE, sizeof(chip8->keypad));
}

void chip8_load_rom(Chip8 *chip8, const char *rom_filename)
{
    FILE *rom = fopen(rom_filename, "rb");
    if (rom == NULL)
    {
        perror("Failed to open ROM");
        exit(EXIT_FAILURE);
    }

    // Get the size of the ROM
    fseek(rom, 0, SEEK_END);
    long rom_size = ftell(rom);

    // Allocate memory for a buffer to hold the ROM
    uint8_t *rom_buffer = (uint8_t *)malloc(sizeof(uint8_t) * rom_size);
    if (rom_buffer == NULL)
    {
        perror("Failed to allocate memory for ROM");
        fclose(rom);
        exit(EXIT_FAILURE);
    }

    // Go to the beginning of the file and read the ROM into the buffer
    rewind(rom);
    size_t bytes_read = fread(rom_buffer, 1, rom_size, rom);
    if (bytes_read != rom_size)
    {
        perror("Failed to read full ROM");
        free(rom_buffer);
        fclose(rom);
        exit(EXIT_FAILURE);
    }
    fclose(rom);

    // Copy the ROM to CHIP-8 memory
    memcpy(&chip8->memory[START_ADDRESS], rom_buffer, rom_size);
    free(rom_buffer);
}

void chip8_cycle(Chip8 *chip8)
{
}
