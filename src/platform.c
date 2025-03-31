#include "platform.h"
#include <stdio.h>

bool platform_init(Platform *platform)
{
    // Initialize SDL video and event subsystems
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Could not initialize SDL: %s\n", SDL_GetError());
        return false;
    }

    platform->window = SDL_CreateWindow(
        "CHIP-8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!platform->window)
    {
        printf("Could not create SDL window: %s\n", SDL_GetError());
        return false;
    }

    platform->renderer = SDL_CreateRenderer(platform->window, -1, SDL_RENDERER_ACCELERATED);
    if (!platform->renderer)
    {
        printf("Could not create SDL renderer: %s\n", SDL_GetError());
        return false;
    }

    platform->texture = SDL_CreateTexture(
        platform->renderer, SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!platform->texture)
    {
        printf("Could not create SDL texture: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void platform_process_input(Chip8 *chip8)
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        SDL_Scancode sc = e.key.keysym.scancode;

        switch (e.type)
        {
        // Checks for the close window button
        case SDL_QUIT:
            chip8->is_running = false;
            break;

        case SDL_KEYDOWN:
            if (sc == SDL_SCANCODE_ESCAPE)
            {
                chip8->is_running = false;
                break;
            }

            if (sc == SDL_SCANCODE_SPACE)
            {
                chip8->is_paused = !chip8->is_paused;
                printf("Paused state: %d\n", chip8->is_paused);
                break;
            }

            // Checks each key by physical key positions and updates keypad state
            for (unsigned int i = 0; i < NUM_KEYS; i++)
            {
                if (sc == KEYMAP[i])
                {
                    chip8->keypad[i] = true;
                }
            }
            break;

        case SDL_KEYUP:
            // Checks each key by physical key positions and updates keypad state
            for (unsigned int i = 0; i < NUM_KEYS; i++)
            {
                if (sc == KEYMAP[i])
                {
                    chip8->keypad[i] = false;
                }
            }
            break;

        default:
            break;
        }
    }
}

void platform_cleanup(Platform *platform)
{
    SDL_DestroyTexture(platform->texture);
    SDL_DestroyRenderer(platform->renderer);
    SDL_DestroyWindow(platform->window);
    SDL_Quit();
}