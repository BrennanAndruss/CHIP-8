#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "chip8.h"

// CLS
void op_0x00E0(Chip8 *chip8);

// RET
void op_0x00EE(Chip8 *chip8);

// JP addr
void op_0x1NNN(Chip8 *chip8);

// CALL addr
void op_0x2NNN(Chip8 *chip8);

// SE Vx, byte
void op_0x3XKK(Chip8 *chip8);

// SNE Vx, byte
void op_0x4XKK(Chip8 *chip8);

// SE Vx, Vy
void op_0x5XY0(Chip8 *chip8);

// LD Vx, byte
void op_0x6XKK(Chip8 *chip8);

// ADD Vx, byte
void op_0x7XKK(Chip8 *chip8);

// LD Vx, Vy
void op_0x8XY0(Chip8 *chip8);

// OR Vx, Vy
void op_0x8XY1(Chip8 *chip8);

// AND Vx, Vy
void op_0x8XY2(Chip8 *chip8);

// XOR Vx, Vy
void op_0x8XY3(Chip8 *chip8);

// ADD Vx, Vy
void op_0x8XY4(Chip8 *chip8);

// SUB Vx, Vy
void op_0x8XY5(Chip8 *chip8);

// SHR Vx
void op_0x8XY6(Chip8 *chip8);

// SUBN Vx, Vy
void op_0x8XY7(Chip8 *chip8);

// SHL Vx
void op_0x8XYE(Chip8 *chip8);

// SNE Vx, Vy
void op_0x9XY0(Chip8 *chip8);

// LD I, addr
void op_0xANNN(Chip8 *chip8);

// JP V0, addr
void op_0xBNNN(Chip8 *chip8);

// RND Vx, byte
void op_0xCXKK(Chip8 *chip8);

// DRW Vx, Vy, nibble
void op_0xDXYN(Chip8 *chip8);

// SKP Vx
void op_0xEX9E(Chip8 *chip8);

// SKNP Vx
void op_0xEXA1(Chip8 *chip8);

// LD Vx, DT
void op_0xFX07(Chip8 *chip8);

// LD Vx, K
void op_0xFX0A(Chip8 *chip8);

// LD DT, Vx
void op_0xFX15(Chip8 *chip8);

// LD ST, Vx
void op_0xFX18(Chip8 *chip8);

// ADD I, Vx
void op_0xFX1E(Chip8 *chip8);

// LD F, Vx
void op_0xFX29(Chip8 *chip8);

// LD B, Vx
void op_0xFX33(Chip8 *chip8);

// LD [I], Vx
void op_0xFX55(Chip8 *chip8);

// LD Vx, [I]
void op_0xFX65(Chip8 *chip8);

#endif // INSTRUCTIONS_H
