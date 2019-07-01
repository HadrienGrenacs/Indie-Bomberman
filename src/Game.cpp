/*
** EPITECH PROJECT, 2019
** Game
** File description:
** Game
*/

#include "Game.hpp"

Game::Game(int width, int height, IrrlichtDevice *device, IVideoDriver *driver, EventManager &receiver, Map &map, int nbPlayers, ISceneManager *smgr) : _map(map), _receiver(receiver)
{
    _width = width;
    _height = height;
    _device = device;
    _driver = driver;
    _nbPlayers = nbPlayers;
    _smgr = smgr;
}

Game::~Game()
{
}


int Game::checkWin()
{
    if (_tabPlayers[0]->isDead() == true)
        return (2);
    else if (_tabPlayers[1]->isDead() == true)
        return (1);
    else
        return (0);
}

void Game::runGame()
{
    std::for_each(_tabPlayers.begin(), _tabPlayers.end(),
				  [](Character* test) {
					  test->update();
				  });
    APowerUp::checkPowerUp();
}

void Game::createBackground()
{
    IMeshSceneNode *left = _smgr->addCubeSceneNode(70, 0, -1, vector3df(-65, -30, 90), vector3df(0, 270, 0), vector3df(1, 0, 1));
    IMeshSceneNode *right = _smgr->addCubeSceneNode(70, 0, -1, vector3df(180, -30, 30), vector3df(0, 270, 0), vector3df(1, 0, 1));

	left->setMaterialFlag(EMF_LIGHTING, false);
	left->setMaterialTexture(0, _driver->getTexture("../media/bomberman_left.png"));
	right->setMaterialFlag(EMF_LIGHTING, false);
	right->setMaterialTexture(0, _driver->getTexture("../media/bomberman_right.png"));
}

void Game::createGame()
{
    createBackground();
    _tabPlayers.push_back(new Character(_device, _receiver, _map, vector3df(7, 1, 7*16), "../media/player", KEY_KEY_Z, KEY_KEY_S, KEY_KEY_Q, KEY_KEY_D, KEY_SPACE));
    _tabPlayers.push_back(new Character(_device, _receiver, _map, vector3df(7*16, 1, 7), "../media/faerie", KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_KEY_M));
//    _tabPlayers.push_back(new Character(_device, _receiver, _map, vector3df(7, 1, 7), KEY_KEY_Z, KEY_KEY_S, KEY_KEY_Q, KEY_KEY_D, KEY_SPACE));
//    _tabPlayers.push_back(new Character(_device, _receiver, _map, vector3df(7*16, 1, 7*16), KEY_KEY_Z, KEY_KEY_S, KEY_KEY_Q, KEY_KEY_D, KEY_SPACE));

    for (int i = 0; i < _tabPlayers.size(); i++) {
        for (int j = 0; j < _tabPlayers.size(); j++) {
            if (i != j)
                _tabPlayers[i]->addCollision(_tabPlayers[j]->getModel());
        }
    }
    for (int i = 0; i < _tabPlayers.size(); i++) {
        _tabPlayers[i]->setPlayers(_tabPlayers);
        _map.addCollision(_tabPlayers[i]->getModel());
    }
}