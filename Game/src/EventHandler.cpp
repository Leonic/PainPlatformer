#include "EventHandler.h"
#include "Game.h"

EventHandler* EventHandler::s_pInstance = 0;

EventHandler::EventHandler()
{}

void EventHandler::OnThink()
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            Game::Instance()->Quit();
        }
    }
}

void EventHandler::Destroy()
{}