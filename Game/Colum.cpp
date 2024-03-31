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
