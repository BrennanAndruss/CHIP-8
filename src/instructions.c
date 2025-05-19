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

/*
 * Opcode 00EE: RET
 * Return from a subroutine.
 */
void op_0x00EE(Chip8 *chip8)
{
    chip8->SP--;
    chip8->PC = chip8->stack[chip8->SP];
}

/*
 * Opcode 1NNN: JP addr
 * Jump to location nnn.
 */
void op_0x1NNN(Chip8 *chip8)
{
    uint16_t address = chip8->current_op & 0x0FFF;
    chip8->PC = address;
}

/*
 * Opcode 2NNN: CALL addr
 * Call subroutine at nnn.
 */
void op_0x2NNN(Chip8 *chip8)
{
    uint16_t address = chip8->current_op & 0x0FFF;
    chip8->stack[chip8->SP] = chip8->PC;
    chip8->SP++;
    chip8->PC = address;
}

/*
 * Opcode 3XKK: SE Vx, byte
 * Skip next instruction if Vx = kk.
 */
void op_0x3XKK(Chip8 *chip8)
{
    uint8_t x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t kk = chip8->current_op & 0x00FF;
    if (chip8->V[x] == kk)
    {
        chip8->PC += 2;
    }
}

/*
 * Opcode 4XKK: SNE Vx, byte
 * Skip next instruction if Vx != kk.
 */
void op_0x4XKK(Chip8 *chip8)
{
    uint8_t x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t kk = chip8->current_op & 0x00FF;
    if (chip8->V[x] != kk)
    {
        chip8->PC += 2;
    }
}

/*
 * Opcode 5XY0: SE Vx, Vy
 * Skip next instruction if Vx = Vy.
 */
void op_0x5XY0(Chip8 *chip8)
{
    uint8_t x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t y = (chip8->current_op & 0x00F0) >> 4;
    if (chip8->V[x] == chip8->V[y])
    {
        chip8->PC += 2;
    }
}

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
 * Set Vx = Vx + kk.
 */
void op_0x7XKK(Chip8 *chip8)
{
    uint8_t x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t kk = chip8->current_op & 0x00FF;
    chip8->V[x] += kk;
}

/*
 * Opcode 8XY0: LD Vx, Vy
 * Set Vx = Vy.
 */
void op_0x8XY0(Chip8 *chip8)
{
    uint8_t x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t y = (chip8->current_op & 0x00F0) >> 4;
    chip8->V[x] = chip8->V[y];
}

/*
 * Opcode 8XY1: OR Vx, Vy
 * Set Vx = Vx OR Vy.
 */
void op_0x8XY1(Chip8 *chip8)
{
    uint8_t x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t y = (chip8->current_op & 0x00F0) >> 4;
    chip8->V[x] = chip8->V[x] | chip8->V[y];
}

/*
 * Opcode 8XY2: AND Vx, Vy
 * Set Vx = Vx AND Vy.
 */
void op_0x8XY2(Chip8 *chip8)
{
    uint8_t x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t y = (chip8->current_op & 0x00F0) >> 4;
    chip8->V[x] = chip8->V[x] | chip8->V[y];
}

/*
 * Opcode 8XY3: XOR Vx, Vy
 * Set Vx = Vx XOR Vy.
 */
void op_0x8XY3(Chip8 *chip8)
{
    uint8_t x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t y = (chip8->current_op & 0x00F0) >> 4;
    chip8->V[x] = chip8->V[x] ^ chip8->V[y];
}

/*
 * Opcode 8XY4: ADD Vx, Vy
 * Set Vx = Vx + Vy, set VF = carry.
 */
void op_0x8XY4(Chip8 *chip8)
{
    uint8_t x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t y = (chip8->current_op & 0x00F0) >> 4;
    uint16_t sum = chip8->V[x] + chip8->V[y];

    // Set carry flag and store lowest 8 bits of sum
    chip8->V[0xF] = sum > 255;
    chip8->V[x] = sum & 0xFF;
}

/*
 * Opcode 0x8XY5: SUB Vx, Vy
 * Set Vx = Vx - Vy, set VF = NOT borrow.
 */
void op_0x8XY5(Chip8 *chip8)
{
    uint8_t x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t y = (chip8->current_op & 0x00F0) >> 4;

    // Set borrow flag and store difference
    chip8->V[0xF] = chip8->V[x] > chip8->V[y];
    chip8->V[x] -= chip8->V[y];
}

/*
 * Opcode 0x8XY6: SHR Vx
 * Set Vx = Vx >> 1, set VF = LSb of Vx.
 */
void op_0x8XY6(Chip8 *chip8)
{
    uint8_t x = (chip8->current_op & 0x0F00) >> 8;
    chip8->V[0xF] = chip8->V[x] & 1;
    chip8->V[x] >>= 1;
}

/*
 * Opcode 0x8XY7: SUBN Vx, Vy
 * Set Vx = Vy - Vx, set VF = NOT borrow.
 */
void op_0x8XY7(Chip8 *chip8)
{
    uint8_t x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t y = (chip8->current_op & 0x00F0) >> 4;

    // Set borrow flag and store difference
    chip8->V[0xF] = chip8->V[y] > chip8->V[x];
    chip8->V[x] = chip8->V[y] - chip8->V[x];
}

/*
 * Opcode 0x8XYE: SHL Vx
 * Set Vx = Vx << 1, set VF = MSb of Vx.
 */
