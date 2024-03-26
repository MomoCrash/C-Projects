#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "game.h"
#include "tools.h"

typedef struct SDL_Button
{

    void (*resetGridFunc)(Grid*);
    SDL_Rect* collider;
    const char* text;

} SDL_Button;

SDL_Rect DrawRectCoord(SDL_Surface* surface, int x, int y, int h, int w, Uint32 color);

bool CheckPointInside(const SDL_Rect* rect, const int x, const int y);

void render_char(SDL_Surface* surface, SDL_Renderer* renderer,int x,int y, char text, TTF_Font* font, SDL_Color* color);

void render_text(SDL_Surface* surface, SDL_Renderer* renderer,int x,int y, const char* text, TTF_Font* font, SDL_Color* color);

void InitButton(SDL_Button* button, SDL_Rect* position, const char* text, SDL_Color* color, void (*resetGridFunc)(Grid*));

void DrawButton(SDL_Surface* surface, SDL_Renderer* renderer, const SDL_Button button, TTF_Font* font);

void UpdateGraphics(const Grid* grid, const SDL_Surface* screenSurface, SDL_Rect* result, SDL_Button* buttons, SDL_Renderer* renderer, TTF_Font* font, bool exploded);

void InitWindow();