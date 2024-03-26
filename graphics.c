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
    if (x>=rect->x && x<=rect->x+rect->w && y<=rect->y+rect->h && y>=rect->y)
        return true;

    return false;
}

bool IsUpdatingGraphics = false;

void render_char(SDL_Surface* surface, SDL_Renderer* renderer, int x, int y, char text, TTF_Font* font, SDL_Color* color) {
    SDL_Surface* textSurface;
    SDL_Texture* texture;

    textSurface = TTF_RenderText_Solid(font, &text, *color);
    texture = SDL_CreateTextureFromSurface(renderer, textSurface);

    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = { x, y, texW, texH };

    SDL_BlitSurface(textSurface, NULL, surface, &dstrect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(texture);
}

void render_text(SDL_Surface* surface, SDL_Renderer* renderer, int x, int y, const char* text, TTF_Font* font, SDL_Color* color) {
    SDL_Surface* textSurface;
    SDL_Texture* texture;

    textSurface = TTF_RenderText_Solid(font, text, *color);
    texture = SDL_CreateTextureFromSurface(renderer, textSurface);

    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = { x, y, texW, texH };

    SDL_BlitSurface(textSurface, NULL, surface, &dstrect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(texture);

}

void InitButton(SDL_Button* button, SDL_Rect* position, const char* text, SDL_Color* color, void (*resetGridFunc)(Grid*)) {

    button->collider = position;
    button->func = resetGridFunc;
    button->text = text;

}

void DrawButton(SDL_Surface* surface, SDL_Renderer* renderer, const SDL_Button button, TTF_Font* font) {


    SDL_Color white = { 255, 255, 255 };
    SDL_Color black = { 0, 0, 0 };

    DrawRectCoord(surface, button.collider->x, button.collider->y, button.collider->h, button.collider->w, &white);
    render_text(surface, renderer, button.collider->x, button.collider->y, button.text, font, &black);

}

void UpdateGraphics(const Grid* grid, const SDL_Surface* screenSurface, SDL_Rect* result, SDL_Button* buttons, SDL_Renderer* renderer, TTF_Font* font, bool exploded) {

    // Clear background
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 128, 139, 150));
    SDL_Color White = { 255, 255, 255 };

    int baseX = 640 / (grid->size / 2);
    int baseY = 480 / (grid->size / 2);
    int index = 0;

    // Render title 
    render_text(screenSurface, renderer, baseX + 50, 10, "Minesweeper", font, &White);

    // Update rendered grid cases
    for (int y = 0; y < grid->size; y++) {
        for (int x = 0; x < grid->size; x++) {

            Tile* tile = GetTile(grid, x, y);
            if (!tile) continue;

            if (exploded) {
                if (tile->isMine) {
                    *(result + index) = DrawRectCoord(screenSurface, baseX + x * 30, baseY + y * 30, 25, 25, SDL_MapRGB(screenSurface->format, 197, 0, 0));
                }
                else {
                    *(result + index) = DrawRectCoord(screenSurface, baseX + x * 30, baseY + y * 30, 25, 25, SDL_MapRGB(screenSurface->format, 225, 179, 127));
                    render_char(screenSurface, renderer, baseX + x * 30, baseY + y * 30, IntToChar(tile->mineNumberAround), font, &White);
                }
            }
            else {
                if (tile->isShowed) {
                    *(result + index) = DrawRectCoord(screenSurface, baseX + x * 30, baseY + y * 30, 25, 25, SDL_MapRGB(screenSurface->format, 225, 179, 127));
                    render_char(screenSurface, renderer, baseX + x * 30, baseY + y * 30, IntToChar(tile->mineNumberAround), font, &White);
                }
                else if (tile->isFlag) {
                    *(result + index) = DrawRectCoord(screenSurface, baseX + x * 30, baseY + y * 30, 25, 25, SDL_MapRGB(screenSurface->format, 73, 209, 110));
                } 
                else {
                    *(result + index) = DrawRectCoord(screenSurface, baseX + x * 30, baseY + y * 30, 25, 25, SDL_MapRGB(screenSurface->format, 213, 219, 219));
                }
            }

            index++;
        }
    }


    DrawButton(screenSurface, renderer, buttons[0], font);
    DrawButton(screenSurface, renderer, buttons[1], font);

    SDL_RenderPresent(renderer);

}

