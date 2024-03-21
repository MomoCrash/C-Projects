#pragma once
#include <SDL.h>
#include "game.h"
#include "tools.h"

SDL_Rect DrawRectCoord(SDL_Surface* surface, int x, int y, int h, int w, Uint32 color);

bool CheckPointInside(const SDL_Rect* rect, const int x, const int y);

void WriteText(SDL_Renderer* renderer, const int x, const int y, const char* text);

void UpdateGraphics(const Grid* grid, const SDL_Surface* screenSurface, SDL_Rect* result, SDL_Renderer* renderer);

void CreateWindow();