#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_net.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <bits/stdc++.h>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;

static SDL_Window* window_ = NULL;
static SDL_Renderer* render_ = NULL;
static SDL_Event event_;
static bool is_paused = false;
static int index = 6;
static int bird2_;
static int bird3_;
#define BIRD_1 1
#define BIRD_2 2
#define BIRD_3 3
#define TO_BACK 4
#define CONTINUE 5
#define EXIT 6
#define SHOP 7
#define PRICE_BIRD2 100
#define PRICE_BIRD3 500

#endif // DEFINE_H_INCLUDED
