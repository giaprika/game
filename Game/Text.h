#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include "Define.h"
#include "BaseObject.h"

class Text
{
private:
    TTF_Font* font;
    const char* text;
    SDL_Color textColor;
    SDL_Texture* texture;
public:
    Text();
    bool loadFont(const char* path, int size);
    bool loadTexture(SDL_Renderer* render_);
    void renderTexture(SDL_Renderer* render_, int x_, int y_, int w_, int h_);
    void Settext(const char* path) {text = path;}
    void SettextColor(int r_, int g_, int b_);
};

class Menu : BaseObject
{
private:
    Text text1;
    Text text2;
    Text text3;
public:
    int ShowMenu(SDL_Renderer* render_, const char* text1_, const char* text2_, const char* text3_);
    int ChooseBird(SDL_Renderer* render_, const char* text1_, const char* text2_, const char* text3_);
};

#endif // TEXT_H_INCLUDED
