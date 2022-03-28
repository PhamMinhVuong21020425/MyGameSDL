#ifndef COLLISION__H_
#define COLLISION__H_

#include "Init.h"
#include "LTexture.h"
#include "CharacterMove.h"
#include "Virus.h"

bool checkCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b);
bool checkCollisionRect(SDL_Rect a, SDL_Rect b);

#endif // COLLISION__H_
