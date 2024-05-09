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

void Text::FreeText()
{
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

Menu::Menu()
{
    _gchunk_ = Mix_LoadWAV("sound//click.wav");
}

bool Menu::loadFont(const char* filename)
{
    bool ret1 = text1.loadFont(filename, 30);
    bool ret2 = text2.loadFont(filename, 30);
    bool ret3 = text3.loadFont(filename, 30);
    bool ret4 = text4.loadFont(filename, 30);
    bool ret5 = text5.loadFont(filename, 30);
    bool ret6 = text6.loadFont(filename, 30);
}

int Menu::ShowMenu(SDL_Renderer* render_, std::string filename, const char* text1_, const char* text2_,
                   const char* text3_, const char* text4_, const char* text5_)
{
    bool ret = BaseObject::loadImage(render_, filename);
    if(!ret) return -1;
    text1.Settext(text1_);
    text2.Settext(text2_);
    text3.Settext(text3_);
    text4.Settext(text4_);
    text5.Settext(text5_);

    text3.SettextColor(0, 255, 255);
    text4.SettextColor(255, 255, 0);
    text5.SettextColor(150, 80, 0);

    BaseObject::Render(render_);
    int x=0;
    int y=0;

    while(1)
    {
        SDL_GetMouseState(&x, &y);
        if(x>=780 && x<=1080 && y>=300 && y<=400){
            text2.SettextColor(255, 0, 0);
        }
        else if(x>=230 && x<=630 && y>=300 && y<=400){
            text1.SettextColor(255, 0 ,0);
        }
        else{
            text1.SettextColor(255, 255, 255);
            text2.SettextColor(255, 255, 255);
        }
        text1.renderTexture(render_, 230, 300, 400, 80);
        text2.renderTexture(render_, 780, 300, 200, 80);
        text3.renderTexture(render_, 780, 180, 400, 80);
        text4.renderTexture(render_, 130, 180, 500, 80);
        text5.renderTexture(render_, 640, 470, 80, 80);
        while(SDL_PollEvent(&event_))
        {
            switch(event_.type)
            {
            case SDL_QUIT:
                return -1;
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = event_.button.x;
                y = event_.button.y;
                if(x>=780 && x<=1080 && y>=300 && y<=380){
                    Mix_PlayChannel(-1, _gchunk_, 0);
                    BaseObject::Free();
                    return -1;
                }
                if(x>=230 && x<=630 && y>=300 && y<=380){
                    Mix_PlayChannel(-1, _gchunk_, 0);
                    BaseObject::Free();
                    return 1;
                }
                break;

            }
        }
        SDL_RenderPresent(render_);
    }
}

int Menu::ChooseBird(SDL_Renderer* render_, const char* text1_, const char* text2_, const char* text3_, const char* text4_,
                      const char* text5_, const char* text6_, int& bird2_, int &bird3_)
{
    bool ret = BaseObject::loadImage(render_, "img//choosebirds.png");
    if(!ret) return -1;
    text1.Settext(text1_);
    text2.Settext(text2_);
    text3.Settext(text3_);
    text4.Settext(text4_);
    text5.Settext(text5_);
    text6.Settext(text6_);

    BaseObject::Render(render_);
    int x=0;
    int y=0;

    while(1)
    {
        SDL_GetMouseState(&x, &y);
        if(x>=100 && x<=325 && y>=200 && y<=270){
            text1.SettextColor(255, 228, 181);
        }
        else if(x>=470 && x<=695 && y>=200 && y<=270){
            if(bird2_ == 1) text2.SettextColor(255, 105 ,180);
        }
        else if(x>=330 && x<=530 && y>=420 && y<=490){
            text3.SettextColor(255, 0, 0);
        }
        else if(x>=700 && x<=900 && y>=420 &&y<=490){
            text4.SettextColor(255, 0, 0);
        }
        else if(x>=830 && x<=1055 && y>=200 && y<=270){
            if(bird3_ == 1) text5.SettextColor(0, 160, 100);
        }
        else if(x>=500 && x<=700 && y>=540 && y<=610){
            text6.SettextColor(255, 0, 0);
        }
        else{
            text1.SettextColor(255, 255, 255);
            if(bird2_ ==1) text2.SettextColor(255, 255, 255);
            text3.SettextColor(255, 255, 255);
            text4.SettextColor(255, 255, 255);
            if(bird3_ ==1) text5.SettextColor(255, 255, 255);
            text6.SettextColor(255, 255, 255);
        }
        text1.renderTexture(render_, 100, 225, 200, 70);
        text2.renderTexture(render_, 470, 225, 200, 70);
        text3.renderTexture(render_, 330, 420, 200, 70);
        text4.renderTexture(render_, 700, 420, 200, 70);
        text5.renderTexture(render_, 830, 225, 200, 70);
        text6.renderTexture(render_, 500, 540, 200, 70);
        if(bird2_ == 0){
            text2.SettextColor(50, 50, 50);
        }
        if(bird3_ == 0){
            text5.SettextColor(50, 50, 50);
        }

        while(SDL_PollEvent(&event_))
        {
            switch(event_.type)
            {
            case SDL_QUIT:
                return -1;
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = event_.button.x;
                y = event_.button.y;
                if(x>=100 && x<=325 && y>=200 && y<=270){
                    Mix_PlayChannel(-1, _gchunk_, 0);
                    BaseObject::Free();
                    return BIRD_1;
                }
                if(x>=470 && x<=695 && y>=200 && y<=270){
                    if(bird2_ == 1){
                        Mix_PlayChannel(-1, _gchunk_, 0);
                        BaseObject::Free();
                        return BIRD_2;
                    }
                }
                if(x>=830 && x<=1055 && y>=200 && y<= 270){
                    if(bird3_ == 1){
                        Mix_PlayChannel(-1, _gchunk_, 0);
                        BaseObject::Free();
                        return BIRD_3;
                    }
                }
                if(x>=330 && x<=530 && y>=420 && y<=490){
                    Mix_PlayChannel(-1, _gchunk_, 0);
                    BaseObject::Free();
                    return -1;
                }
                if(x>=700 && x<=900 && y>=420 &&y<=490){
                    Mix_PlayChannel(-1, _gchunk_, 0);
                    BaseObject::Free();
                    return TO_BACK;
                }
                if(x>=500 && x<=700 && y>=540 && y<=610){
                    Mix_PlayChannel(-1, _gchunk_, 0);
                    BaseObject::Free();
                    return SHOP;
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
    text1.Settext(text1_);
    text2.Settext(text2_);
    text1.SettextColor(255, 215, 0);
    text2.SettextColor(255, 215, 0);
    BaseObject::Render(render_);
    int x;
    int y;
    while(1){
        SDL_GetMouseState(&x, &y);
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
        text1.renderTexture(render_, 100, 500, 200, 100);
        text2.renderTexture(render_, 900, 500, 200, 100);
        while(SDL_PollEvent(&event_)){
            switch(event_.type)
            {
                case SDL_QUIT:
                    return -1;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x = event_.button.x;
                    y = event_.button.y;
                    if(x>=100 && x<=300 && y>=500 && y<=600){
                        Mix_PlayChannel(-1, _gchunk_, 0);
                        BaseObject::Free();
                        return -1;
                    }
                    if(x>=900 && x<=1100 && y>=500 && y<=600){
                        Mix_PlayChannel(-1, _gchunk_, 0);
                        BaseObject::Free();
                        return TO_BACK;
                    }
                    break;
            }
        }
        SDL_RenderPresent(render_);
    }
}

int Menu::ShowShop(SDL_Renderer* render_, const char* text_, int& coin_money, int& bird2_, int& bird3_)
{
    bool ret = BaseObject::loadImage(render_, "img//shop.png");
    if(!ret) return -1;
    BaseObject::Render(render_);

    int x, y;
    text3.Settext(text_);
    while(1){
        std::string money_ = std::to_string(coin_money);
        text4.Settext(money_.c_str());
        text4.SettextColor(150, 80, 0);

        text3.renderTexture(render_, 930, 520, 200, 80);
        text4.renderTexture(render_, 140, 520, 80, 80);

        std::ifstream file2("bird2.txt");
        file2 >> bird2_;
        file2.close();
        std::ifstream file3("bird3.txt");
        file3 >> bird3_;
        file3.close();
//        bird2_ = Get_From_File("bird2.txt");
//        bird3_ = Get_From_File("bird3.txt");
        SDL_GetMouseState(&x, &y);
        if(x>=280 && x<=480 && y>=320 && y<=400){
            if(bird2_ == 0 && coin_money >=PRICE_BIRD2){
                text1.SettextColor(255, 0, 0);
            }
        }
        else if(x>=860 && x<=1060 && y>=320 && y<=400){
            if(bird3_ == 0 && coin_money >=PRICE_BIRD3){
                text2.SettextColor(255, 0, 0);
            }
        }
        else if(x>=930 && x<=1130 && y>=520 && y<=600){
            text3.SettextColor(255, 0, 0);
        }
        else{
            if(bird2_ == 0){
                text1.SettextColor(255, 255, 255);
            }
            if(bird3_ == 0){
                text2.SettextColor(255, 255, 255);
            }
            text3.SettextColor(255, 255, 255);
        }
        if(bird2_ == 0){
            text1.Settext("Buy it");
            if(coin_money < PRICE_BIRD2){
                text1.SettextColor(50, 50, 50);
            }
        }else{
            text1.Settext("Received");
            text1.SettextColor(250, 200, 120);
        }
        if(bird3_ == 0){
            text2.Settext("Buy it");
            if(coin_money < PRICE_BIRD3){
                text2.SettextColor(50, 50, 50);
            }
        }else{
            text2.Settext("Received");
            text2.SettextColor(250, 200, 120);
        }

        text1.renderTexture(render_, 280, 320, 200, 80);
        text2.renderTexture(render_, 860, 320, 200, 80);
        while(SDL_PollEvent(&event_)){
            switch(event_.type)
            {
                case SDL_QUIT:
                    return -1;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x = event_.motion.x;
                    y = event_.motion.y;
                    if(x>=930 && x<=1130 && y>=520 && y<=600){
                        Mix_PlayChannel(-1, _gchunk_, 0);
                        BaseObject::Free();
                        return TO_BACK;
                    }
                    if(x>=280 && x<=480 && y>=320 && y<=400){
                        if(bird2_ == 0 && coin_money>=PRICE_BIRD2){
                            coin_money -= PRICE_BIRD2;
                            Mix_PlayChannel(-1, _gchunk_, 0);
                            std::ofstream file2("bird2.txt");
                            file2 << 1;
                            file2.close();
//                            Write_To_File("bird2.txt", 1);
                            return TO_BACK;
                        }
                    }
                    if(x>=860 && x<=1060 && y>=320 && y<=400){
                        if(bird3_ == 0 && coin_money>=PRICE_BIRD3){
                            coin_money -= PRICE_BIRD3;
                            Mix_PlayChannel(-1, _gchunk_, 0);
                            std::ofstream file3("bird3.txt");
                            file3 << 1;
                            file3.close();
//                            Write_To_File("bird3.txt", 1);
                            return TO_BACK;
                        }
                    }
                    break;
            }
        }
        SDL_RenderPresent(render_);
    }
}

void Menu::FreeMenu()
{
    BaseObject::Free();
    text1.FreeText();
    text2.FreeText();
    text3.FreeText();
    text4.FreeText();
    text5.FreeText();
    text6.FreeText();
    Mix_FreeChunk(_gchunk_);
}

Pause::Pause()
{
    gchunk_ = Mix_LoadWAV("sound//click.wav");
}

int Pause::RenderPause(SDL_Renderer* render_)
{
    bool ret1 = continue_.loadImage(render_, "img//p1.png");
    bool ret2 = exit_.loadImage(render_, "img//e1.png");
    bool ret3 = pause_game.loadImage(render_, "img//pause.png");
    if(!ret1 || !ret2 || !ret3) return -1;
    continue_.SetRect(SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT/2-50);
    exit_.SetRect(SCREEN_WIDTH/2 + 50, SCREEN_HEIGHT/2-50);
    pause_game.SetRect(SCREEN_WIDTH/2 - 250 , SCREEN_HEIGHT/2 - 145);
    int x;
    int y;
    while(1){
        SDL_Rect rect_continue = continue_.GetRect();
        SDL_Rect rect_exit = exit_.GetRect();
        SDL_GetMouseState(&x, &y);
        if(x>=rect_continue.x && x<=rect_continue.x+rect_continue.w && y>=rect_continue.y && y<=rect_continue.y+rect_continue.h){
            ret1 = continue_.loadImage(render_, "img//p2.png");
        }else if(x>=rect_exit.x && x<=rect_exit.x+rect_exit.w && y>=rect_exit.y && y<=rect_exit.y+rect_exit.h){
            ret2 = exit_.loadImage(render_, "img//e2.png");
        }else{
            ret1 = continue_.loadImage(render_, "img//p1.png");
            ret2 = exit_.loadImage(render_, "img//e1.png");
        }
        pause_game.Render(render_);
        continue_.Render(render_);
        exit_.Render(render_);

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
                        Mix_PlayChannel(-1, gchunk_, 0);
                        continue_.Free();
                        exit_.Free();
                        SDL_Delay(500);
                        return CONTINUE;
                    }
                    else if(x>=rect_exit.x && x<=rect_exit.x+rect_exit.w && y>=rect_exit.y && y<=rect_exit.y+rect_exit.h){
                        Mix_PlayChannel(-1, gchunk_, 0);
                        continue_.Free();
                        exit_.Free();
                        return EXIT;
                    }
                    break;
            }
        }
        SDL_RenderPresent(render_);
    }
}

void Pause::FreePause()
{
    continue_.Free();
    exit_.Free();
    Mix_FreeChunk(gchunk_);
}