void ResetGrid(Grid* grid) {
    free(grid->tiles);
    InitGrid(grid, grid->size, 10);
    IsUpdatingGraphics = true;
}

void Quit() {
    exit(0);
}

void InitWindow() {
	
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Surface* screenSurface = NULL;

    if (TTF_Init() == -1) {
        printf("TTF_text module can't be loaded");
        exit(0);
    }

    TTF_Font* font = TTF_OpenFont("TypeMachine.ttf", 24);

    if (font == NULL) exit(0);

    Grid grid;
    int gridSize = 10;
    InitGrid(&grid, gridSize, 10);
    SDL_Rect* allRect = (SDL_Rect*)malloc(sizeof(SDL_Rect) * gridSize * gridSize);

    int BUTTON_NUMBER = 2;

    // Reset button
    SDL_Button* buttons = (SDL_Button*)malloc(sizeof(SDL_Button) * BUTTON_NUMBER);

    SDL_Rect restartRect = { 120, 400, 200, 50 };
    SDL_Rect quitRect = { 360, 400, 100, 50 };
    SDL_Color White = { 255, 255, 255 };

    InitButton(&buttons[0], &restartRect, "Recommencer", &White, &ResetGrid);
    InitButton(&buttons[1], &quitRect, "Quitter", &White, &Quit);

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

            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL) {
                printf("Render canno't be created");
                exit(0);
            }

            screenSurface = SDL_GetWindowSurface(window);
            if (screenSurface == NULL) {
                printf("Window cannot be created");
                exit(0);
            }
            
            UpdateGraphics(&grid, screenSurface, allRect, buttons, renderer, font, false);

            SDL_UpdateWindowSurface(window);

            SDL_Event e;
            bool quit = false;
            bool lose = false;
            while (!quit) {

                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        int x = e.motion.x;
                        int y = e.motion.y;
                        SDL_MouseButtonEvent buttonEvent = e.button;

                        Tile* tile = NULL;
                        int index = 0;
                        for (int i = 0; i < gridSize * gridSize; i++) {
                            SDL_Rect rect = allRect[i];
                            if (CheckPointInside(&rect, x, y)) {
                                tile = &(grid.tiles[i]);
                                index = i;
                            }
                        }
                        printf("%d", index);
                        if (tile == NULL) {
                            
                            for (int i = 0; i < BUTTON_NUMBER; i++) {
                                if (CheckPointInside(buttons[i].collider, x, y)) {
                                    buttons[i].func(&grid);
                                }
                            }

                            continue;
                        }

                        if (lose) continue;

                        int tileX = index % gridSize;
                        int tileY = index / gridSize;

                        if (buttonEvent.button == SDL_BUTTON_LEFT)
                        {

                            if (tile->isFlag) continue;

                            if (TileIsAMine(tile)) {
                                UpdateGraphics(&grid, screenSurface, allRect, buttons, renderer, font, true);
                            }
                            else {
                                DiscoverTile(&grid, tile, tileX, tileY);
                                UpdateGraphics(&grid, screenSurface, allRect, buttons, renderer, font, false);
                            }

                            SDL_UpdateWindowSurface(window);

                        }
                        else {

                            PlaceFlag(&grid, tileX, tileY);

                            UpdateGraphics(&grid, screenSurface, allRect, buttons, renderer, font, false);

                            SDL_UpdateWindowSurface(window);

                        }

                    }
                    if (e.type == SDL_QUIT) quit = true;
                }

                SDL_Delay(10);

                if (IsUpdatingGraphics) {
                    UpdateGraphics(&grid, screenSurface, allRect, buttons, renderer, font, false);
                    SDL_UpdateWindowSurface(window);
                    IsUpdatingGraphics = false;
                }

            }

        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

}