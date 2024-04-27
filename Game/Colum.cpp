#include "BaseObject.h"
#include "Colum.h"

int pos[7]={1000, 1300, 1600, 1850, 2150, 2400, 2650};
bool is_upping[7] = {true, true, false, true, false, false, true};
Colum::Colum()
{
    x_pos_=0;
    y_pos_=0;
    is_back=false;
}
Colum::~Colum()
{
    BaseObject::Free();
}

bool Colum::LoadColum(SDL_Renderer* render_, std::string file_name)
{
    bool ret = BaseObject::loadImage(render_, file_name);
    return ret;
}

void Colum::SetPos(const int &xp, const int &yp)
{
    BaseObject::SetRect(xp, yp);
}

void Colum::SetXpos(const int &xp)
{
    SDL_Rect rect = BaseObject::GetRect();
    BaseObject::SetRect(xp, rect.y);
}

void Colum::ShowColum(SDL_Renderer* render_)
{
    BaseObject::Render(render_);
}

SDL_Rect Colum::GetRectColum() const
{
    return BaseObject::GetRect();
}

void Colum::Run(int x_val)
{
    if(!is_paused){
        rect_.x += x_val;
        if(rect_.x + rect_.w < 0) is_back = true;
    }
}

void Colum::Setisback(bool ib)
{
    is_back = ib;
}

void Colum::UpDown(bool &is_upping, SDL_Rect &rect_to_updown, int y_)
{
    if(is_upping){
        rect_.y -= y_;
        if(rect_to_updown.y <= 0) is_upping = false;
    }else{
        rect_.y += y_;
        if(rect_to_updown.y + rect_to_updown.h >= SCREEN_HEIGHT) is_upping = true;
    }
}

DoubleColum::DoubleColum()
{
    x_run = -3;
    is_back_ = false;
    is_pass_ = false;
}

bool DoubleColum::InitColum(SDL_Renderer* render_, const int &xp)
{
    bool ret1= top_colum.LoadColum(render_, "img//top_colum.png");
    bool ret2= bottom_colum.LoadColum(render_, "img//bottom_colum.png");

    int topy = -520 + rand()%311 + 70;
    int bottomy = topy + 520 + 150 + rand()%21;
    top_colum.SetPos(xp, topy);
    bottom_colum.SetPos(xp, bottomy);

    if(ret1 && ret2) return true;
    else return false;
}

void DoubleColum::ShowDoubleColum(SDL_Renderer* render_)
{
    top_colum.ShowColum(render_);
    bottom_colum.ShowColum(render_);
}

void DoubleColum::Move()
{
    top_colum.Run(x_run);
    bottom_colum.Run(x_run);
    if(top_colum.Getisback() || bottom_colum.Getisback()){
        is_back_ = true;
    }
}

void DoubleColum::SetX(const int &xp)
{
    top_colum.SetXpos(xp);
    bottom_colum.SetXpos(xp);
}

SDL_Rect DoubleColum::GetTopRect() const
{
    return top_colum.GetRectColum();
}

void DoubleColum::Setisback_(bool ib_)
{
    is_back_ = ib_;
    top_colum.Setisback(ib_);
    bottom_colum.Setisback(ib_);
}

bool DoubleColum::CheckCollision(const SDL_Rect &rect)
{
    SDL_Rect rect1 = top_colum.GetRectColum();
    SDL_Rect rect2 = bottom_colum.GetRectColum();
    bool ret1 = SDL_HasIntersection(&rect1, &rect);
    bool ret2 = SDL_HasIntersection(&rect2, &rect);
    return (ret1 || ret2);
}

bool DoubleColum::CheckPass(const SDL_Rect &rect)
{
    bool ret = SDL_HasIntersection(&pass_rect, &rect);
    return ret;
}

void DoubleColum::SetPassrect()
{
    SDL_Rect top = top_colum.GetRectColum();
    SDL_Rect bottom = bottom_colum.GetRectColum();
    pass_rect.x = top.x + top.w + 64;
    pass_rect.y = top.y + top.h;
    pass_rect.w = 1;
    pass_rect.h = bottom.y - (top.y + top.h);
}

void DoubleColum::UpDown_(bool &is_upping)
{
    int y_ = rand() % 3;
    top_colum.UpDown(is_upping, pass_rect, y_);
    bottom_colum.UpDown(is_upping, pass_rect, y_);
}

ColumList::ColumList()
{
    end_list=0;
    die = false;
    music = nullptr;
    score = 0;
    saved_ = false;
    Bird_rect = {0, 0, 0, 0}; /**/
}

