#include "Bird.h"

Bird::Bird()
{
    x_val_=0;
    y_val_=2;
    text1 = NULL;
    text2 = NULL;
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
            y_val_= -9;
      }
  }
  else if( events.type == SDL_KEYUP )
  {
      if(events.key.keysym.sym == SDLK_UP || events.key.keysym.sym == SDLK_SPACE){
            y_val_=4;
      }
  }
}

bool Bird::LoadBird(SDL_Renderer* render_, std::string file1, std::string file2)
{
    text1 = IMG_LoadTexture(render_, "img//bird1.png");
    text2 = IMG_LoadTexture(render_, "img//bird2.png");
    return (text1 != NULL && text2 != NULL);
}

void Bird::RenderBird(SDL_Renderer* render_)
{
    dem++;
    if(dem<35){
        rect_.w = 64;
        rect_.h = 48;
        SDL_RenderCopy(render_, text1, NULL, &rect_);
    }else if (dem>=35 && dem<70){
        rect_.w = 64;
        rect_.h = 56;
        SDL_RenderCopy(render_, text2, NULL, &rect_);
    }else{
        SDL_RenderCopy(render_, text2, NULL, &rect_);
        dem = 0;
    }
}

void Bird::Run()
{
    rect_.y+=y_val_;
}
