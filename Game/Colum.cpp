#include "BaseObject.h"
#include "Colum.h"

int pos[7]={1000, 1300, 1600, 1850, 2150, 2400, 2650};
Colum::Colum()
{
    x_pos_=0;
    y_pos_=0;
    is_back=false;
}
Colum::~Colum()
{

}

bool Colum::LoadColum(SDL_Renderer* render_, std::string file_name)
{
    bool ret = BaseObject::loadImage(render_, file_name);
    return ret;
}

void Colum::SetPos(const int &xp, const int &yp)
{
    this->SetRect(xp, yp);
}

void Colum::SetXpos(const int &xp)
{
    SDL_Rect rect = this->GetRect();
    this->SetRect(xp, rect.y);
}

void Colum::ShowColum(SDL_Renderer* render_)
{
    this->Render(render_);
}
SDL_Rect Colum::GetRectColum() const
{
    return this->GetRect();
}

void Colum::Run(int x_val)
{
    rect_.x += x_val;
    if(rect_.x + rect_.w < 0) is_back = true;
}

bool Colum::Getisback()
{
    return is_back;
}

void Colum::Setisback(bool ib)
{
    is_back = ib;
}

DoubleColum::DoubleColum()
{
    x_run = -3;
    is_back_ = false;
}

bool DoubleColum::InitColum(SDL_Renderer* render_, const int &xp)
{
    bool ret1= top_colum.LoadColum(render_, "img//top_colum.png");
    bool ret2= bottom_colum.LoadColum(render_, "img//bottom_colum.png");
    int topx = -520 + rand()%311 + 70;
    int bottomx = topx + 520 + 130 + rand()%31;
    top_colum.SetPos(xp, topx);
    bottom_colum.SetPos(xp, bottomx);
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

SDL_Rect DoubleColum::GetTopRect()
{
    return top_colum.GetRectColum();
}

bool DoubleColum::Getisback_()
{
    return is_back_;
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

ColumList::ColumList()
{
    end_list=0;
}

bool ColumList::InitColumList(SDL_Renderer* render_)
{
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
//    Colum_list[0].ShowDoubleColum(render_);
    for(int i=0; i<Colum_list.size(); i++){
        DoubleColum* cl = Colum_list.at(i);
        cl->Move();
        if(cl->Getisback_()){
            DoubleColum* endcl = Colum_list.at(end_list);
            SDL_Rect end_rect = endcl->GetTopRect();
            int xp = end_rect.x + rand()%70 + 180;
            cl->SetX(xp);
            cl->Setisback_(false);
            end_list = i;
        }

        cl->ShowDoubleColum(render_);
    }
}

void ColumList::SetBird_rect(SDL_Rect bird_rect)
{
    Bird_rect = bird_rect;
}

