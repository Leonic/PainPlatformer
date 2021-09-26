#pragma once
#ifndef __ENGINETYPES_H__
#define __ENGINETYPES_H__

#include <functional>
#include <SDL2/SDL.h>

// Just to abrevate these long std::function defs
typedef std::function<void()> HKeyCallback;
typedef std::function<void(SDL_Event)> HInputCallback;

#endif