/*
** EPITECH PROJECT, 2019
** bomn
** File description:
** bomb
*/

#ifndef BOMB_HPP_
#define BOMB_HPP_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <irrlicht.h>
#include <SFML/Audio.hpp>
#include <algorithm>
#include "Map.hpp"
#include "APowerUp.hpp"
#include "Explosion.hpp"

using namespace irr;
using namespace core;
using namespace video;
using namespace io;
using namespace gui;
using namespace scene;
using namespace std;

class Character;

class Bomb {
	public:
		Bomb(IrrlichtDevice *device, IAnimatedMeshSceneNode *player, u32 timePlaced);
		~Bomb();
        void setCoord(IAnimatedMeshSceneNode*);
        void plantBomb();
        vector3df getPos();
        void addCollision(IAnimatedMeshSceneNode *model);
        void setCollided(bool value);
        bool getCollided();
        u32 getTimePlaced();
        void explode(Map &map, int bombPower, std::vector<Character *> tabPlayers);
        void blowDirection(Map &map, unsigned int const bombPower, vector3df const &dir, std::vector<Character *> tabPlayers);

	private:
        IrrlichtDevice *_device;
        ISceneManager *_smgr;
        IAnimatedMeshSceneNode *_bomb;
        vector3df _pos;
        ITriangleSelector *_selector;
        bool _isCollided;
        u32 _timePlaced;
        IParticleSystemSceneNode *_particleSystem;
        vector<Explosion*> _tabExplo;
        sf::SoundBuffer _bufferPlace;
        sf::Sound _soundPlace;
};

#endif /* !Bomb */
