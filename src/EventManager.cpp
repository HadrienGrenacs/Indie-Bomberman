/*
** EPITECH PROJECT, 2019
** Event
** File description:
** Event
*/

#include "EventManager.hpp"

bool EventManager::OnEvent(const SEvent &event)
{
    if (event.EventType == EET_KEY_INPUT_EVENT)
    {
        if (event.KeyInput.PressedDown && !KeyIsDown[event.KeyInput.Key])
            KeyIsPressed[event.KeyInput.Key] = true;
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    }
    return (false);
}

bool EventManager::IsKeyPressed(EKEY_CODE keyCode) const
{
    return (KeyIsPressed[keyCode]);
}

bool EventManager::IsKeyDown(EKEY_CODE keyCode) const
{
    return (KeyIsDown[keyCode]);
}

void EventManager::resetKeyIsPressed(void)
{
    for (int i = 0; i < KEY_KEY_CODES_COUNT; ++i)
        KeyIsPressed[i] = false;
}

EventManager::EventManager()
{
    for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
        KeyIsDown[i] = false;
    for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
        KeyIsPressed[i] = false;
}

EventManager::~EventManager()
{
}