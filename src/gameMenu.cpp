/*
** EPITECH PROJECT, 2019
** gameMenu
** File description:
** gameMenu
*/

#include "gameMenu.hpp"

gameMenu::gameMenu(int width, int height, IrrlichtDevice *device, ISceneManager *smgr, IVideoDriver *driver, IGUIEnvironment *gui, EventManager receiver) : _receiver(receiver)
{
    _width = width;
    _height = height;
    _device = device;
    _smgr = smgr;
    _driver = driver;
    _gui = gui;
    _imagesMenu.push_back(_driver->getTexture("../media/Resume.png"));
    _imagesMenu.push_back(_driver->getTexture("../media/Restart.png"));
    _imagesMenu.push_back(_driver->getTexture("../media/Exit.png"));
}

gameMenu::~gameMenu()
{
}

void gameMenu::createMenu()
{
    int dif = _height / 3;

    for (int i = 0; i < 3; i++) {
        _MenuButtons.push_back(_gui->addButton(rect<s32>(_width / 2.3, dif - _height / 16, _width / 1.8, dif += _height / 10)));
        _MenuButtons[i]->setImage(_imagesMenu[i]);
        _MenuButtons[i]->setUseAlphaChannel(true);
        _MenuButtons[i]->setDrawBorder(0);
        _MenuButtons[i]->setIsPushButton();
        _MenuButtons[i]->setVisible(false);
    }
}

void gameMenu::buttonsVisibility(bool state)
{
    for (int i = 0; i < _MenuButtons.size(); i++) {
        _MenuButtons[i]->setVisible(state);
    }
}

int gameMenu::displayMenu(int i)
{
    buttonsVisibility(true);
    if (i == 1)
        _MenuButtons[0]->setVisible(false);
    while (_device->run()) {
        _driver->beginScene(true, true, SColor(0, 0, 0, 0));
        _driver->draw2DImage(_driver->getTexture("../media/menu.jpg"),
		       rect<s32>(0, 0, _width, _height),
		       rect<s32>(0, 0, _width, _height));
        if (_MenuButtons[0]->isPressed()) {
            _MenuButtons[0]->setPressed(false);
            return (1);
        } else if (_MenuButtons[1]->isPressed()) {
            _MenuButtons[1]->setPressed(false);
            return (2);
        } else if (_MenuButtons[2]->isPressed()) {
            _MenuButtons[2]->setPressed(false);
            return (3);
        }

        _gui->drawAll();
        _driver->endScene();
        _receiver.resetKeyIsPressed();
    }
    return (0);
}