void op_0x8XYE(Chip8 *chip8)
{
    uint8_t x = (chip8->current_op & 0x0F00) >> 8;
    chip8->V[0xF] = chip8->V[x] & 0x80;
    chip8->V[x] <<= 1;
}

/*
 * Opcode 9XY0: SNE Vx, Vy
 * Skip next instruction if Vx != Vy.
 */
void op_0x9XY0(Chip8 *chip8)
{
    uint8_t x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t y = (chip8->current_op & 0x00F0) >> 4;
    if (chip8->V[x] != chip8->V[y])
    {
        chip8->PC += 2;
    }
};

/*
 * Opcode ANNN: LD I, addr
 * Set the value of register I to nnn.
 */
void op_0xANNN(Chip8 *chip8)
{
    uint16_t nnn = chip8->current_op & 0x0FFF;
    chip8->I = nnn;
}

/*
 * Opcode BNNN: JP V0, addr
 * Jump to location nnn + V0.
 */
void op_0xBNNN(Chip8 *chip8)
{
    uint16_t address = chip8->current_op & 0x0FFF;
    chip8->PC = address + chip8->V[0];
}

/*
 * Opcode CXKK: RND Vx, byte
 * Set Vx = random byte AND kk.
 */
void op_0xCXKK(Chip8 *chip8)
{
    uint8_t x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t kk = chip8->current_op & 0x00FF;
    uint8_t random_val = rand() % 256;
    chip8->V[x] = random_val & kk;
}

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

/*
 * Opcode EX9E: SKP Vx
 * Skip next instruction if key with the value of Vx is pressed.
 */
void op_0xEX9E(Chip8 *chip8)
{
    uint8_t x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t key = chip8->V[x];
    if (chip8->keypad[key])
    {
        chip8->PC += 2;
    }
}

/*
 * Opcode EXA1: SKNP Vx
 * Skip next instruction if key with the value of Vx is not pressed.
 */
void op_0xEXA1(Chip8 *chip8)
{
    uint8_t x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t key = chip8->V[x];
    if (!chip8->keypad[key])
    {
        chip8->PC += 2;
    }
}

/*
 * Opcode FX07: LD Vx, DT
 * Set Vx = delay timer value.
 */
void op_0xFX07(Chip8 *chip8)
{
    uint8_t x = (chip8->current_op & 0x0F00) >> 8;
    chip8->V[x] = chip8->delay_timer;
}

/*
 * Opcode FX0A: LD Vx, K
 * Wait for a key press, store the value of the key in Vx.
 */
void op_0xFX0A(Chip8 *chip8)
{
    uint8_t x = (chip8->current_op & 0x0F00) >> 8;

    // Check each key for a key input
    for (int i = 0; i < NUM_KEYS; i++)
    {
        if (chip8->keypad[i])
        {
            chip8->V[x] = i;

            // Return to resume program execution
            return;
        }
    }

    // Decrement the PC, blocking the instruction
    chip8->PC -= 2;
}

/*
 * Opcode FX15: LD DT, Vx
 * Set delay timer = Vx.
 */
void op_0xFX15(Chip8 *chip8)
{
    uint8_t x = (chip8->current_op & 0x0F00) >> 8;
    chip8->delay_timer = chip8->V[x];
}

/*
 * Opcode FX18: LD ST, Vx
 * Set sound timer = Vx.
 */
void op_0xFX18(Chip8 *chip8)
{
    uint8_t x = (chip8->current_op & 0x0F00) >> 8;
    chip8->sound_timer = chip8->V[x];
}

/*
 * Opcode FX1E: ADD I, Vx
 * Set I = I + Vx.
 */
void op_0xFX1E(Chip8 *chip8)
{
    uint8_t x = (chip8->current_op & 0x0F00) >> 8;
    chip8->I += chip8->V[x];
}

/*
 * Opcode FX29: LD F, Vx
 * Set I = location of sprite for digit Vx.
 */
void op_0xFX29(Chip8 *chip8)
{
    uint8_t x = (chip8->current_op & 0x0F00) >> 8;
    chip8->I = 0x5 * chip8->V[x];
}

/*
 * Opcode 0xFX33: LD B, Vx
 * Store BCD representation of Vx in memory locations I,
 * I+1, and I+2.
 */
void op_0xFX33(Chip8 *chip8)
{
    uint8_t x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t val = chip8->V[x];

    chip8->memory[chip8->I] = val / 100;
    chip8->memory[chip8->I + 1] = val / 10 % 10;
    chip8->memory[chip8->I + 2] = val % 10;
}

/*
 * Opcode FX55: LD [I], Vx
 * Store registers V0 through Vx in memory starting at location I.
 */
void op_0xFX55(Chip8 *chip8)
{
    uint8_t x = (chip8->current_op & 0x0F00) >> 8;

    for (int i = 0; i < x; i++)
    {
        chip8->memory[chip8->I + i] = chip8->V[i];
    }
}

/*
 * Opcode FX65: LD Vx, [I]
 * Read registers V0 through Vx from memory starting at location I.
 */
void op_0xFX65(Chip8 *chip8)
{
    uint8_t x = (chip8->current_op & 0x0F00) >> 8;

    for (int i = 0; i < x; i++)
    {
        chip8->V[i] = chip8->memory[chip8->I + i];
    }
}