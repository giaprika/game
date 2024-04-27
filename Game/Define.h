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
#endif // DEFINE_H_INCLUDED
