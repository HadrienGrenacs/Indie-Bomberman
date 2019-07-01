/*
** EPITECH PROJECT, 2019
** Game
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <irrlicht.h>
#include "EventManager.hpp"
#include "Map.hpp"
#include "Character.hpp"

using namespace irr;
using namespace core;
using namespace video;
using namespace io;
using namespace gui;
using namespace scene;
using namespace std;

class Game
{
public:
    Game(int width, int height, IrrlichtDevice *device, IVideoDriver *driver, EventManager &receiver, Map &map, int nbPlayers, ISceneManager *smgr);
    ~Game();
    int checkWin();
    void createBackground();
    void createGame();
    void runGame();

protected:
private:
    int _nbPlayers;
    int _height;
    int _width;
    Map &_map;
    IrrlichtDevice *_device;
    IVideoDriver *_driver;
    ISceneManager *_smgr;
    EventManager &_receiver;
    std::vector<Character *> _tabPlayers;
};

#endif /* !GAME_HPP_ */
