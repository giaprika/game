#ifndef BIRD_H_INCLUDED
#define BIRD_H_INCLUDED

#include "BaseObject.h"
class Bird : public BaseObject
{
private:
    SDL_Texture* text1;
    SDL_Texture* text2;
    SDL_Texture* text3;
    const int g = 9;
    int speed;
    int dem;
public:
    Bird();
    ~Bird();
    void HandleInputAction(SDL_Event events);
    bool LoadBird(SDL_Renderer* render_, std::string file1, std::string file2, std::string file3);
    void RenderBird(SDL_Renderer* render_);
    void Run();
    void Rendertext3(SDL_Renderer* render_);
};

#endif // BIRD_H_INCLUDED
