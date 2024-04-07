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
    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) return false;
    return true;

}

void close()
{
    SDL_Delay(2000);
    bk_grd.Free();
    SDL_DestroyRenderer(render_);
    render_ = NULL;

    SDL_DestroyWindow(window_);
    window_ = NULL;

    IMG_Quit();
    SDL_Quit();
}
//
//bool Game_over(Bird bird_, ColumList columlist_)
//{
//    std::vector<DoubleColum*> colum_list = columlist_.GetList();
//    SDL_Rect flbird = bird_.GetRect();
//    for(int i=0; i<colum_list.size(); i++){
//        DoubleColum* cl = colum_list.at(i);
//        if(cl->CheckCollision(flbird)){
//            return true;
//        }
//    }
//    return false;
//
//}

int main(int argc, char* argv[])
{
    srand(time(NULL));
    if(Init() == false) return -1;
    bool ret = bk_grd.loadImage(render_, "img//bk_ground.jpg");
    if(ret == false) return -1;

    Bird bird;
    ret = bird.loadImage(render_, "img//bird1.png");
    if(ret == false) return -1;
    ret = bird.LoadBird(render_, "img//bird1.png", "img//bird2.png", "img//bird3.png");
    if(ret == false) return -1;
    ColumList colum_;
    ret = colum_.InitColumList(render_);
//    DoubleColum colum;
//    ret = colum.InitColum(render_, ppp);
    if(ret == false) return -1;
//    Mix_Music *Music_nen = Mix_LoadMUS("nhacnen.mp3");
//    if(Music_nen == nullptr) return -1;
    bird.SetRect(100, 100);
    bool quit=false;
    while(!quit && !colum_.Getdie()){
//        if (Mix_PlayingMusic() == 0) {
//            Mix_PlayMusic( Music_nen, -1 );
//        }
        while (SDL_PollEvent(&event_) != 0)
        {
            if (event_.type == SDL_QUIT)
            {
                quit = true;
            }

            bird.HandleInputAction(event_);
        }
        bk_grd.Render(render_);
        colum_.SetBird_rect(bird.GetRect());

//        colum.Move();
//        colum.ShowDoubleColum(render_);
        bird.Run();
        bird.RenderBird(render_);
//        if(Game_over(bird, colum_)){
//            bird.Rendertext3(render_);
//            quit = true;
//        }
        colum_.ShowList(render_);
        SDL_RenderPresent(render_);
    }
    close();
}
