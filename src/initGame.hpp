/*
** EPITECH PROJECT, 2019
** initGame
** File description:
** initGame
*/

#ifndef INITGAME_HPP_
#define INITGAME_HPP_

#include <irrlicht.h>
#include <stdexcept>
#include "EventManager.hpp"
#include "controlGame.hpp"

using namespace irr;
using namespace core;
using namespace video;
using namespace io;
using namespace gui;
using namespace scene;
using namespace std;

class initGame
{
public:
    initGame(int width, int height);
    ~initGame();
    int loop();

private:
    int _width;
    int _height;
    IrrlichtDevice *_device;
    ISceneManager *_smgr;
    IVideoDriver *_driver;
    IGUIEnvironment *_gui;
    EventManager _receiver;
};

#endif /* !INITGAME_HPP_ */
