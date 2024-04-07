#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include "Define.h"
struct Text
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
};

#endif // TEXT_H_INCLUDED
