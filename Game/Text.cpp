#include "Text.h"

Text::Text()
{
    textColor.r = 255;
    textColor.g = 255;
    textColor.b = 255;
    texture = NULL;
    font = NULL;
}

bool Text::loadFont(const char* path, int size)
{
    font = TTF_OpenFont(path, size);
    return (font != NULL);
}


void Text::renderTexture(SDL_Renderer* render_, int x_, int y_, int w_, int h_)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
    if(textSurface != NULL){
        texture = SDL_CreateTextureFromSurface(render_, textSurface);
        SDL_Rect recttext = {x_, y_, w_, h_};
        SDL_RenderCopy(render_, texture, NULL, &recttext);
    }

}

void Text::SettextColor(int r_, int g_, int b_)
{
    textColor.r = r_;
    textColor.g = g_;
    textColor.b = b_;
}

int Menu::ShowMenu(SDL_Renderer* render_, const char* text1_, const char* text2_, const char* text3_)
{
    bool ret = this->loadImage(render_, "MENU.png");
    if(!ret) return -1;
    bool ret1 = text1.loadFont("ARCADE.ttf", 30);
    bool ret2 = text2.loadFont("ARCADE.ttf", 30);
    bool ret3 = text3.loadFont("ARCADE.ttf", 30);
    if(!ret1 || !ret2 || !ret3) return -1;
    text1.Settext(text1_);
    text2.Settext(text2_);
    text3.Settext(text3_);

    text3.SettextColor(0, 255, 255);

    this->Render(render_);
    int x=0;
    int y=0;

    while(1)
    {
        text1.renderTexture(render_, 200, 350, 400, 100);
        text2.renderTexture(render_, 200, 500, 200, 80);
        text3.renderTexture(render_, 200, 200, 400, 100);
        while(SDL_PollEvent(&event_))
        {
            switch(event_.type)
            {
            case SDL_QUIT:
                return -1;
                break;
            case SDL_MOUSEMOTION:
                x = event_.motion.x;
                y = event_.motion.y;
                if(x>=200 && x<=400 && y>=500 && y<=580){
                    text2.SettextColor(255, 0, 0);
                }
                else if(x>=200 && x<=600 && y>=350 && y<=450){
                    text1.SettextColor(255, 0 ,0);
                }
                else{
                    text1.SettextColor(255, 255, 255);
                    text2.SettextColor(255, 255, 255);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = event_.button.x;
                y = event_.button.y;
                if(x>=200 && x<=400 && y>=500 && y<=580){
                    this->Free();
                    return -1;
                }
                if(x>=200 && x<=600 && y>=350 && y<=450){
                    this->Free();
                    return 1;
                }
                break;

            }
        }
        SDL_RenderPresent(render_);
    }
}
