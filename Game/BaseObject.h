#ifndef BASEOBJECT_H_INCLUDED
#define BASEOBJECT_H_INCLUDED


#include "Define.h"

class BaseObject
{
protected:
    SDL_Texture* object_;
    SDL_Rect rect_;
public:
    BaseObject();
    ~BaseObject();
    virtual bool loadImage(SDL_Renderer* render_, std::string filename);
    void Render(SDL_Renderer* render_);
    void Free();
    void SetRect(const int& x, const int& y);
    SDL_Rect GetRect() const;
};

#endif // BASEOBJECT_H_INCLUDED
