#ifndef VIRUS__H_
#define VIRUS__H_

#include "Init.h"
#include "LTexture.h"
#include "Collision.h"
class Virus
{
public:
    static const int VIRUS_WIDTH = 40;
    static const int VIRUS_HEIGHT = 40;
    static const int VIRUS_VEL = 1;
    SDL_Rect Covid = {0, 0, VIRUS_WIDTH, VIRUS_HEIGHT};

    LTexture gVirusTexture;

    Virus();
    ~Virus();
    void loadVirus(SDL_Renderer* gRenderer);
    void renderVirus(SDL_Renderer * gRenderer, SDL_Rect* clip = NULL);
    void move(SDL_Rect &otherColliders);

private:
    int mPosX, mPosY;
    int mVelX, mVelY;

};

#endif // VIRUS__H_
