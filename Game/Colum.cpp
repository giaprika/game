#include "BaseObject.h"
#include "Colum.h"
Colum::Colum()
{
    x_pos_=0;
    y_pos_=0;
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
}

DoubleColum::DoubleColum()
{
    x_run = -3;
}

bool DoubleColum::InitColum(SDL_Renderer* render_)
{
    bool ret1= top_colum.LoadColum(render_, "top_colum.png");
    bool ret2= bottom_colum.LoadColum(render_, "bottom_colum.png");
    top_colum.SetPos(1000, -300);
    bottom_colum.SetPos(1000, 400);
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
}

