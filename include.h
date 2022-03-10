#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <bits/stdc++.h>
#include <windows.h>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;//g_screen
static SDL_Event event;

//thong so screen
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 1000;
const int SCREEN_BPP = 32; //pixel

const int COLOR_KEY_R = 167;//red
const int COLOR_KEY_G = 175;//green
const int COLOR_KEY_B = 180;//blue

const int RENDER_DRAW_COLOR = 0xff;
#endif // COMMON_FUNCTION_H_

using namespace std;
