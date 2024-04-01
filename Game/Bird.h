#ifndef BIRD_H_INCLUDED
#define BIRD_H_INCLUDED

#include "BaseObject.h"
class Bird : public BaseObject
{
private:
    SDL_Texture* text1;
    SDL_Texture* text2;
    int x_val_;
    int y_val_;
    int dem;
public:
    Bird();
    ~Bird();
    void HandleInputAction(SDL_Event events);
    bool LoadBird(SDL_Renderer* render_, std::string file1, std::string file2);
    void RenderBird(SDL_Renderer* render_);
    void Run();
};




#endif // BIRD_H_INCLUDED
