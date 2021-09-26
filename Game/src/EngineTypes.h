#pragma once
#ifndef __ENGINETYPES_H__
#define __ENGINETYPES_H__

#include <functional>
#include <SDL2/SDL.h>

#define WIDTH 1280
#define HEIGHT 720

class BaseObject;

// Just to abrevate these long std::function defs
typedef std::function<void()> HKeyCallback;
typedef std::function<void(SDL_Event)> HInputCallback;

typedef std::function<void(BaseObject)> HOverlapEvent;

#endif