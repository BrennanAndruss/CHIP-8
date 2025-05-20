# 🕹️ CHIP-8 Emulator

A CHIP-8 emulator written in C, featuring full instruction decoding, memory and register handling, SDL2-based graphics, and keyboard input mapping. 

---

## 🔧 Features

- Full implementation of the CHIP-8 instruction set
- Accurate memory, stack, and register management
- 64×32 monochrome display rendered with SDL2
- Configurable display scaling
- Keypad input mapped to modern keyboard layout
- Modular architecture with separate platform and emulation layers

---

## 🖥️ Controls

### Chip8 Keypad
|   |   |   |   |
|---|---|---|---|
| 1 | 2 | 3 | C |
| 4 | 5 | 6 | D |
| 7 | 8 | 9 | E |
| A | 0 | B | F |

### Keyboard Mapping
|   |   |   |   |
|---|---|---|---|
| 1 | 2 | 3 | 4 |
| Q | W | E | R |
| A | S | D | F |
| Z | X | C | V |

- `ESC` — Quit
- `SPACE` — Pause / Resume

---

## 📦 Build Instructions

### Prerequisites

- C compiler
- [CMake](https://cmake.org/)
- [SDL2](https://libsdl.org/)

### Build with CMake

```bash
mkdir build
cd build
cmake ..
make
```

### Run

```bash
./chip8-emulator <scale> <rom>
# Example:
./chip8-emulator 16 roms/pong.ch8
```

---

## 🔍 What I Learned

- Low level systems programming in C
- Core concepts in computer architecture and organization applied through emulation
- Configuring and developing in a Linux environment through WSL and VS Code

## 📚 Reference

- [Cowgod's Chip-8 Technical Reference](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM)
- [Guide to making a CHIP-8 emulator](https://tobiasvl.github.io/blog/write-a-chip-8-emulator/)
