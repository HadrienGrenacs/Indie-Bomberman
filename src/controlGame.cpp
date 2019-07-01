/*
** EPITECH PROJECT, 2019
** controlGame
** File description:
** controlGame
*/

#include "gameMenu.hpp"
#include "controlGame.hpp"

controlGame::controlGame(int width, int height, IrrlichtDevice *device, ISceneManager *smgr, IVideoDriver *driver, IGUIEnvironment *gui, EventManager &receiver) : _receiver(receiver)
{
    _width = width;
    _height = height;
    _device = device;
    _smgr = smgr;
    _driver = driver;
    _gui = gui;
    _imagesMenu.push_back(_driver->getTexture("../media/Play.png"));
    _imagesMenu.push_back(_driver->getTexture("../media/Help.png"));
    _imagesMenu.push_back(_driver->getTexture("../media/Exit.png"));
}

controlGame::~controlGame()
{
}

void controlGame::deleteMenu()
{
    if (!_MenuButtons.empty())
    {
        _MenuButtons[0]->remove();
        _MenuButtons[1]->remove();
        _MenuButtons[2]->remove();
        _MenuButtons.clear();
    }
}

void controlGame::restart(Map *map, Game *game, gameMenu *menu)
{
    APowerUp::clearAllPowerUp();
    _driver->endScene();
    _gui->clear();
    delete(game);
    delete(map);
    delete(menu);
    _smgr->clear();
    controlLoop();
    return;
}

void controlGame::quit(Map *map, Game *game, gameMenu *menu)
{
    APowerUp::clearAllPowerUp();
    _driver->endScene();
    _gui->clear();
    createMenu();
    delete(game);
    delete(map);
    delete(menu);
    _smgr->clear();
    return;
}

bool controlGame::controlLoop()
{
    int nbPlayers = 2;
    int action = 0;
    int i = 0;
    Map *map = new Map(_device);
    Game *game = new Game(_width, _height, _device, _driver, _receiver, *map, nbPlayers, _smgr);  
    gameMenu *menu = new gameMenu(_width, _height, _device, _smgr, _driver, _gui, _receiver);

    menu->createMenu();
    game->createGame();
    while (_device->run()) {
        _driver->beginScene(true, true, SColor(0, 0, 0, 0));
        if (game->checkWin() == 0 && !(_receiver.IsKeyDown(KEY_ESCAPE))) {
            game->runGame();
            _device->getCursorControl()->setVisible(false);
        } else {
            deleteMenu();
            while (_device->run()) {
                if (game->checkWin() == 1) {
                    _gui->addImage(_driver->getTexture("../media/player1.png"), position2di(_width / 2.8, _height / 3.1));
                    i = 1;
                } else if (game->checkWin() == 2) {
                    _gui->addImage(_driver->getTexture("../media/player2.png"), position2di(_width / 2.8, _height / 3.1));
                    i = 1;
                }
                _device->getCursorControl()->setVisible(true);
                _driver->beginScene(true, true, SColor(0, 0, 0, 0));
                action = menu->displayMenu(i);
                if (action == 1) {
                    menu->buttonsVisibility(false);
                    break;
                }
                if (action == 2) {
                    restart(map, game, menu);
                    return (false);
                }
                if (action == 3) {
                    quit(map, game, menu);
                    return (false);
                }
                _gui->drawAll();
                _driver->endScene();
                _receiver.resetKeyIsPressed();
            }
        }
        _smgr->drawAll();
        _gui->drawAll();
        _driver->endScene();
        _receiver.resetKeyIsPressed();
    }
    return (true);
}

void controlGame::createMenu()
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

void controlGame::buttonsVisibility(bool state)
{
    for (int i = 0; i < _MenuButtons.size(); i++) {
        _MenuButtons[i]->setVisible(state);
    }
}

void controlGame::displayHelp()
{
    char c;
    std::ifstream file("../media/info.txt");
    std::string str;

    if (!file)
        str = "Veuillez remplir un fichier info.txt dans le répertoire media";
    else {
        while (file.get(c))
            str += c;
    }

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wstr = converter.from_bytes(str);
    const wchar_t *cstr = wstr.c_str();

    IGUIStaticText *texte = _gui->addStaticText(cstr, rect<s32>(500, 50, 500 + 920, 50 + 800), true, true, 0, -1, true);
    IGUIFont *font = _gui->getFont("../media/fontlucida.png");
    texte->setOverrideFont(font); 
    texte->setBackgroundColor(SColor(150, 0, 0, 0));
    texte->setOverrideColor(SColor(255, 255, 255, 255));
    texte->setTextAlignment(EGUIA_CENTER, EGUIA_CENTER);

    IGUIButton *retour = _gui->addButton(rect<s32>(880, 870, 880 + 180, 870 + 50));
    retour->setImage(_driver->getTexture("../media/Exit.png"));
    retour->setUseAlphaChannel(true);
    retour->setDrawBorder(0);
    retour->setIsPushButton();

    while (_device->run() && retour->isPressed() != true)
    {
        _driver->beginScene(true, true, SColor(0, 200, 200, 200));
        _driver->draw2DImage(_driver->getTexture("../media/bomberman.jpg"),
		       rect<s32>(0, 0, _width, _height),
		       rect<s32>(0, 0, _width, _height));
        _gui->drawAll();
        _driver->endScene();
    }
    texte->remove();
    retour->remove();
}

bool controlGame::displayMenu()
{
    _driver->draw2DImage(_driver->getTexture("../media/bomberman.jpg"),
		       rect<s32>(0, 0, _width, _height),
		       rect<s32>(0, 0, _width, _height));
    buttonsVisibility(true);
    if (_MenuButtons[0]->isPressed()) {
        _MenuButtons[0]->setPressed(false);
        buttonsVisibility(false);
        controlLoop();
    } else if (_MenuButtons[1]->isPressed()) {
        _MenuButtons[1]->setPressed(false);
        buttonsVisibility(false);
        displayHelp();
        buttonsVisibility(true);
    } else if (_MenuButtons[2]->isPressed()) {
        _MenuButtons[2]->setPressed(false);
        return (true);
    }
    return (false);
}