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
#include <cstdlib>

//Screen dimension constants
static const int SCREEN_WIDTH = 1260;
static const int SCREEN_HEIGHT = 672;
static const int NUM_VIRUS = 6;

//Initialize SDL
bool init(SDL_Window* &gWindow, SDL_Renderer* &gRenderer);

//Loads individual image as texture
SDL_Texture* loadTexture( const std::string &path, SDL_Renderer* &gRenderer );

void setBackgroundTexture( const std::string &path, SDL_Renderer* &gRenderer );

void waitUntilEnterPressed();

void welcome(SDL_Renderer* &gRenderer);

void renderTextTexture(SDL_Renderer* &gRenderer, const std::string &fontName,
                       const std::string &content, const int &fontSize,
                       const SDL_Color &fg, const int &x, const int &y);

void renderScore(SDL_Renderer* &gRenderer, Uint32 score);

void GameOver(SDL_Renderer* &gRenderer, Uint32 score);

//Frees media and shuts down SDL
void close(SDL_Window* &gWindow, SDL_Renderer* &gRenderer);

#endif // INIT__H_
