#ifndef INIT__H_
#define INIT__H_

#define SCREEN_WIDTH 1260
#define SCREEN_HEIGHT 673

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <windows.h>
#include <cstdlib>
#include <time.h>
#include <bits/stdc++.h>

//Initialize SDL
bool init(SDL_Window* &gWindow, SDL_Renderer* &gRenderer);

//Frees media and shuts down SDL
void close(SDL_Window* &gWindow, SDL_Renderer* &gRenderer, Mix_Music* &gMusic);

//Program continue when press ENTER
void waitUntilEnterPressed();

#endif // INIT__H_
