#ifndef COLUM_H_INCLUDED
#define COLUM_H_INCLUDED

#include "BaseObject.h"
class Colum : BaseObject
{
private:
    int x_pos_;
    int y_pos_;
public:
    Colum();
    ~Colum();
    bool LoadColum(SDL_Renderer* render_, std::string file_name);
    void ShowColum(SDL_Renderer* render_);
    void SetPos(const int &xp, const int &yp);
    SDL_Rect GetRectColum() const;
    void Run(int x_val);
};

#endif // COLUM_H_INCLUDED
