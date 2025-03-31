#ifndef PLATFORM_H
#define PLATFORM_H

#include <SDL2/SDL.h>
#include "chip8.h"

#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH 1280

static const uint8_t KEYMAP[NUM_KEYS] =
    {
        SDL_SCANCODE_X, // 0
        SDL_SCANCODE_1, // 1
        SDL_SCANCODE_2, // 2
        SDL_SCANCODE_3, // 3
        SDL_SCANCODE_Q, // 4
        SDL_SCANCODE_W, // 5
        SDL_SCANCODE_E, // 6
        SDL_SCANCODE_A, // 7
        SDL_SCANCODE_S, // 8
        SDL_SCANCODE_D, // 9
        SDL_SCANCODE_Z, // A
        SDL_SCANCODE_C, // B
        SDL_SCANCODE_4, // C
        SDL_SCANCODE_R, // D
        SDL_SCANCODE_F, // E
        SDL_SCANCODE_V  // F
};

typedef struct Platform_t Platform;

struct Platform_t
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    uint32_t pixels[SCREEN_WIDTH * SCREEN_HEIGHT];
};

bool platform_init(Platform *platform);
void platform_update(Platform *platform, const uint8_t screen[SCREEN_WIDTH * SCREEN_HEIGHT]);
void platform_process_input(Chip8 *chip8);
void platform_cleanup(Platform *platform);

#endif // PLATFORM_H