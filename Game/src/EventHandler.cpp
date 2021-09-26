#include "EventHandler.h"
#include "Game.h"
#include <iostream>

CEventHandler* CEventHandler::s_pInstance = 0;

CEventHandler::CEventHandler()
{
    std::cout << "(CEventHandler::CEventHandler) CEventHandler created." << std::endl;
}

CEventHandler::~CEventHandler()
{
    Destroy();
}

void CEventHandler::onMouseButtonDown(SDL_Event e)
{
    if (m_mouseDownCallbacks.size() != 0)
    {
        for (size_t i = 0; i < m_mouseDownCallbacks.size(); i++)
        {
            m_mouseDownCallbacks[i](e);
        }
    }
}

void CEventHandler::onMouseButtonUp(SDL_Event e)
{
    if (m_mouseUpCallbacks.size() != 0)
    {
        for (size_t i = 0; i < m_mouseUpCallbacks.size(); i++)
        {
            m_mouseUpCallbacks[i](e);
        }
    }
}

void CEventHandler::onKeyDown(SDL_Event e)
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

void CEventHandler::onKeyUp(SDL_Event e)
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

void CEventHandler::onFingerDown(SDL_Event e)
{
    if (m_fingerDownCallbacks.size() != 0)
    {
        for (size_t i = 0; i < m_fingerDownCallbacks.size(); i++)
        {
            m_fingerDownCallbacks[i](e);
        }
    }
}

void CEventHandler::onFingerUp(SDL_Event e)
{
    if (m_fingerUpCallbacks.size() != 0)
    {
        for (size_t i = 0; i < m_fingerUpCallbacks.size(); i++)
        {
            m_fingerUpCallbacks[i](e);
        }
    }
}

void CEventHandler::OnThink()
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {

        switch (e.type)
        {

        case SDL_QUIT:
            CGame::Instance()->Quit();
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

void CEventHandler::Destroy()
{
    // Clean up
    m_keyDownCallbacks.clear();
    m_keyUpCallbacks.clear();

    m_mouseDownCallbacks.clear();
    m_mouseUpCallbacks.clear();

    m_fingerDownCallbacks.clear();
    m_fingerUpCallbacks.clear();
}

void CEventHandler::AddOnKeyDown(HKeyCallback callBack)
{
    m_keyDownCallbacks.push_back(callBack);
}

void CEventHandler::AddOnKeyUp(HKeyCallback callBack)
{
    m_keyUpCallbacks.push_back(callBack);
}

void CEventHandler::AddOnMouseDown(HInputCallback callBack)
{
    m_mouseDownCallbacks.push_back(callBack);
}

void CEventHandler::AddOnMouseUp(HInputCallback callBack)
{
    m_mouseUpCallbacks.push_back(callBack);
}

void CEventHandler::AddOnFingerDown(HInputCallback callBack)
{
    m_fingerDownCallbacks.push_back(callBack);
}

void CEventHandler::AddOnFingerUp(HInputCallback callBack)
{
    m_fingerUpCallbacks.push_back(callBack);
}

void CEventHandler::RemoveOnKeyDown(HKeyCallback callBack)
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

void CEventHandler::RemoveOnKeyUp(HKeyCallback callBack)
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

void CEventHandler::RemoveOnMouseDown(HInputCallback callBack)
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

void CEventHandler::RemoveOnMouseUp(HInputCallback callBack)
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

void CEventHandler::RemoveOnFingerDown(HInputCallback callBack)
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

void CEventHandler::RemoveOnFingerUp(HInputCallback callBack)
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