#include "Bird.h"

Bird::Bird()
{
    speed = 2;
    text1 = NULL;
    text2 = NULL;
    text3 = NULL;
    dem=0;
}
Bird::~Bird()
{
    this->Free();
}

void Bird::HandleInputAction(SDL_Event events)
{
  if( events.type == SDL_KEYDOWN )
  {
      if(events.key.keysym.sym == SDLK_UP || events.key.keysym.sym == SDLK_SPACE){
            speed = -15;
      }
  }
  else if( events.type == SDL_KEYUP )
  {
      if(events.key.keysym.sym == SDLK_UP || events.key.keysym.sym == SDLK_SPACE){
            speed = 1;
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
    if(dem<10){
        rect_.w = 64;
        rect_.h = 48;
        SDL_RenderCopy(render_, text1, NULL, &rect_);
    }else{
        rect_.w = 64;
        rect_.h = 56;
        SDL_RenderCopy(render_, text2, NULL, &rect_);
        if(dem>20) dem=0;
    }

}

void Bird::Run()
{
    rect_.y+= speed + 0.5*g;
    speed += 0.1 * g;
}

void Bird::Rendertext3(SDL_Renderer* render_)
{
    rect_.w = 64;
    rect_.h = 56;
    SDL_RenderCopy(render_, text3, NULL, &rect_);
}
