#ifndef INIT__H_
#define INIT__H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <windows.h>
#include <stdio.h>
#include <string>
#include <bits/stdc++.h>

//Screen dimension constants
const int SCREEN_WIDTH = 1260;
const int SCREEN_HEIGHT = 672;
const int ANIMATION_FRAMES = 3;

static SDL_Rect FullScreen = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

//Loads individual image as texture
SDL_Texture* loadTexture( std::string path, SDL_Renderer* gRenderer);

//Initialize SDL
bool init(SDL_Window* &gWindow, SDL_Renderer* &gRenderer);

void waitUntilEnterPressed();

void welcome(SDL_Renderer* gRenderer);

void GameOver(SDL_Renderer* gRenderer);

//Frees media and shuts down SDL
void close(SDL_Window* gWindow, SDL_Renderer* gRenderer, SDL_Texture* gTexture);

#endif // INIT__H_
