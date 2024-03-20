#include "Module.hpp"

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#include <vector>
#include <iostream>

/* Global context of the module */
static ModuleContext ctx;

static SDL_FPoint worldToView(const SDL_FPoint world)
{
    int w, h;
    SDL_GetWindowSize(ctx.window, &w, &h);
    SDL_FPoint view;
    view.x = world.x - ctx.camera.x + w/2;
    view.y = world.y - ctx.camera.y + h/2;
    return view;
}

/* Render the grid based on the context */
static void renderGrid()
{
    int w, h;
    SDL_GetWindowSize(ctx.window, &w, &h);
    double startX = ctx.camera.x - w/2;
    double startY = ctx.camera.y - h/2;
    double endX = startX + w;
    double endY = startY + h;
    double ppu = ctx.ppu;
    
    //Vertical lines
    for (double x = ppu * floor(startX / ppu); x <= ppu * ceil(endX / ppu); x += ppu)
    {
        SDL_FPoint start;
        start.x = x;
        start.y = startY;
        SDL_FPoint end;
        end.x = x;
        end.y = endY;

        SDL_SetRenderDrawColor(ctx.renderer, 100, 100, 100, 255);
        if (x == 0) SDL_SetRenderDrawColor(ctx.renderer, 0xe9, 0x9a, 0x0a, 255); // Y axis

        start = worldToView(start);
        end = worldToView(end);
        SDL_RenderDrawLineF(ctx.renderer, start.x, start.y, end.x, end.y);
    }

    //Horizontal lines
    for (double y = ppu * floor(startY / ppu); y <= ppu * ceil(endY / ppu); y += ppu)
    {
        SDL_FPoint start;
        start.x = startX;
        start.y = y;
        SDL_FPoint end;
        end.x = endX;
        end.y = y;

        SDL_SetRenderDrawColor(ctx.renderer, 100, 100, 100, 255);
        if (y == 0) SDL_SetRenderDrawColor(ctx.renderer, 0xe9, 0x9a, 0x0a, 255); // X axis

        start = worldToView(start);
        end = worldToView(end);
        SDL_RenderDrawLineF(ctx.renderer, start.x, start.y, end.x, end.y);
    }
}

static void renderFunction()
{
    int w, h;
    SDL_GetWindowSize(ctx.window, &w, &h);
    double startX = ctx.camera.x - w/2;
    double endX = startX + w;
    double ppu = ctx.ppu;
    double dx = ppu / 10;

    std::vector<SDL_FPoint> lines;

    for (double x = dx * floor(startX / dx); x <= dx * ceil(endX / dx); x += dx)
    {
        SDL_FPoint point;
        point.x = x;
        point.y = -ppu * cos(x / ppu);
        point = worldToView(point);
        lines.push_back(point);
    }

    SDL_SetRenderDrawColor(ctx.renderer, 0x27, 0x4c, 0x43, 255);
    SDL_RenderDrawLinesF(ctx.renderer, lines.data(), lines.size());
}

static void mainloop(void)
{
    if (!ctx.open)
    {
        if (ctx.renderer != NULL) SDL_DestroyRenderer(ctx.renderer);
        if (ctx.window != NULL) SDL_DestroyWindow(ctx.window);
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
            ctx.open = false;
    }

    SDL_SetRenderDrawColor(ctx.renderer, 0, 0, 0, 255);
    SDL_RenderClear(ctx.renderer);

    renderGrid();
    renderFunction();

    SDL_RenderPresent(ctx.renderer);
}

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    ctx.window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    ctx.renderer = SDL_CreateRenderer(ctx.window, -1, SDL_RENDERER_ACCELERATED);


    if (ctx.window != NULL && ctx.renderer != NULL) ctx.open = true;

    ctx.camera.x = 0;
    ctx.camera.y = 0;

    ctx.ppu = 50;

    #ifdef EMSCRIPTEN
    emscripten_set_main_loop(mainloop, 0, 1);
    #else
    while (1) { mainloop(); }
    #endif

    return EXIT_SUCCESS;
}