#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#include <SDL2/SDL.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Rect rect;
int open = 1;

static void mainloop(void)
{
    if (!open)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        #ifdef EMSCRIPTEN
        emscripten_cancel_main_loop();
        #else
        exit(0);
        #endif
    }

    SDL_Event evnt;
    while (SDL_PollEvent(&evnt))
    {
        if (evnt.type == SDL_QUIT)
            open = 0;
        else if (evnt.type == SDL_KEYDOWN)
        {
            switch (evnt.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                open = 0;
                break;
            }
        }
        break;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 600, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    rect.x = 50;
    rect.y = 50;
    rect.w = 100;
    rect.h = 100;

    #ifdef EMSCRIPTEN
    printf("emscripten\n");
    emscripten_set_main_loop(mainloop, 0, 1);
    #else
    printf("native\n");
    while (1) { mainloop(); }
    #endif

    return EXIT_SUCCESS;
}