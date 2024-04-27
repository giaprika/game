#include "Menu&Score.h"

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

void Text::RenderRectScore(SDL_Renderer* render_)
{
    SDL_SetRenderDrawColor(render_, 0, 0, 0, 0xFF);
    SDL_Rect rect_score = {0, 0, SCREEN_WIDTH, 40};
    SDL_RenderFillRect(render_, &rect_score);
}

int Menu::ShowMenu(SDL_Renderer* render_, const char* text1_, const char* text2_, const char* text3_, const char* text4_, const char* text5_)
{
    bool ret = BaseObject::loadImage(render_, "img//MENU.png");
    if(!ret) return -1;
    bool ret1 = text1.loadFont("ARCADE.ttf", 30);
    bool ret2 = text2.loadFont("ARCADE.ttf", 30);
    bool ret3 = text3.loadFont("ARCADE.ttf", 30);
    bool ret4 = text4.loadFont("ARCADE.ttf", 30);
    bool ret5 = text5.loadFont("ARCADE.ttf", 30);
    if(!ret1 || !ret2 || !ret3 || !ret4 || !ret5) return -1;
    text1.Settext(text1_);
    text2.Settext(text2_);
    text3.Settext(text3_);
    text4.Settext(text4_);
    text5.Settext(text5_);

    text3.SettextColor(0, 255, 255);
    text4.SettextColor(255, 0, 0);
    text5.SettextColor(255, 255, 0);

    BaseObject::Render(render_);
    int x=0;
    int y=0;

    while(1)
    {
        text1.renderTexture(render_, 200, 400, 400, 100);
        text2.renderTexture(render_, 200, 550, 200, 80);
        text3.renderTexture(render_, 200, 280, 400, 100);
        text4.renderTexture(render_, 500, 30, 400, 140);
        text5.renderTexture(render_, 200, 150, 500, 120);
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
                if(x>=200 && x<=400 && y>=550 && y<=630){
                    text2.SettextColor(255, 0, 0);
                }
                else if(x>=200 && x<=600 && y>=400 && y<=500){
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
                if(x>=200 && x<=400 && y>=550 && y<=630){
                    BaseObject::Free();
                    return -1;
                }
                if(x>=200 && x<=600 && y>=400 && y<=500){
                    BaseObject::Free();
                    return 1;
                }
                break;

            }
        }
        SDL_RenderPresent(render_);
    }
}

int Menu::ChooseBird(SDL_Renderer* render_, const char* text1_, const char* text2_, const char* text3_, const char* text4_)
{
    bool ret = BaseObject::loadImage(render_, "img//MENU.png");
    if(!ret) return -1;
    bool ret1 = text1.loadFont("ARCADE.ttf", 30);
    bool ret2 = text2.loadFont("ARCADE.ttf", 30);
    bool ret3 = text3.loadFont("ARCADE.ttf", 30);
    bool ret4 = text4.loadFont("ARCADE.ttf", 30);
    if(!ret1 || !ret2 || !ret3 || !ret4) return -1;
    text1.Settext(text1_);
    text2.Settext(text2_);
    text3.Settext(text3_);
    text4.Settext(text4_);

    BaseObject::Render(render_);
    int x=0;
    int y=0;

    while(1)
    {
        text1.renderTexture(render_, 200, 200, 300, 100);
        text2.renderTexture(render_, 200, 350, 300, 100);
        text3.renderTexture(render_, 200, 500, 200, 80);
        text4.renderTexture(render_, 500, 500, 200, 80);
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
                if(x>=200 && x<=500 && y>=200 && y<=300){
                    text1.SettextColor(255, 228, 181);
                }
                else if(x>=200 && x<=500 && y>=350 && y<=450){
                    text2.SettextColor(255, 105 ,180);
                }
                else if(x>=200 && x<=400 && y>=500 && y<=580){
                    text3.SettextColor(255, 0, 0);
                }
                else if(x>=500 && x<=700 && y>=500 &&y<=580){
                    text4.SettextColor(255, 0, 0);
                }
                else{
                    text1.SettextColor(255, 255, 255);
                    text2.SettextColor(255, 255, 255);
                    text3.SettextColor(255, 255, 255);
                    text4.SettextColor(255, 255, 255);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = event_.button.x;
                y = event_.button.y;
                if(x>=200 && x<=500 && y>=200 && y<=300){
                    BaseObject::Free();
                    return 1;
                }
                if(x>=200 && x<=500 && y>=350 && y<=450){
                    BaseObject::Free();
                    return 2;
                }
                if(x>=200 && x<=400 && y>=500 && y<=580){
                    BaseObject::Free();
                    return -1;
                }
                if(x>=500 && x<=700 && y>=500 && y<=580){
                    BaseObject::Free();
                    return 3;
                }
                break;
            }
        }
        SDL_RenderPresent(render_);
    }
}

