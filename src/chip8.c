#include "chip8.h"

#include <string.h>

/*
 * Initialize the system to the startup state
 */
chip8_init(Chip8 *chip8)
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

chip8_load_rom(Chip8 *chip8, const char *rom_filename)
{
    
}

chip8_cycle(Chip8 *chip8)
{
}
