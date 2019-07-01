/*
** EPITECH PROJECT, 2019
** Visual Studio Live Share (Workspace)
** File description:
** Bomb
*/

#include "Bomb.hpp"
#include "Character.hpp"

Bomb::Bomb(IrrlichtDevice *device, IAnimatedMeshSceneNode *player, u32 timePlaced) : _device(device)
{
    IVideoDriver *driver = device->getVideoDriver();
    IParticleEmitter *emitter;

    _smgr = device->getSceneManager();
    _bomb = _smgr->addAnimatedMeshSceneNode(_smgr->getMesh("../media/bomb.3DS"), 0, -1, player->getPosition(), vector3df(0, 0, 0), vector3df(0.2, 0.2, 0.2));
    setCoord(player);
    _bomb->setPosition(_pos);
    _bomb->setMaterialFlag(EMF_LIGHTING, false);
    _selector = _smgr->createOctreeTriangleSelector(_bomb->getMesh(), _bomb, 128);
    _bomb->setTriangleSelector(_selector);
    _isCollided = false;
    _timePlaced = timePlaced;
    _particleSystem = _smgr->addParticleSystemSceneNode(false);
    emitter = _particleSystem->createBoxEmitter(aabbox3d<f32>(_pos.X, 0, _pos.Z, _pos.X, 0, _pos.Z),
                                                vector3df(0.0f, 0.25, 0.0f),
                                                10, 12,
                                                SColor(0, 255, 255, 255),
                                                SColor(0, 255, 255, 255),
                                                4, 4, 0,
                                                dimension2df(8.0f, 8.0f),
                                                dimension2df(14.0f, 14.0f));
    _particleSystem->setEmitter(emitter);
    emitter->drop();
    _particleSystem->setMaterialFlag(EMF_LIGHTING, false);
    _particleSystem->setMaterialFlag(EMF_ZWRITE_ENABLE, false);
    _particleSystem->setMaterialTexture(0, driver->getTexture("../media/fire.bmp"));
    _particleSystem->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
    _bufferPlace.loadFromFile("../media/placebomb.wav");
    _soundPlace.setBuffer(_bufferPlace);
    _soundPlace.play();
}

Bomb::~Bomb()
{
    _selector->drop();
    _smgr->addToDeletionQueue(_particleSystem);
}

vector3df Bomb::getPos()
{
    return (_pos);
}

void Bomb::setCoord(IAnimatedMeshSceneNode *player)
{
    _pos.X = _pos.X + ((static_cast<int>(player->getPosition().X) + 4) / 7) * 7;
    _pos.Z = _pos.Z + ((static_cast<int>(player->getPosition().Z) + 4) / 7) * 7;
}

void Bomb::setCollided(bool value)
{
    _isCollided = value;
}

bool Bomb::getCollided()
{
    return (_isCollided);
}

u32 Bomb::getTimePlaced()
{
    return (_timePlaced);
}

void Bomb::explode(Map &map, int bombPower, std::vector<Character *> tabPlayers)
{
    _bomb->setPosition(vector3df(_pos.X, -14, _pos.Z));
    blowDirection(map, bombPower, vector3df(7, 0, 0), tabPlayers);
    blowDirection(map, bombPower, vector3df(-7, 0, 0), tabPlayers);
    blowDirection(map, bombPower, vector3df(0, 0, 7), tabPlayers);
    blowDirection(map, bombPower, vector3df(0, 0, -7), tabPlayers);
    this->~Bomb();
}

void Bomb::blowDirection(Map &map, unsigned int const bombPower, vector3df const &dir, std::vector<Character *> tabPlayers)
{
    APowerUp *powerUp;

    for (int i = 1; i <= bombPower; i++) {
        if (map.isWall(vector3df(_pos.X, 0, _pos.Z) + dir * i)) {
            if (map.removeWall(vector3df(_pos.X, 0, _pos.Z) + dir * i)) {
                if (powerUp = APowerUp::createPowerUp(_smgr, vector3df(_pos.X, 0, _pos.Z) + dir * i)) {
                    for (int j = 0; j < tabPlayers.size(); j++)
                        powerUp->assignCollision(tabPlayers[j]->getModel());
                }
            }
            return;
        }
    }
}

void Bomb::addCollision(IAnimatedMeshSceneNode *model)
{
    ISceneNodeAnimator *anim = _smgr->createCollisionResponseAnimator(_selector, model,
                                                                                  vector3df(2, 2, 2),
                                                                                  vector3df(0.0f, 0.0f, 0.0f),
                                                                                  vector3df(0.0f, 0.0f, 0.0f));
    model->addAnimator(anim);
    anim->drop();
}