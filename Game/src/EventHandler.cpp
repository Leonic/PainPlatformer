#include "EventHandler.h"
#include "Game.h"
#include <iostream>

EventHandler* EventHandler::s_pInstance = 0;

EventHandler::EventHandler()
{
    std::cout << "EventHandler created." << std::endl;
}

EventHandler::~EventHandler()
{
    Destroy();
}

void EventHandler::onMouseButtonDown(SDL_Event e)
{
    if (m_mouseDownCallbacks.size() != 0)
    {
        for (size_t i = 0; i < m_mouseDownCallbacks.size(); i++)
        {
            m_mouseDownCallbacks[i](e);
        }
    }
}

void EventHandler::onMouseButtonUp(SDL_Event e)
{
    if (m_mouseUpCallbacks.size() != 0)
    {
        for (size_t i = 0; i < m_mouseUpCallbacks.size(); i++)
        {
            m_mouseUpCallbacks[i](e);
        }
    }
}

void EventHandler::onKeyDown(SDL_Event e)
{
    m_keystates = (Uint8*)SDL_GetKeyboardState(0);

    if (m_keyDownCallbacks.size() != 0)
    {
        for (size_t i = 0; i < m_keyDownCallbacks.size(); i++)
        {
            m_keyDownCallbacks[i]();
        }
    }
}

void EventHandler::onKeyUp(SDL_Event e)
{
    m_keystates = (Uint8*)SDL_GetKeyboardState(0);

    if (m_keyUpCallbacks.size() != 0)
    {
        for (size_t i = 0; i < m_keyUpCallbacks.size(); i++)
        {
            m_keyUpCallbacks[i]();
        }
    }
}

void EventHandler::onFingerDown(SDL_Event e)
{
    if (m_fingerDownCallbacks.size() != 0)
    {
        for (size_t i = 0; i < m_fingerDownCallbacks.size(); i++)
        {
            m_fingerDownCallbacks[i](e);
        }
    }
}

void EventHandler::onFingerUp(SDL_Event e)
{
    if (m_fingerUpCallbacks.size() != 0)
    {
        for (size_t i = 0; i < m_fingerUpCallbacks.size(); i++)
        {
            m_fingerUpCallbacks[i](e);
        }
    }
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
{
    // Clean up
    m_keyDownCallbacks.clear();
    m_keyUpCallbacks.clear();

    m_mouseDownCallbacks.clear();
    m_mouseUpCallbacks.clear();

    m_fingerDownCallbacks.clear();
    m_fingerUpCallbacks.clear();
}

void EventHandler::AddOnKeyDown(HKeyCallback callBack)
{
    m_keyDownCallbacks.push_back(callBack);
}

void EventHandler::AddOnKeyUp(HKeyCallback callBack)
{
    m_keyUpCallbacks.push_back(callBack);
}

void EventHandler::AddOnMouseDown(HInputCallback callBack)
{
    m_mouseDownCallbacks.push_back(callBack);
}

void EventHandler::AddOnMouseUp(HInputCallback callBack)
{
    m_mouseUpCallbacks.push_back(callBack);
}

void EventHandler::AddOnFingerDown(HInputCallback callBack)
{
    m_fingerDownCallbacks.push_back(callBack);
}

void EventHandler::AddOnFingerUp(HInputCallback callBack)
{
    m_fingerUpCallbacks.push_back(callBack);
}

void EventHandler::RemoveOnKeyDown(HKeyCallback callBack)
{
    for (size_t i = 0; i < m_keyDownCallbacks.size(); i++)
    {
        if (m_keyDownCallbacks[i].target<SDL_Scancode>() == callBack.target<SDL_Scancode>())
        {
            m_keyDownCallbacks.erase(m_keyDownCallbacks.begin() + i);
            break;
        }
    }
}

void EventHandler::RemoveOnKeyUp(HKeyCallback callBack)
{
    for (size_t i = 0; i < m_keyUpCallbacks.size(); i++)
    {
        if (m_keyUpCallbacks[i].target<SDL_Scancode>() == callBack.target<SDL_Scancode>())
        {
            m_keyUpCallbacks.erase(m_keyUpCallbacks.begin() + i);
            break;
        }
    }
}

void EventHandler::RemoveOnMouseDown(HInputCallback callBack)
{
    for (size_t i = 0; i < m_mouseDownCallbacks.size(); i++)
    {
        if (m_mouseDownCallbacks[i].target<SDL_Event>() == callBack.target<SDL_Event>())
        {
            m_mouseDownCallbacks.erase(m_mouseDownCallbacks.begin() + i);
            break;
        }
    }
}

void EventHandler::RemoveOnMouseUp(HInputCallback callBack)
{
    for (size_t i = 0; i < m_mouseUpCallbacks.size(); i++)
    {
        if (m_mouseUpCallbacks[i].target<SDL_Event>() == callBack.target<SDL_Event>())
        {
            m_mouseUpCallbacks.erase(m_mouseUpCallbacks.begin() + i);
            break;
        }
    }
}

void EventHandler::RemoveOnFingerDown(HInputCallback callBack)
{
    for (size_t i = 0; i < m_fingerDownCallbacks.size(); i++)
    {
        if (m_fingerDownCallbacks[i].target<SDL_Event>() == callBack.target<SDL_Event>())
        {
            m_fingerDownCallbacks.erase(m_fingerDownCallbacks.begin() + i);
            break;
        }
    }
}

void EventHandler::RemoveOnFingerUp(HInputCallback callBack)
{
    for (size_t i = 0; i < m_fingerUpCallbacks.size(); i++)
    {
        if (m_fingerUpCallbacks[i].target<SDL_Event>() == callBack.target<SDL_Event>())
        {
            m_fingerUpCallbacks.erase(m_fingerUpCallbacks.begin() + i);
            break;
        }
    }
}
