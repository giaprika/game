#ifndef BIRD_H_INCLUDED
#define BIRD_H_INCLUDED

#include "BaseObject.h"
class Bird : public BaseObject
{
private:
    int x_val_;
    int y_val_;
public:
    Bird();
    ~Bird();
    void HandleInputAction(SDL_Event events);
    void Run();
};




#endif // BIRD_H_INCLUDED
