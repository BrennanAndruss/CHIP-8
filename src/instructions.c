#include "instructions.h"

#include <string.h>

/*
 * Opcode 00E0: CLS
 * Clear the display by setting all pixels to 'off'.
 */
void op_0x00E0(Chip8 *chip8)
{
    memset(chip8->screen, 0, sizeof(chip8->screen));
}

// RET
void op_0x00EE(Chip8 *chip8) {};

/*
 * Opcode 1NNN: JP addr
 * Jump to location nnn.
 */
void op_0x1NNN(Chip8 *chip8)
{
    uint16_t address = chip8->current_op & 0x0FFF;
    chip8->PC = address;
}

// CALL addr
void op_0x2NNN(Chip8 *chip8) {};

// SE Vx, byte
void op_0x3XKK(Chip8 *chip8) {};

// SNE Vx, byte
void op_0x4XKK(Chip8 *chip8) {};

// SE Vx, Vy
void op_0x5XY0(Chip8 *chip8) {};

/*
 * Opcode 6XKK: LD Vx, byte
 * Set Vx = kk.
 */
void op_0x6XKK(Chip8 *chip8)
{
    uint8_t x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t kk = chip8->current_op & 0x00FF;
    chip8->V[x] = kk;
}

/*
 * Opcode 7XKK: ADD Vx, byte
 * Adds the value kk to the value of register Vx,
 * then stores the result in Vx.
 */
void op_0x7XKK(Chip8 *chip8)
{
    uint8_t x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t kk = chip8->current_op & 0x00FF;
    chip8->V[x] += kk;
}

// LD Vx, Vy
void op_0x8XY0(Chip8 *chip8) {};

// OR Vx, Vy
void op_0x8XY1(Chip8 *chip8) {};

// AND Vx, Vy
void op_0x8XY2(Chip8 *chip8) {};

// XOR Vx, Vy
void op_0x8XY3(Chip8 *chip8) {};

// ADD Vx, Vy
void op_0x8XY4(Chip8 *chip8) {};

// SUB Vx, Vy
void op_0x8XY5(Chip8 *chip8) {};

// SHR Vx
void op_0x8XY6(Chip8 *chip8) {};

// SUBN Vx, Vy
void op_0x8XY7(Chip8 *chip8) {};

// SHL Vx
void op_0x8XYE(Chip8 *chip8) {};

// SNE Vx, Vy
void op_0x9XY0(Chip8 *chip8) {};

// LD I, addr
/*
 * Opcode ANNN: LD I, addr
 * Set the value of register I to nnn.
 */
void op_0xANNN(Chip8 *chip8)
{
    uint16_t nnn = chip8->current_op & 0x0FFF;
    chip8->I = nnn;
}

// JP V0, addr
void op_0xBNNN(Chip8 *chip8) {};

// RND Vx, byte
void op_0xCXKK(Chip8 *chip8) {};

// DRW Vx, Vy, nibble
/*
 * Opcode DXYN: DRW Vx, Vy, nibble
 * Display n-byte sprite starting at memory location I at (Vx, Vy),
 * set VF = collision.
 */
void op_0xDXYN(Chip8 *chip8)
{
    uint8_t x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t y = (chip8->current_op & 0x00F0) >> 4;
    uint8_t n = chip8->current_op & 0x000F;

    // Get the x and y coordinates of the sprite from the x and y registers
    uint8_t x_pos = chip8->V[x] & 63;
    uint8_t y_pos = chip8->V[y] & 31;

    // Initialize collision register to false
    chip8->V[0xF] = 0;

    // Loop through the n rows of the sprite
    for (unsigned int row = 0; row < n; row++)
    {
        // Get the nth byte of sprite data
        uint8_t spriteByte = chip8->memory[chip8->I + row];

        // Go through each pixel in the sprite row
        for (unsigned int col = 0; col < 8; col++)
        {
            uint8_t sprite_pixel = spriteByte & (0x80 >> col);

            // Check if the sprite pixel is on
            if (!sprite_pixel)
                continue;

            uint32_t *screen_pixel =
                &chip8->screen[(y_pos + row) * SCREEN_WIDTH + (x_pos + col)];

            // Set the collision register to true if the screen pixel is also on
            if (*screen_pixel)
                chip8->V[0xF] = 1;

            // Flip the pixel state
            *screen_pixel ^= 0xFFFFFFFF;
        }
    }
}

// SKP Vx
void op_0xEX9E(Chip8 *chip8) {};

// SKNP Vx
void op_0xEXA1(Chip8 *chip8) {};

// LD Vx, DT
void op_0xFX07(Chip8 *chip8) {};

// LD Vx, K
void op_0xFX0A(Chip8 *chip8) {};

// LD DT, Vx
void op_0xFX15(Chip8 *chip8) {};

// LD ST, Vx
void op_0xFX18(Chip8 *chip8) {};

// ADD I, Vx
void op_0xFX1E(Chip8 *chip8) {};

// LD F, Vx
void op_0xFX29(Chip8 *chip8) {};

// LD B, Vx
void op_0xFX33(Chip8 *chip8) {};

// LD [I], Vx
void op_0xFX55(Chip8 *chip8) {};

// LD Vx, [I]
void op_0xFX65(Chip8 *chip8) {};