#ifndef BASE_FUNCTION__H_
#define BASE_FUNCTION__H_

#include "Init.h"

//Loads individual image as texture
SDL_Texture* loadTexture( const std::string &path, SDL_Renderer* &gRenderer );

//Loads text content image as texture
SDL_Rect renderTextTexture(SDL_Renderer* &gRenderer, const std::string &fontName,
                           const std::string &content, const int &fontSize,
                           const SDL_Color &fcolor, const int &x, const int &y);

//Kiem tra va cham giua hai hinh chu nhat
bool checkCollisionRect(SDL_Rect &a, SDL_Rect &b);

//Kiem tra xem diem co toa do (x,y) co nam trong hinh chu nhat khong
bool checkInside(SDL_Rect &a, const int &x, const int &y);

void setBackgroundTexture( const std::string &path, SDL_Renderer* &gRenderer );

bool welcome(SDL_Renderer* &gRenderer);

void renderScore(SDL_Renderer* &gRenderer, Uint32 &score, const int &NUM_COVID_SCORES);

void GameOver(SDL_Renderer* &gRenderer, Uint32 &score, const int &NUM_COVID_SCORES);

#endif // BASE_FUNCTION__H_

