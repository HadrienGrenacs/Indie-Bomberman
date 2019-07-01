/*
** EPITECH PROJECT, 2019
** gameMenu
** File description:
** gameMenu
*/

#ifndef GAMEMENU_HPP_
#define GAMEMENU_HPP_

#include <irrlicht.h>
#include <vector>
#include <iostream>
#include "EventManager.hpp"

using namespace irr;
using namespace core;
using namespace video;
using namespace io;
using namespace gui;
using namespace scene;
using namespace std;

class gameMenu {
public:
    gameMenu(int width, int height, IrrlichtDevice *device, ISceneManager *smgr, IVideoDriver *driver, IGUIEnvironment *gui, EventManager receiver);
    ~gameMenu();
    void createMenu();
    int displayMenu(int i);
    void buttonsVisibility(bool state);
private:
    EventManager &_receiver;
    int _width;
    int _height;
    IrrlichtDevice *_device;
    ISceneManager *_smgr;
    IVideoDriver *_driver;
    IGUIEnvironment *_gui;
    vector<ITexture *> _imagesMenu;
    vector<IGUIButton *> _MenuButtons;
};

#endif /* !GAMEMENU_HPP_ */
