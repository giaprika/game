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
    bool LoadColum(SDL_Renderer* render_, std::string file_name);
    void ShowColum(SDL_Renderer* render_);
    void SetPos(const int &xp, const int &yp);
    void SetXpos(const int &xp);
    SDL_Rect GetRectColum() const;
    void Run(int x_val);
    bool Getisback() const {return is_back;}
    void Setisback(bool ib);
    void UpDown(bool &is_upping, SDL_Rect &rect_to_updown, int y_);
    void FreeColum();
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
    SDL_Rect GetTopRect() const;
    bool Getisback_() const {return is_back_;}
    void Setisback_(bool ib_);
    bool CheckCollision(const SDL_Rect &rect);
    bool CheckPass(const SDL_Rect &rect);
    bool Getispass() const {return is_pass_;}
    void Setispass(bool pass) {is_pass_ = pass;}
    void SetPassrect();
    SDL_Rect GetPassrect() const {return pass_rect;}
    void UpDown_(bool &is_upping);
    void FreeDoubleColum();
};

class ColumList
{
private:
    std::vector<DoubleColum*> Colum_list;
    int end_list;
    SDL_Rect Bird_rect;
    bool die;
    Mix_Music *music;
    int score;
    bool saved_;
    bool just_lose_save;

public:
    ColumList();
    bool InitColumList(SDL_Renderer* render_);
    void ShowList(SDL_Renderer* render_);
    void SetBird_rect(SDL_Rect bird_rect);
    std::vector<DoubleColum*> GetList() {return Colum_list;}
    bool Getdie() const {return die;}
    void Setdie(bool die_) {die = die_;}
    int Getscore() const {return score;}
    void Setsaved_(bool saved) {saved_ = saved;}
    bool Getsaved_()const {return saved_;}
    SDL_Rect GetBird_rect() const {return Bird_rect;}
    void waitUntilKeyPressed();
    void pauseMusic() { Mix_PauseMusic(); }
    void resumeMusic() { Mix_ResumeMusic(); }
    void freeMusic() { Mix_FreeMusic(music); }
    void FreeColumList();
    void List_UpDown();
    bool Get_just_lose_save() const {return just_lose_save;}
    void Set_just_lose_save(bool res) {just_lose_save = res;}
    int Getend_list() const {return end_list;}
};

class Save : BaseObject
{
private:
    bool is_looted;
public:
    Save();
    bool LoadSave(SDL_Renderer* render_, std::string filename);
    void ShowSave(SDL_Renderer* render_);
    void SetRectSave (SDL_Rect rect) {rect_ = rect;}
    void SaveMove() {rect_.x -= 3;}
    bool GetIs_Looted() const {return is_looted;}
    void SetIs_Looted(bool loot) {is_looted = loot;}
    void FreeSave();

};

#endif // COLUM_H_INCLUDED