int Menu::ShowRule(SDL_Renderer* render_, const char* text1_, const char* text2_)
{
    bool ret = BaseObject::loadImage(render_, "img//rule.png");
    if(!ret) return -1;
    bool ret1 = text1.loadFont("ARCADE.ttf", 30);
    bool ret2 = text2.loadFont("ARCADE.ttf", 30);
    if(!ret1 || !ret2) return -1;
    text1.Settext(text1_);
    text2.Settext(text2_);
    text1.SettextColor(255, 215, 0);
    text2.SettextColor(255, 215, 0);
    BaseObject::Render(render_);
    int x;
    int y;
    while(1){
        text1.renderTexture(render_, 100, 500, 200, 100);
        text2.renderTexture(render_, 900, 500, 200, 100);
        while(SDL_PollEvent(&event_)){
            switch(event_.type)
            {
                case SDL_QUIT:
                    return -1;
                    break;
                case SDL_MOUSEMOTION:
                    x = event_.motion.x;
                    y = event_.motion.y;
                    if(x>=100 && x<=300 && y>=500 && y<=600){
                        text1.SettextColor(255, 0, 0);
                    }
                    else if(x>=900 && x<=1100 && y>=500 && y<=600){
                        text2.SettextColor(255, 0, 0);
                    }
                    else{
                        text1.SettextColor(255, 215, 0);
                        text2.SettextColor(255, 215, 0);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x = event_.button.x;
                    y = event_.button.y;
                    if(x>=100 && x<=300 && y>=500 && y<=600){
                        BaseObject::Free();
                        return -1;
                    }
                    if(x>=900 && x<=1100 && y>=500 && y<=600){
                        BaseObject::Free();
                        return 3;
                    }
                    break;
            }
        }
        SDL_RenderPresent(render_);
    }
}

int Pause::RenderPause(SDL_Renderer* render_)
{
    bool ret1 = continue_.loadImage(render_, "img//continue.png");
    bool ret2 = exit_.loadImage(render_, "img//exit.png");
    if(!ret1 || !ret2) return -1;
    continue_.SetRect(SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT/2-50);
    exit_.SetRect(SCREEN_WIDTH/2 + 50, SCREEN_HEIGHT/2-50);
    int x;
    int y;
    while(1){
        continue_.Render(render_);
        exit_.Render(render_);
        SDL_Rect rect_continue = continue_.GetRect();
        SDL_Rect rect_exit = exit_.GetRect();
        while(SDL_PollEvent(&event_)){
            switch (event_.type)
            {
                case SDL_QUIT:
                    continue_.Free();
                    exit_.Free();
                    return -1;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x = event_.button.x;
                    y = event_.button.y;
                    if(x>=rect_continue.x && x<=rect_continue.x+rect_continue.w && y>=rect_continue.y && y<=rect_continue.y+rect_continue.h){
                        continue_.Free();
                        exit_.Free();
                        SDL_Delay(500);
                        return 1;
                    }
                    else if(x>=rect_exit.x && x<=rect_exit.x+rect_exit.w && y>=rect_exit.y && y<=rect_exit.y+rect_exit.h){
                        continue_.Free();
                        exit_.Free();
                        return 2;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    x = event_.motion.x;
                    y = event_.motion.y;
                    if(x>=rect_continue.x && x<=rect_continue.x+rect_continue.w && y>=rect_continue.y && y<=rect_continue.y+rect_continue.h){
                        SDL_Rect res = {SCREEN_WIDTH/2 - 160, SCREEN_HEIGHT/2 - 60, 120, 120};
                        continue_.Set_Rect(res);
                    }else if(x>=rect_exit.x && x<=rect_exit.x+rect_exit.w && y>=rect_exit.y && y<=rect_exit.y+rect_exit.h){
                        SDL_Rect res = {SCREEN_WIDTH/2 + 40, SCREEN_HEIGHT/2 - 60, 120, 120};
                        exit_.Set_Rect(res);
                    }else{
                        SDL_Rect res1 = {SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT/2 - 50, 100, 100};
                        SDL_Rect res2 = {SCREEN_WIDTH/2 + 50, SCREEN_HEIGHT/2 -50, 100, 100};
                        continue_.Set_Rect(res1);
                        exit_.Set_Rect(res2);
                    }
                    break;
            }
        }
        SDL_RenderPresent(render_);
    }
}
