#ifndef CHIP8_H
#define CHIP8_H

#include <stdint.h>
#include <stdbool.h>

#define NUM_REGISTERS 16
#define TOTAL_RAM 4096
#define STACK_SIZE 16
#define NUM_KEYS 16
#define FONTSET_SIZE 80

#define FONTSET_START_ADDRESS 0x500
#define START_ADDRESS 0x200

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

static const uint8_t FONTSET[FONTSET_SIZE] =
    {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

typedef struct Chip8_t Chip8;

struct Chip8_t
{
    uint8_t memory[TOTAL_RAM];
    uint16_t stack[STACK_SIZE];

    uint8_t V[NUM_REGISTERS];
    uint16_t I;  // Index register
    uint16_t PC; // Program counter
    uint8_t SP;  // Stack pointer
    uint8_t delay_timer;
    uint8_t sound_timer;

    uint8_t keypad[NUM_KEYS];
    uint32_t screen[SCREEN_WIDTH * SCREEN_HEIGHT];

    uint16_t current_op;

    // Execution control flags
    bool is_running;
    bool is_paused;
};

void chip8_init(Chip8 *chip8);
void chip8_load_rom(Chip8 *chip8, const char *rom_filename);
void chip8_cycle(Chip8 *chip8);

#endif // CHIP8_H
