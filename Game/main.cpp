#include "Define.h"
#include "BaseObject.h"
#include "Bird.h"
#include "Colum.h"
#include "Text.h"

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
    if(TTF_Init() == -1) return false;
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
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}

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
    if(ret == false) return -1;

    Text text_score;
    ret = text_score.loadFont("ARCADE.ttf", 40);
    if(ret==false) return -1;

    Save Mangbv;
    ret = Mangbv.LoadSave(render_, "save.png");
    if (ret == false) return -1;

    bird.SetRect(100, 100);
    bool quit=false;
    while(!quit && !colum_.Getdie()){
        while (SDL_PollEvent(&event_) != 0)
        {
            if (event_.type == SDL_QUIT)
            {
                quit = true;
            }
            bird.HandleInputAction(event_);
        }
        bk_grd.Render(render_);
        bird.Run();

        colum_.SetBird_rect(bird.GetRect());
        colum_.Setsaved_(bird.GetIs_saved());
        colum_.ShowList(render_);
        bird.SetIs_saved(colum_.Getsaved_());
        bird.SetRect_(colum_.GetBird_rect().x, colum_.GetBird_rect().y);
        if(colum_.Getdie()){
            bird.Rendertext3(render_);
        }else{
            bird.RenderBird(render_);
        }

        int diem = colum_.Getscore();
        std::string diemso = std::to_string(diem);
        text_score.Settext(diemso.c_str());
        text_score.renderTexture(render_, SCREEN_WIDTH/2, 2, 50, 50);

        if(diem >= 2){
            SDL_Rect rectsave;
            SDL_Rect birdrect = bird.GetRect();
            if(!Mangbv.GetIs_Looted()){
                std::vector<DoubleColum*> listcolum = colum_.GetList();
                rectsave = listcolum.at(6)->GetPassrect();
                rectsave = {rectsave.x-128, rectsave.y + 40, 70, 60};
                if(SDL_HasIntersection(&rectsave, &birdrect)){
                    Mix_Chunk* gChunk = Mix_LoadWAV("vobong.wav");
                    if(gChunk != nullptr){
                        Mix_PlayChannel(-1, gChunk, 0);
                    }
                    Mangbv.SetIs_Looted(true);
                    bird.SetIs_saved(true);
                }
                Mangbv.SetRectSave(rectsave);
                Mangbv.ShowSave(render_);
            }
            else if(bird.GetIs_saved()){

                rectsave = {birdrect.x - 5, birdrect.y - 10, 80, 75};
                Mangbv.SetRectSave(rectsave);
                Mangbv.ShowSave(render_);
            }
            Mangbv.SetIs_Looted(bird.GetIs_saved());
        }

        SDL_RenderPresent(render_);
    }
    close();
}
