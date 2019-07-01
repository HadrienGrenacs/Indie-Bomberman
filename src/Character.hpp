/*
** EPITECH PROJECT, 2019
** Character
** File description:
** Character
*/

#ifndef CHARACTER_HPP_
#define CHARACTER_HPP_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <irrlicht.h>
#include <memory>
#include "EventManager.hpp"
#include "Bomb.hpp"
#include "Map.hpp"
#include "Explosion.hpp"

using namespace irr;
using namespace core;
using namespace video;
using namespace io;
using namespace gui;
using namespace scene;

enum direction {
    NONE,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Character {
	public:
		Character(IrrlichtDevice *device, EventManager const &receiver, Map &map , vector3df const &pos, const path &texture, EKEY_CODE keyUp, EKEY_CODE keyDown, EKEY_CODE keyLeft, EKEY_CODE keyRight, EKEY_CODE keyBomb);
		~Character();
        static Character *getCharacterFromNode(ISceneNode const *node);
        void addBomb();
        void addSpeed();
        void addRange();
        void update();
        bool move();
        void addCollision(IAnimatedMeshSceneNode *model);
        IAnimatedMeshSceneNode* getModel();
        void placeBomb();
        void checkBomb();
        void checkExplo();
        void checkDeath();
        void setPlayers(std::vector<Character *> tabPlayers);
        bool isBombAtPos(f32 posX, f32 posZ);
        vector3df getCenterPos();
        bool isDead();
    
	private:
        Map &_map;
        IrrlichtDevice *_device;
        IAnimatedMeshSceneNode *_model;
        vector3df const &_pos;
        f32 _speed;
        EventManager const &_receiver;
        u32 _now;
        u32 _then;
        f32 _frameDeltaTime;
        direction _direction;
        EKEY_CODE _keyUp;
        EKEY_CODE _keyDown;
        EKEY_CODE _keyLeft;
        EKEY_CODE _keyRight;
        EKEY_CODE _keyBomb;
        ITriangleSelector *_selector;
        int _maxBomb;
        int _bombPower;
        static std::vector<Character*> _tabPlayers;
        std::vector<Bomb*> _tabBomb;
        std::vector<CrossExplo*> _tabExplo;
        bool _isDead;
};

#endif /* !CHARACTER_HPP_ */
