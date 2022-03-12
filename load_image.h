#include "include.h"

const std::string WINDOW_TITLE = "SDL GAME VIRUS";

void logSDLError(std::ostream& out, const std::string& msg, bool fatal);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer); //thiet lap dau tien
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
SDL_Texture *IMG_LoadTexture(const char *file, SDL_Renderer *renderer);

SDL_Texture *IMG_LoadTexture(const char *file, SDL_Renderer *renderer)
{
    SDL_Texture *texture = NULL;
    SDL_Surface *surface = IMG_Load(file);
    if (surface)
    {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
    else
    {
        std::cout << "Unable to create texture from " << file << " SDL Error: "
                  << SDL_GetError() << std::endl;
    }
    return texture;
}

void logSDLError(std::ostream& out, const std::string& msg, bool fatal)
{
    out << msg << "Error: " << SDL_GetError() << std::endl;
    if(fatal == true)
    {
        SDL_Quit();
        exit(1); //EXIT_FAILURE
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(),
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_FULLSCREEN_DESKTOP);
                              //SDL_WINDOW_SHOWN

    if (window == nullptr)
    logSDLError(std::cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{

    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    IMG_Quit();
    SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true)
    {
        if ( SDL_WaitEvent(&e) != 0 &&
                (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return ;
        SDL_Delay(50);
    }
}


/*
SDL_Surface* LoadImage(std::string file_path)
{
    SDL_Surface *load_image = NULL;
    SDL_Surface *optimize_image = NULL;

    load_image = IMG_Load(file_path.c_str());
    if(load_image != NULL)
    {
        *optimize_image = *load_image;
        SDL_FreeSurface(load_image);
    }
    return optimize_image;
}
int main(int argc, char* argv[])
{
    SDL_Surface *screen;
    SDL_Surface *image;
    SDL_Renderer* renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
        return 1;

//        screen = SDL_SetVideoMode(1200, 600, 32, SDL_SWSURFACE);
        image = LoadImage("daybien.PNG");
    SDL_BlitSurface(image, NULL, screen, NULL);

    SDL_Flip(screen);
    SDL_Delay(5000);
    SDL_FreeSurface(image);
    SDL_Quit();
    return 0;
}

*/
