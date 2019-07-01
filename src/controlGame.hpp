/*
** EPITECH PROJECT, 2019
** controlGame
** File description:
** controlGame
*/

#ifndef CONTROLGAME_HPP_
#define CONTROLGAME_HPP_

#include <irrlicht.h>
#include <locale>
#include <codecvt>
#include <string>
#include <vector>
#include <iostream>
#include "Map.hpp"
#include "Game.hpp"
#include "EventManager.hpp"

using namespace irr;
using namespace core;
using namespace video;
using namespace io;
using namespace gui;
using namespace scene;
using namespace std;

class gameMenu;

class controlGame {
public:
    controlGame(int width, int height, IrrlichtDevice *device, ISceneManager *smgr, IVideoDriver *driver, IGUIEnvironment *gui, EventManager &receiver);
    ~controlGame();
    void restart(Map *map, Game *game, gameMenu *menu);
    void quit(Map *map, Game *game, gameMenu *menu);
    void createMenu();
    void deleteMenu();
    bool displayMenu();
    void displayHelp();
    void buttonsVisibility(bool state);
    bool controlLoop();

private:
    EventManager &_receiver;
    int _width;
    int _height;
    IrrlichtDevice *_device;
    ISceneManager *_smgr;
    IVideoDriver *_driver;
    IGUIEnvironment *_gui;
    vector<IGUIButton *> _MenuButtons;
    vector<ITexture *> _imagesMenu;
};


#endif /* !CONTROLGAME_HPP_ */
