
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
    object_ = IMG_LoadTexture(render_, filename.c_str());
    SDL_QueryTexture(object_, NULL, NULL, &rect_.w, &rect_.h);
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

SDL_Rect BaseObject::GetRect() const
{
    return rect_;
}
