#ifndef LTexture__H_
#define LTexture__H_

#include "Init.h"

class LTexture
{
    public:
    //Initializes variables
    LTexture();

    //Deallocates memory
    ~LTexture();

    //Loads image at specified path
    virtual bool loadFromFile( const std::string &path, SDL_Renderer* &gRenderer);

    #if defined(SDL_TTF_MAJOR_VERSION)
    //Creates image from font string
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor, TTF_Font *gFont, SDL_Renderer* gRenderer );
    #endif // defined

    //Deallocates texture
    void free();

    //Set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );

    //Set blending
    void setBlendMode( SDL_BlendMode blending );

    //Set alpha modulation
    void setAlpha( Uint8 alpha );

    //Renders texture at given point
    void render( const int &x, const int &y, const SDL_Rect* clip = NULL, SDL_Renderer* gRenderer = NULL,
                const double angle = 0.0, SDL_Point* center = NULL, const SDL_RendererFlip flip = SDL_FLIP_NONE );

    //Gets image dimensions
    int getWidth();
    int getHeight();

private:
    //The actual hardware texture
    SDL_Texture* mTexture;

    //Image dimensions
    int mWidth;
    int mHeight;
};

#endif // LTexture__H_
