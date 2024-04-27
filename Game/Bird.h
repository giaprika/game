#ifndef BIRD_H_INCLUDED
#define BIRD_H_INCLUDED

#include "BaseObject.h"
class Bird : public BaseObject
{
private:
    SDL_Texture* text1;
    SDL_Texture* text2;
    SDL_Texture* text3;
    const double g = 0.5;
    double speed;
    int dem;
    bool is_saved;
public:
    Bird();
    void HandleInputAction(SDL_Event events);
    bool LoadBird(SDL_Renderer* render_, std::string file1, std::string file2, std::string file3);
    void RenderBird(SDL_Renderer* render_);
    void Run();
    void Rendertext3(SDL_Renderer* render_);
    bool GetIs_saved() const {return is_saved;}
    void SetIs_saved(bool saved) {is_saved = saved;}
    void SetRect_(const int &x, const int &y);
};

#endif // BIRD_H_INCLUDED
