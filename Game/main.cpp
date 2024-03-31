#include "Define.h"
#include "BaseObject.h"
#include "Bird.h"
#include "Colum.h"

BaseObject bk_grd;
bool Init()
{
    int ret = SDL_Init(SDL_INIT_EVERYTHING);
    if (ret < 0) return false;
    window_ = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(window_ == NULL) return false;
    render_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(render_ == NULL) return false;
    return true;

}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

void close()
{
    bk_grd.Free();
    SDL_DestroyRenderer(render_);
    render_ = NULL;

    SDL_DestroyWindow(window_);
    window_ = NULL;

    IMG_Quit();
    SDL_Quit();
}
int main(int argc, char* argv[])
{

    if(Init() == false) return -1;
    bool ret = bk_grd.loadImage(render_, "bkgn.png");
    if(ret == false) return -1;


    Bird bird;
    ret = bird.loadImage(render_, "fl_bird.png");
    Colum colum;
    ret = colum.LoadColum(render_, "bottomblock2.png");
    colum.SetPos(1000, 320);
    if(ret == false) return -1;
    bird.SetRect(100, 100);
    bool quit=false;
    while(!quit){

        while (SDL_PollEvent(&event_) != 0)
        {
            if (event_.type == SDL_QUIT)
            {
                quit = true;
            }

            bird.HandleInputAction(event_);


        }


        bk_grd.Render(render_);
        colum.Run(-2);
        colum.ShowColum(render_);

        bird.Run();
        bird.Render(render_);
        SDL_RenderPresent(render_);

    }
    waitUntilKeyPressed();
    close();
}
