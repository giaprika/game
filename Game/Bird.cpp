#include "Bird.h"

Bird::Bird()
{
    speed = 0;
    text1 = NULL;
    text2 = NULL;
    text3 = NULL;
    dem=0;
    is_saved = false;
}

void Bird::HandleInputAction(SDL_Event events)
{
    if(!is_paused){
          if( events.type == SDL_KEYDOWN )
          {
              if(events.key.keysym.sym == SDLK_UP ){
                    speed = -8;
              }
          }
          else if( events.type == SDL_KEYUP )
          {
              if(events.key.keysym.sym == SDLK_UP ){
                    speed = 0;
              }
          }
    }
}

bool Bird::LoadBird(SDL_Renderer* render_, std::string file1, std::string file2, std::string file3)
{
    text1 = IMG_LoadTexture(render_, file1.c_str());
    text2 = IMG_LoadTexture(render_, file2.c_str());
    text3 = IMG_LoadTexture(render_, file3.c_str());
    return (text1 != NULL && text2 != NULL && text3 != NULL);
}

void Bird::RenderBird(SDL_Renderer* render_)
{
        dem++;
        if(dem<5){
            rect_.w = 64;
            rect_.h = 48;
            SDL_RenderCopy(render_, text1, NULL, &rect_);
        }else{
            rect_.w = 64;
            rect_.h = 56;
            SDL_RenderCopy(render_, text2, NULL, &rect_);
            if(dem>10) dem=0;
        }
}

void Bird::Run()
{
    if(!is_paused){
        rect_.y+= speed + 0.5*g;
        speed += 0.5*g;
    }
}

void Bird::Rendertext3(SDL_Renderer* render_)
{
    rect_.w = 64;
    rect_.h = 56;
    SDL_RenderCopy(render_, text3, NULL, &rect_);
}

void Bird::SetRect_(const int &x, const int &y)
{
    BaseObject::SetRect(x, y);
}

void Bird::FreeBird()
{
    BaseObject::Free();
    SDL_DestroyTexture(text1);
    SDL_DestroyTexture(text2);
    SDL_DestroyTexture(text3);
}
