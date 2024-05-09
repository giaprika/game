#include "Define.h"
#include "BaseObject.h"
#include "Bird.h"
#include "Colum.h"
#include "Menu&Score.h"
#include "GetFromFile.h"
#include <fstream>
bool Init()
{
    int ret = SDL_Init(SDL_INIT_EVERYTHING);
    if (ret < 0) return false;
    window_ = SDL_CreateWindow("Plappy Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(window_ == NULL) return false;
    render_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(render_ == NULL) return false;
    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) return false;
    if(TTF_Init() == -1) return false;
    return true;
}

void close()
{
    SDL_DestroyRenderer(render_);
    render_ = NULL;
    SDL_DestroyWindow(window_);
    window_ = NULL;
    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}

int high_score;
int money;

int main(int argc, char* argv[])
{
    srand(time(NULL));
    BaseObject bk_grd;
    if(Init() == false){
        close();
        return 0;
    }
    bool quit=false;
    bool menu_show = true;
    while(!quit){
        Menu menu;
        bool ret_ = menu.loadFont("font.ttf");
        if(!ret_) quit = true;
        int ret_menu;
        money = Get_From_File("money.txt");
        if(menu_show){
            ret_menu = menu.ShowMenu(render_,"img//MENU.png", "Play Game", "Exit", "", "");
            if(ret_menu == -1){
                close();
                return 0;
            }
        }
        Pause pause;
        Bird bird;
        if(ret_menu != -1){
            ret_menu = TO_BACK;
            while(ret_menu == TO_BACK){
                bird2_ = Get_From_File("bird2.txt");
                bird3_ = Get_From_File("bird3.txt");
                ret_menu = menu.ChooseBird(render_, "Bird 1", "Bird 2", "Exit", "Rule", "Bird 3", "Shop", bird2_, bird3_);
                if(ret_menu == TO_BACK) ret_menu = menu.ShowRule(render_, "Exit", "Back");
                if(ret_menu == SHOP) ret_menu = menu.ShowShop(render_, "Back", money, bird2_, bird3_);
                Write_To_File("money.txt", money);
            }
        }
        if(ret_menu == -1){
            close();
            return 0;
        }
        bool ret1, ret2;
        if(ret_menu == BIRD_1){
            ret1 = bk_grd.loadImage(render_, "img//bk_ground1.jpg");
            ret2 = bird.LoadBird(render_, "img//bird1_1.png", "img//bird1_2.png", "img//bird1_3.png");
        }
        if(ret_menu == BIRD_2){
            ret1 = bk_grd.loadImage(render_, "img//bk_ground2.png");
            ret2 = bird.LoadBird(render_, "img//bird2_1.png", "img//bird2_2.png", "img//bird2_3.png");
        }
        if(ret_menu == BIRD_3){
            ret1 = bk_grd.loadImage(render_, "img//bk_ground2.png");
            ret2 = bird.LoadBird(render_, "img//bird3_1.png", "img//bird3_2.png", "img//bird3_3.png");
        }
        if(!ret1 || !ret2){
            close();
            return 0;
        }
        bird.SetRect(100, 100);

        ColumList colum_;
        bool ret = colum_.InitColumList(render_);
        if(ret == false){
            close();
            return 0;
        }
        ret = colum_.init_coin(render_);
        if(!ret){
            close();
            return 0;
        }

        Text text_score;
        ret = text_score.loadFont("fonttt.ttf", 40);
        if(ret==false){
            close();
            return 0;
        }

        Text text_coin;
        ret = text_coin.loadFont("fonttt.ttf", 40);
        if(ret==false) return 0;
        text_coin.SettextColor(150, 80, 0);

        Save Mangbv;
        ret = Mangbv.LoadSave(render_, "img//save.png");
        if (ret == false){
            close();
            return 0;
        }
        high_score = Get_From_File("high_score.txt");
        while(!colum_.Getdie()){
            while (SDL_PollEvent(&event_) != 0)
            {
                if (event_.type == SDL_QUIT)
                {
                    quit = true;
                }
                if(event_.type == SDL_KEYDOWN)
                    if(event_.key.keysym.sym == SDLK_SPACE){
                            is_paused = true;
                    }
                bird.HandleInputAction(event_);
            }
            bk_grd.Render(render_);
            bird.Run();

            colum_.SetBird_rect(bird.GetRect());
            colum_.Setsaved_(bird.GetIs_saved());
            colum_.ShowList(render_);
            bird.SetIs_saved(colum_.Getsaved_());
            bird.SetRect_(colum_.GetBird_rect().x, colum_.GetBird_rect().y);

            if(colum_.Getdie()){
                bird.Rendertext3(render_);
            }else{
                bird.RenderBird(render_);
            }

            colum_.Render_text_coin(render_);
            colum_.Render_coin_base(render_);
            text_score.RenderRectScore(render_);
            int diem = colum_.Getscore();
            std::string diemso = std::to_string(diem);
            text_score.Settext(diemso.c_str());
            text_score.renderTexture(render_, SCREEN_WIDTH/2, 2, 50, 50);

            int so_coin = colum_.Get_cnt_coin();
            std::string number_coin = std::to_string(so_coin);
            text_coin.Settext(number_coin.c_str());
            text_coin.renderTexture(render_, 60, 95, 40, 40);

            if(diem >= 10){
                SDL_Rect rectsave;
                SDL_Rect birdrect = bird.GetRect();
                if(!Mangbv.GetIs_Looted()){
                    std::vector<DoubleColum*> listcolum = colum_.GetList();
                    if(colum_.Get_just_lose_save()){
                        index = colum_.Getend_list();
                        colum_.Set_just_lose_save(false);
                    }
                    rectsave = listcolum[index]->GetPassrect();
                    rectsave = {rectsave.x-128, rectsave.y + 40, 70, 70};
                    if(SDL_HasIntersection(&rectsave, &birdrect)){
                        Mix_Chunk* gChunk = Mix_LoadWAV("sound//vobong.wav");
                        if(gChunk != nullptr){
                            Mix_PlayChannel(-1, gChunk, 0);
                        }
                        Mangbv.SetIs_Looted(true);
                        bird.SetIs_saved(true);
                    }
                    Mangbv.SetRectSave(rectsave);
                    Mangbv.ShowSave(render_);
                }
                else if(bird.GetIs_saved()){

                    rectsave = {birdrect.x - 10, birdrect.y - 20, 90, 85};
                    Mangbv.SetRectSave(rectsave);
                    Mangbv.ShowSave(render_);
                }
                Mangbv.SetIs_Looted(bird.GetIs_saved());
            }

            if(diem > 10) colum_.List_UpDown();

            if(is_paused){
                colum_.pauseMusic();
                int ret_pause = pause.RenderPause(render_);
                if(ret_pause == CONTINUE){
                    is_paused = false;
                    colum_.resumeMusic();
                }
                if(ret_pause == -1){
                    pause.FreePause();
                    bird.FreeBird();
                    colum_.FreeColumList();
                    text_score.FreeText();
                    Mangbv.FreeSave();
                    quit = true;
                    break;
                }
                if(ret_pause == EXIT){
                    is_paused = false;
                    colum_.Setdie(true);
                    colum_.freeMusic();
                }
            }

            SDL_RenderPresent(render_);
            if(colum_.Getdie()){
                SDL_Delay(1000);
                money += so_coin;
                Write_To_File("money.txt", money);
                if(diem > high_score){
                    high_score = diem;
                    Write_To_File("high_score.txt", diem);
                }
                std::string highscore = "High Score: " + std::to_string(high_score);
                std::string score = "Score: " + diemso;
                int ret_menu = menu.ShowMenu(render_,"img//gameover.png", "Play Again", "Exit", score.c_str(), highscore.c_str());
                if(ret_menu == -1){
                    pause.FreePause();
                    bird.FreeBird();
                    colum_.FreeColumList();
                    text_score.FreeText();
                    Mangbv.FreeSave();
                    quit = true;
                    continue;
                }
                if(ret_menu == 1){
                    pause.FreePause();
                    bird.FreeBird();
                    colum_.FreeColumList();
                    text_score.FreeText();
                    Mangbv.FreeSave();
                    menu_show = false;
                }
            }
        }
    }
    close();
    return 0;
}