bool ColumList::InitColumList(SDL_Renderer* render_)
{
    music = Mix_LoadMUS("sound//nhacnen.mp3");
    if(music == nullptr) return false;


    DoubleColum* colum1 = new DoubleColum();
    DoubleColum* colum2 = new DoubleColum();
    DoubleColum* colum3 = new DoubleColum();
    DoubleColum* colum4 = new DoubleColum();
    DoubleColum* colum5 = new DoubleColum();
    DoubleColum* colum6 = new DoubleColum();
    DoubleColum* colum7 = new DoubleColum();

    bool ret1 = colum1->InitColum(render_, pos[0]);
    bool ret2 = colum2->InitColum(render_, pos[1]);
    bool ret3 = colum3->InitColum(render_, pos[2]);
    bool ret4 = colum4->InitColum(render_, pos[3]);
    bool ret5 = colum5->InitColum(render_, pos[4]);
    bool ret6 = colum6->InitColum(render_, pos[5]);
    bool ret7 = colum7->InitColum(render_, pos[6]);

    Colum_list.push_back(colum1);
    Colum_list.push_back(colum2);
    Colum_list.push_back(colum3);
    Colum_list.push_back(colum4);
    Colum_list.push_back(colum5);
    Colum_list.push_back(colum6);
    Colum_list.push_back(colum7);

    end_list = 6;

    if(ret1 && ret2 && ret3 && ret4 && ret5 && ret6 && ret7) return true;
    else return false;
}

void ColumList::ShowList(SDL_Renderer* render_)
{
    if (Mix_PlayingMusic() == 0){
           Mix_PlayMusic( music, -1 );
    }
    if(Bird_rect.y + Bird_rect.h <0 || Bird_rect.y > SCREEN_HEIGHT){
        Mix_FreeMusic(music);
        Mix_Chunk* gChunk = Mix_LoadWAV("sound//out.wav");
            if (gChunk != nullptr) {
                Mix_PlayChannel( -1, gChunk, 0 );
            }
        die = true;
    }

    for(int i=0; i<(int)Colum_list.size(); i++){
        DoubleColum* cl = Colum_list.at(i);
        cl->SetPassrect();
        cl->Move();

        if(cl->Getisback_()){
            DoubleColum* endcl = Colum_list.at(end_list);
            SDL_Rect end_rect = endcl->GetTopRect();
            int xp = end_rect.x + rand()%20 + 230;
            cl->SetX(xp);
            cl->Setisback_(false);
            cl->Setispass(false);
            end_list = i;
        }
        SDL_Rect MinRectBird = {Bird_rect.x, Bird_rect.y + 5, Bird_rect.w - 5, Bird_rect.h -10};
        if(cl->CheckCollision(MinRectBird)){

            if(saved_){
                Mix_Chunk* gChunk = Mix_LoadWAV("sound//vobong.wav");
                if(gChunk != nullptr){
                    Mix_PlayChannel(-1, gChunk, 0);
                }
                SDL_Rect res = cl->GetPassrect();
                Bird_rect.y = res.y + 50;
                SDL_Delay(500);
                saved_ = false;
            }else{
                die = true;
                Mix_Chunk* gChunk = Mix_LoadWAV("sound//collide.wav");
                if (gChunk != nullptr) {
                    Mix_PlayChannel( -1, gChunk, 0 );
                }
                Mix_FreeMusic(music);
            }
        }
        if(cl->CheckPass(Bird_rect)){
            if(cl->Getispass() == false){
                Mix_Chunk* ting = Mix_LoadWAV("sound//ting.wav");
                if (ting != NULL)  Mix_PlayChannel(-1, ting, 0);
                score++;
                cl->Setispass(true);
            }
        }
        cl->ShowDoubleColum(render_);
    }
}

void ColumList::SetBird_rect(SDL_Rect bird_rect)
{
    Bird_rect = bird_rect;
}

Save::Save()
{
    is_looted = false;
}

void ColumList::freeColum()
{
    for(int i=0; i<(int)Colum_list.size(); i++){
        delete Colum_list.at(i);
    }
    Colum_list.clear();
}

void ColumList::List_UpDown()
{
    for(int i=0; i<(int)Colum_list.size(); i++){
        Colum_list.at(i)->UpDown_(is_upping[i]);
    }
}

bool Save::LoadSave(SDL_Renderer* render_, std::string filename)
{
    bool ret = BaseObject::loadImage(render_, filename);
    return ret;
}

void Save::ShowSave(SDL_Renderer* render_)
{
    BaseObject::Render(render_);
}
