#ifndef COLUM_H_INCLUDED
#define COLUM_H_INCLUDED

#include "BaseObject.h"
class Colum : BaseObject
{
private:
    int x_pos_;
    int y_pos_;
    bool is_back;
public:
    Colum();
    ~Colum();
    bool LoadColum(SDL_Renderer* render_, std::string file_name);
    void ShowColum(SDL_Renderer* render_);
    void SetPos(const int &xp, const int &yp);
    void SetXpos(const int &xp);
    SDL_Rect GetRectColum() const;
    void Run(int x_val);
    bool Getisback();
    void Setisback(bool ib);
};

class DoubleColum
{
private:
    Colum top_colum;
    Colum bottom_colum;
    int x_run;
    bool is_back_;
    bool is_pass_;
    SDL_Rect pass_rect;
public:
    DoubleColum();
    bool InitColum(SDL_Renderer* render_, const int &xp);
    void ShowDoubleColum(SDL_Renderer* render_);
    void Move();
    void SetX(const int &xp);
    SDL_Rect GetTopRect();
    bool Getisback_();
    void Setisback_(bool ib_);
    bool CheckCollision(const SDL_Rect &rect);
    bool CheckPass(const SDL_Rect &rect);
    bool Getispass() {return is_pass_;}
    void Setispass(bool pass) {is_pass_ = pass;}
    void SetPassrect();
};

class ColumList
{
private:
    std::vector<DoubleColum*> Colum_list;
    int end_list;
    SDL_Rect Bird_rect;
    bool die;
    Mix_Music *music;
public:
    ColumList();
    bool InitColumList(SDL_Renderer* render_);
    void ShowList(SDL_Renderer* render_);
    void SetBird_rect(SDL_Rect bird_rect);
    std::vector<DoubleColum*> GetList() {return Colum_list;}
    bool Getdie() {return die;}
};

#endif // COLUM_H_INCLUDED
