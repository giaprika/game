#include "Live.h"

bool Live::InitHeart(SDL_Renderer* render_)
{
    BaseObject* heart1 = new BaseObject();
    BaseObject* heart2 = new BaseObject();
    BaseObject* heart3 = new BaseObject();

    bool ret1 = heart1->loadImage(render_, "img//heart.png");
    bool ret2 = heart2->loadImage(render_, "img//heart.png");
    bool ret3 = heart3->loadImage(render_, "img//heart.png");

    heart.push_back(heart1);
    heart.push_back(heart2);
    heart.push_back(heart3);

    if(!ret1 || !ret2 || !ret3) return false;
    return true;
}

void Live::RenderHeart(SDL_Renderer* render_, int& mang)
{
    int x_ = 20;
    for(int i=0; i<mang; i++){
        heart[i]->SetRect(x_, 150);
        heart[i]->Render(render_);
        x_ += 50;
    }
    for(int i=mang; i<heart.size(); i++){
        heart[i]->SetRect(-100, -100);
        heart[i]->Render(render_);
    }
}

void Live::FreeLive()
{
    for(int i=0; i<heart.size(); i++){
        heart[i]->Free();
        delete heart[i];
    }
    heart.clear();
}
