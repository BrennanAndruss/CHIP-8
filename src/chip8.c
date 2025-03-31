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
    // Fetch the next instruction as an opcode
    uint8_t MSB = chip8->memory[chip8->PC];
    uint8_t LSB = chip8->memory[chip8->PC + 1];
    uint16_t opcode = (MSB << 8) | LSB;

    // Increment the program counter
    chip8->PC += 1;

    // Decode and execute the instructions
    // Filter by the first half-byte
    switch (opcode & 0xF000)
    {
    case 0x0000:
        switch (opcode & 0x00FF)
        {
        case 0x00E0:
            // CLS
            op_0x00E0(chip8);
            break;
        case 0x00EE:
            // RET
            op_0x00EE(chip8);
            break;
        default:
            printf("Unrecognized opcode 0x%X\n", opcode);
            exit(EXIT_FAILURE);
        }
        break;

    case 0x1000:
        // JP
        op_0x1NNN(chip8);
        break;

    case 0x2000:
        // CALL
        op_0x2NNN(chip8);
        break;

    case 0x3000:
        // SE Vx, byte
        op_0x3XKK(chip8);
        break;

    case 0x4000:
        // SNE Vx, byte
        op_0x4XKK(chip8);
        break;

    case 0x5000:
        // SE Vx, Vy
        op_0x5XY0(chip8);
        break;

    case 0x6000:
        // LD Vx, byte
        op_0x6XKK(chip8);
        break;

    case 0x7000:
        // ADD Vx, byte
        op_0x7XKK(chip8);
        break;

    case 0x8000:
        switch (opcode & 0x000F)
        {
        case 0x0000:
            // LD
            op_0x8XY0(chip8);
            break;
        case 0x0001:
            // OR
            op_0x8XY1(chip8);
            break;
        case 0x0002:
            // AND
            op_0x8XY2(chip8);
            break;
        case 0x0003:
            // XOR
            op_0x8XY3(chip8);
            break;
        case 0x0004:
            // ADD
            op_0x8XY4(chip8);
            break;
        case 0x0005:
            // SUB
            op_0x8XY5(chip8);
            break;
        case 0x0006:
            op_0x8XY6(chip8);
            // SHR
            break;
        case 0x0007:
            op_0x8XY7(chip8);
            // SUBN
            break;
        case 0x000E:
            // SHL
            op_0x8XYE(chip8);
            break;
        default:
            printf("Unrecognized opcode 0x%X\n", opcode);
            exit(EXIT_FAILURE);
        }
        break;

    case 0xA000:
        // LD I, addr
        op_0xANNN(chip8);
        break;

    case 0xB000:
        // JP V0, addr
        op_0xBNNN(chip8);
        break;

    case 0xC000:
        // RND Vx, byte
        op_0xCXKK(chip8);
        break;

    case 0xD000:
        // DRW Vx, Vy, nibble
        op_0xDXYN(chip8);
        break;

    case 0xE000:
        switch (opcode & 0x00FF)
        {
        case 0x009E:
            // SKP
            break;
        case 0x00A1:
            // SKNP
            break;
        default:
            printf("Unrecognized opcode 0x%X\n", opcode);
            exit(EXIT_FAILURE);
        }
        break;

    case 0xF000:
        switch (opcode & 0x00FF)
        {
        case 0x0007:
            // LD Vx, DT
            break;
        case 0x000A:
            // LD Vx, K
            break;
        case 0x0015:
            // LD DT, Vx
            break;
        case 0x0018:
            // LD ST, Vx
            break;
        case 0x001E:
            // ADD I, Vx
            break;
        case 0x0029:
            // LD F, Vx
            break;
        case 0x0033:
            // LD B, Vx
            break;
        case 0x0055:
            // LD [I], Vx
            break;
        case 0x0065:
            // LD Vx, [I]
            break;
        default:
            printf("Unrecognized opcode 0x%X\n", opcode);
            exit(EXIT_FAILURE);
        }
        break;

    default:
        printf("Unrecognized opcode 0x%X\n", opcode);
        exit(EXIT_FAILURE);
    }
}
