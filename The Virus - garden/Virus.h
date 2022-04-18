#ifndef VIRUS__H_
#define VIRUS__H_

#include "Init.h"
#include "LTexture.h"
#include "Collision.h"
class Virus : public LTexture
{
public:
    static const int VIRUS_WIDTH = 38;
    static const int VIRUS_HEIGHT = 38;

    int frVirus = 0;
    SDL_Rect gVirusClips[2];
    SDL_Rect CovidRect = {0, 0, VIRUS_WIDTH, VIRUS_HEIGHT};

    Virus();
    ~Virus();
    void setPos(const int &x, const int &y);
    void renderVirus(SDL_Renderer* &gRenderer);
    void move(SDL_Rect &otherColliders, SDL_Rect &mCollider, bool &gameOver, bool &destroyWall);

private:
    int mPosX, mPosY;
    int mVelX, mVelY;

};

#endif // VIRUS__H_
