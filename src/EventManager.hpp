/*
** EPITECH PROJECT, 2019
** Event
** File description:
** Event
*/

#ifndef EVENTMANAGER_HPP_
#define EVENTMANAGER_HPP_

#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace video;
using namespace io;
using namespace gui;
using namespace scene;

class EventManager : public IEventReceiver {
    public:
        bool OnEvent(const SEvent &event);
        bool IsKeyDown(EKEY_CODE const keyCode) const;
        bool IsKeyPressed(EKEY_CODE const keyCode) const;
        void resetKeyIsPressed(void);
        EventManager();
        ~EventManager();

    private:
        bool KeyIsDown[KEY_KEY_CODES_COUNT];
        bool KeyIsPressed[KEY_KEY_CODES_COUNT];
};

#endif /* !EVENTMANAGER_HPP_ */
