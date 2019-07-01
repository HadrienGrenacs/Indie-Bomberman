/*
** EPITECH PROJECT, 2019
** Explosion
** File description:
** Explosion
*/

#include "Explosion.hpp"

CrossExplo::CrossExplo(IrrlichtDevice *device, Map &map,vector3df const &pos, int bombPower, u32 initialTime)
{
    _device = device;    
    _timePlaced = initialTime;
    _pos = pos;
    _bufferExplo.loadFromFile("../media/explosion.wav");
    _soundExplo.setBuffer(_bufferExplo);
    _soundExplo.play();
    _tabExplo.push_back(new Explosion(_device, _pos));
    exploDirection(map, bombPower,vector3df(7, 0, 0));
    exploDirection(map, bombPower,vector3df(-7, 0, 0));
    exploDirection(map, bombPower,vector3df(0, 0, 7));
    exploDirection(map, bombPower,vector3df(0, 0, -7));
}

CrossExplo::~CrossExplo()
{
}

vector3df CrossExplo::getPos()
{
    return(_pos);
}

void CrossExplo::exploDirection(Map &map, int bombPower, vector3df const &dir)
{
    for (int i = 1; i <= bombPower; i++) {
        if (map.isWall(vector3df(_pos.X, 0, _pos.Z) + dir * i))
            return;
        _tabExplo.push_back(new Explosion(_device, vector3df(_pos.X, 0, _pos.Z) + dir * i));
    }
}

void CrossExplo::removeExplosion()
{
    for (int i = 0; i < _tabExplo.size(); i++)
        _tabExplo[i]->removeExplosion();
};


u32 CrossExplo::getTimePlaced()
{
    return (_timePlaced);
}

bool CrossExplo::checkPos(vector3df pos)
{
    for (int i = 0; i < _tabExplo.size(); i++) {
        if (_tabExplo[i]->getPos() == pos)
            return (true);
    }
    return (false);
}

Explosion::Explosion(IrrlichtDevice *device, vector3df const &pos)
{
    _smgr = device->getSceneManager();
    IVideoDriver *driver = device->getVideoDriver();
    IParticleEmitter *emitter;

    _particleSystem = _smgr->addParticleSystemSceneNode(false);
    emitter = _particleSystem->createBoxEmitter(aabbox3d<f32>(pos.X, 0, pos.Z, pos.X, 0, pos.Z),
                                              vector3df(0.0f, 0.0f, 0.0f),
                                              10, 10,
                                              SColor(0, 255, 255, 255),
                                              SColor(0, 255, 255, 255),
                                              250, 250, 0,
                                              dimension2df(8.0f, 8.0f),
                                              dimension2df(14.0f, 14.0f));
    _particleSystem->setEmitter(emitter);
    emitter->drop();
    _particleSystem->setMaterialFlag(EMF_LIGHTING, false);
    _particleSystem->setMaterialFlag(EMF_ZWRITE_ENABLE, false);
    _particleSystem->setMaterialTexture(0, driver->getTexture("../media/fire.bmp"));
    _particleSystem->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
    _pos = vector3df(pos.X, 0, pos.Z);
}

Explosion::~Explosion()
{
}

vector3df Explosion::getPos()
{
    return (_pos);
}

void Explosion::removeExplosion()
{
    _smgr->addToDeletionQueue(_particleSystem);
}