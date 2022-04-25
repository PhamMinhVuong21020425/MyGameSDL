#ifndef INIT__H_
#define INIT__H_

#define SCREEN_WIDTH 1260
#define SCREEN_HEIGHT 673

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <windows.h>
#include <stdio.h>
#include <string>
#include <bits/stdc++.h>
#include <cstdlib>

//Initialize SDL
bool init(SDL_Window* &gWindow, SDL_Renderer* &gRenderer);

//Loads individual image as texture
SDL_Texture* loadTexture( const std::string &path, SDL_Renderer* &gRenderer );

void setBackgroundTexture( const std::string &path, SDL_Renderer* &gRenderer );

bool checkInside(SDL_Rect &a, const int &x, const int &y);

void waitUntilEnterPressed();

bool welcome(SDL_Renderer* &gRenderer);

SDL_Rect renderTextTexture(SDL_Renderer* &gRenderer, const std::string &fontName,
                       const std::string &content, const int &fontSize,
                       const SDL_Color &fcolor, const int &x, const int &y);

void renderScore(SDL_Renderer* &gRenderer, Uint32 &score, const int &NUM_COVID_SCORES);

void GameOver(SDL_Renderer* &gRenderer, Uint32 &score, const int &NUM_COVID_SCORES);

//Frees media and shuts down SDL
void close(SDL_Window* &gWindow, SDL_Renderer* &gRenderer);

#endif // INIT__H_
