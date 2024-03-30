#include "Bird.h"

Bird::Bird()
{
    x_val_=0;
    y_val_=2;
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

void Bird::Run()
{
    rect_.y+=y_val_;
}
