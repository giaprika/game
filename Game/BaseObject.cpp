
#include "BaseObject.h"
#include "Define.h"

BaseObject::BaseObject()
{
    object_=NULL;
    rect_.x=0;
    rect_.y=0;
    rect_.w=0;
    rect_.h=0;
}

BaseObject::~BaseObject()
{
    Free();
}

void BaseObject::Free()
{
    if (object_ != NULL)
    {
        SDL_DestroyTexture(object_);
        object_ = NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
}
bool BaseObject::loadImage(SDL_Renderer* render_, std::string filename)
{
    Free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if(surface != NULL){
        Uint32 key = SDL_MapRGB(surface->format, 180, 180, 180);
        SDL_SetColorKey(surface, SDL_TRUE, key);

        newTexture = SDL_CreateTextureFromSurface(render_, surface);

        if(newTexture != NULL){
            rect_.w = surface->w;
            rect_.h = surface->h;
        }

        SDL_FreeSurface(surface);
        object_ = newTexture;
    }

    return object_ != NULL;
}

void BaseObject::Render(SDL_Renderer* render_)
{
    SDL_RenderCopy(render_, object_, NULL, &rect_);

}

void BaseObject::SetRect(const int &x, const int &y)
{
    rect_.x=x;
    rect_.y=y;
}
