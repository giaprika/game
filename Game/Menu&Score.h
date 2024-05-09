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
    void renderTexture(SDL_Renderer* render_, int x_, int y_, int w_, int h_);
    void Settext(const char* path) {text = path;}
    void SettextColor(int r_, int g_, int b_);
    void RenderRectScore(SDL_Renderer* render_);
    void FreeText();
};

class Menu : BaseObject
{
private:
    Text text1;
    Text text2;
    Text text3;
    Text text4;
    Text text5;
    Text text6;
    Mix_Chunk* _gchunk_;
public:
    Menu();
    bool loadFont(const char* filename);
    int ShowMenu(SDL_Renderer* render_, std::string filename, const char* text1_, const char* text2_, const char* text3_, const char* text4_, const char* text5_);
    int ChooseBird(SDL_Renderer* render_, const char* text1_, const char* text2_, const char* text3_, const char* text4_,
                    const char* text5_, const char* text6_, int& bird2_, int& bird3_);
    int ShowRule(SDL_Renderer* render_, const char* text1_, const char* text2_);
    int ShowShop(SDL_Renderer* render_, const char* text_, int& coin_money, int& bird2_, int& bird3_);
    void FreeMenu();
};

class Pause
{
private:
    BaseObject pause_game;
    BaseObject continue_;
    BaseObject exit_;
    Mix_Chunk* gchunk_;
public:
    Pause();
    int RenderPause(SDL_Renderer* render_);
    void FreePause();
};

#endif // TEXT_H_INCLUDED
