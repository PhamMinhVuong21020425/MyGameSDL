#include "Collision.h"

bool checkCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int botA, botB;

    //Go through the A boxes
    for(int Abox = 0; Abox < a.size(); Abox++)
    {
        leftA = a[Abox].x;
        rightA = a[Abox].x + a[Abox].w;
        topA = a[Abox].y;
        botA = a[Abox].y + a[Abox].h;

        //Go through the B boxes
        for(int Bbox = 0; Bbox < b.size(); Bbox++)
        {
            leftB = b[Abox].x;
            rightB = b[Abox].x + b[Abox].w;
            topB = b[Abox].y;
            botB = b[Abox].y + b[Abox].h;

            if (
                (rightA <= leftB) == false &&
                (leftA >= rightB) == false &&
                (topA <= botB) == false &&
                (botA >= topB) == false
               )
                return true;
        }
    }

    return false;
}

bool checkCollisionRect(SDL_Rect a, SDL_Rect b)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}
