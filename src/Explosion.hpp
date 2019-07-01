/*
** EPITECH PROJECT, 2019
** Explosion
** File description:
** Explosion
*/

#ifndef EXPLOSION_HPP_
#define EXPLOSION_HPP_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <irrlicht.h>
#include <algorithm>
#include "Map.hpp"
#include <SFML/Audio.hpp>

using namespace irr;
using namespace core;
using namespace video;
using namespace io;
using namespace gui;
using namespace scene;
using namespace std;

class Explosion {
    public:
        Explosion(IrrlichtDevice *device, vector3df const &pos);
        ~Explosion();
        void removeExplosion();
        vector3df getPos();

    private:
        u32 _timeStarted;
        ISceneManager *_smgr;
        IParticleSystemSceneNode *_particleSystem;
        vector3df _pos;
};

class CrossExplo {
    public:
        CrossExplo(IrrlichtDevice *device, Map &map, vector3df const &pos, int bombPower, u32 initialTime);
        ~CrossExplo();
        void exploDirection(Map &map, int bombPower, vector3df const &dir);
        u32 getTimePlaced();
        void removeExplosion();
        vector3df getPos();
        bool checkPos(vector3df pos);

    private:
        vector<Explosion *> _tabExplo;
        u32 _timePlaced;
        vector3df _pos;
        IrrlichtDevice *_device;
        sf::SoundBuffer _bufferExplo;
        sf::Sound _soundExplo;
};

#endif /* !Explosion */
