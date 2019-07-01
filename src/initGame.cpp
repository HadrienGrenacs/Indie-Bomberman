/*
** EPITECH PROJECT, 2019
** initGame
** File description:
** initGame
*/

#include "initGame.hpp"

initGame::initGame(int width, int height) : _width(width), _height(height), _receiver()
{
    if (!(_device = createDevice(EDT_OPENGL, dimension2d<u32>(width, height), 32, false, true, false, &_receiver)))
        throw runtime_error("Error loading device");
    _device->setWindowCaption(L"Bomberman");
    _smgr = _device->getSceneManager();
    _driver = _device->getVideoDriver();
    _gui = _device->getGUIEnvironment();
}

initGame::~initGame()
{
    _smgr->clear();
    _device->drop();
}

int initGame::loop()
{
    sf::SoundBuffer buffer;
    sf::Sound sound;
    bool end = false;
    controlGame game(_width, _height, _device, _smgr, _driver, _gui, _receiver);

    game.createMenu();
    if (!(buffer.loadFromFile("../media/background.wav")))
        throw runtime_error("Error finding background.wav");
    sound.setBuffer(buffer);
    sound.play();
    sound.setLoop(true);

    while (_device->run() && !end) {
        _driver->beginScene(true, true, SColor(0, 0, 0, 0));
        end = game.displayMenu();
        _smgr->drawAll();
        _gui->drawAll();
        _driver->endScene();
        _receiver.resetKeyIsPressed();
    }
    return (0);
}
