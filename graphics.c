#include "graphics.h"
#include "tools.h"
#include "game.h"
#include <SDL.h>
#include <SDL_ttf.h>

SDL_Rect DrawRectCoord(SDL_Surface* surface, int x, int y, int h, int w, Uint32 color) {

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_FillRect(surface, &rect, color);
    return rect;

}

bool CheckPointInside(const SDL_Rect* rect, const int x, const int y)
{
    if (x > rect->x && x < rect->x+ rect->w && y > rect->y+ rect->h && y < rect->y)
        return true;

    return false;
}

void WriteText(SDL_Renderer* renderer, const int x, const int y, const char* text) {

    TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24);

    SDL_Color White = { 255, 255, 255 };

    // as TTF_RenderText_Solid could only be used on
    // SDL_Surface then you have to create the surface first
    SDL_Surface* surfaceMessage =
        TTF_RenderText_Solid(Sans, text, White);

    // now you can convert it into a texture
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_Rect Message_rect;
    Message_rect.x = x; 
    Message_rect.y = y;
    Message_rect.w = 100;
    Message_rect.h = 100;

    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}

void UpdateGraphics(const Grid* grid, const SDL_Surface* screenSurface, SDL_Rect* result, SDL_Renderer* renderer) {

    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

    int baseX = 640 / (grid->size / 2);
    int baseY = 480 / (grid->size / 2);
    int index = 0;

    for (int y = 0; y < grid->size; y++) {
        for (int x = 0; x < grid->size; x++) {

            Tile* tile = GetTile(grid, x, y);
            if (!tile) continue;

            if (tile->isMine) {
                printf("%d", index);
                *(result + index) = DrawRectCoord(screenSurface, baseX + x * 30, baseY + y * 30, 25, 25, SDL_MapRGB(screenSurface->format, 255, 0, 0));
                WriteText(renderer, x, y, "M");
            }
            else {
                printf("%d", index);
                *(result + index) = DrawRectCoord(screenSurface, baseX + x * 30, baseY + y * 30, 25, 25, SDL_MapRGB(screenSurface->format, 0, 255, 0));
                WriteText(renderer, x, y, "T");
            }
            index++;
        }
    }

    SDL_RenderPresent(renderer);

}

void CreateWindow() {
	
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Surface* screenSurface = NULL;
    //TTF_Init();

    Grid grid;
    int gridSize = 10;
    InitGrid(&grid, gridSize, 10);
    SDL_Rect* allRect = (SDL_Rect*)malloc(sizeof(SDL_Rect) * gridSize * gridSize);

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        window = SDL_CreateWindow("Demineur", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            screenSurface = SDL_GetWindowSurface(window);
            if (screenSurface == NULL) {
                printf("Window cannot be created");
                exit(0);
            }
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL) {
                printf("Render canno't be created");
                exit(0);
            }

            SDL_UpdateWindowSurface(window);

            SDL_Event e;
            bool quit = false;

            while (loop()) {

                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        int x;
                        int y;
                        SDL_GetGlobalMouseState(&x, &y);
                        SDL_MouseButtonEvent buttonEvent = e.button;
                        if (buttonEvent.button == SDL_BUTTON_LEFT)
                        {
                            Tile* tile = NULL;
                            int index = 0;
                            for (int i = 0; i < gridSize * gridSize; i++) {
                                SDL_Rect rect = allRect[i];
                                if (CheckPointInside(&rect, x, y)) {
                                    tile = &(grid.tiles[i]);
                                    index = i;
                                }
                            }
                            if (tile == NULL) continue;

                            int tileX = index % gridSize;
                            int tileY = index / gridSize;

                            DiscoverTile(&grid, tile, tileX, tileY);
                            UpdateGraphics(&grid, screenSurface, allRect, renderer);

                        }
                        else {
                            printf("Right");
                        }
                    }
                    if (e.type == SDL_QUIT) quit = true;
                }

                UpdateGraphics(&grid, screenSurface, allRect, renderer);

                SDL_Delay(10);

            }

            SDL_Event e; 
            bool quit = false; 
            while (quit == false) { 
                while (SDL_PollEvent(&e)) { 
                    if (e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        int x;
                        int y;
                        SDL_GetGlobalMouseState(&x, &y);
                        SDL_MouseButtonEvent buttonEvent = e.button;
                        if (buttonEvent.button == SDL_BUTTON_LEFT)
                        {
                            Tile* tile = NULL;
                            int index = 0;
                            for (int i = 0; i < gridSize * gridSize; i++) {
                                SDL_Rect rect = allRect[i];
                                if (CheckPointInside(&rect, x, y)) {
                                    tile = &(grid.tiles[i]);
                                    index = i;
                                }
                            }
                            if (tile == NULL) continue;

                            int tileX = index % gridSize;
                            int tileY = index / gridSize;

                            DiscoverTile(&grid, tile, tileX, tileY);
                            UpdateGraphics(&grid, screenSurface, allRect, renderer);

                        }
                        else {
                            printf("Right");
                        }
                    }
                    if (e.type == SDL_QUIT) quit = true; 
                } 
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

}