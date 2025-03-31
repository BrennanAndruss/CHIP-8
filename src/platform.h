#ifndef PLATFORM_H
#define PLATFORM_H

#include <SDL2/SDL.h>
#include "chip8.h"

#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH 1280

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
void platform_process_input(uint8_t *keypad);
void platform_cleanup(Platform *platform);

#endif // PLATFORM_H