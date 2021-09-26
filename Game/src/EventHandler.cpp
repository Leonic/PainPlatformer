#include "EventHandler.h"
#include "Game.h"

EventHandler* EventHandler::s_pInstance = 0;

EventHandler::EventHandler()
{}

void EventHandler::onMouseButtonDown(SDL_Event e)
{
}

void EventHandler::onMouseButtonUp(SDL_Event e)
{
}

void EventHandler::onKeyDown(SDL_Event e)
{
}

void EventHandler::onKeyUp(SDL_Event e)
{
}

void EventHandler::onFingerDown(SDL_Event e)
{
}

void EventHandler::onFingerUp(SDL_Event e)
{
}

void EventHandler::OnThink()
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {

        switch (e.type)
        {

        case SDL_QUIT:
            Game::Instance()->Quit();
            break;

        case SDL_MOUSEBUTTONDOWN:
            onMouseButtonDown(e);
            break;

        case SDL_MOUSEBUTTONUP:
            onMouseButtonUp(e);
            break;

        case SDL_FINGERDOWN:
            onFingerDown(e);
            break;

        case SDL_FINGERUP:
            onFingerUp(e);
            break;

        case SDL_KEYDOWN:
            onKeyDown(e);
            break;

        case SDL_KEYUP:
            onKeyUp(e);
            break;
        }
    }
}

void EventHandler::Destroy()
{}