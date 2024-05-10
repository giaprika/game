#ifndef LIVE_H_INCLUDED
#define LIVE_H_INCLUDED
#include "BaseObject.h"
class Live : BaseObject
{
private:
    std::vector<BaseObject*> heart;
public:
    bool InitHeart(SDL_Renderer* render_);
    void RenderHeart(SDL_Renderer* render_, int& mang);
    void FreeLive();
};

#endif // LIVE_H_INCLUDED
