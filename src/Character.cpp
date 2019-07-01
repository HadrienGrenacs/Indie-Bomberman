/*
** EPITECH PROJECT, 2019
** Character
** File description:
** Character
*/

#include "Character.hpp"

std::vector<Character*> Character::_tabPlayers;

Character::Character(IrrlichtDevice *device, EventManager const &receiver, Map &map, vector3df const &pos, const path &texture, EKEY_CODE keyUp, EKEY_CODE keyDown, EKEY_CODE keyLeft, EKEY_CODE keyRight, EKEY_CODE keyBomb)
    : _device(device), _receiver(receiver), _map(map),_pos(pos), _keyUp(keyUp), _keyDown(keyDown), _keyLeft(keyLeft), _keyRight(keyRight), _keyBomb(keyBomb)
{
    _model = _device->getSceneManager()->addAnimatedMeshSceneNode(_device->getSceneManager()->getMesh(texture + ".md2"), 0, -1, pos, vector3df(0, 0, 0), vector3df(0.2, 0.2, 0.2));
    _model->setMaterialFlag(EMF_LIGHTING, false);
    _model->setMD2Animation(EMAT_STAND);
    _model->setMaterialTexture(0, _device->getVideoDriver()->getTexture(texture + ".bmp"));
    _selector = _device->getSceneManager()->createOctreeTriangleSelector(_model->getMesh(), _model, 128);
    _model->setTriangleSelector(_selector);
    _speed = 20.f;
    _now = _device->getTimer()->getTime();
    _then = _now;
    _maxBomb = 1;
    _bombPower = 2;
    _isDead = false;
}

Character::~Character()
{
}

Character *Character::getCharacterFromNode(ISceneNode const *node)
{
    for (int i = 0; i < _tabPlayers.size(); i++) {
        if (_tabPlayers[i]->getModel() == node)
            return (_tabPlayers[i]);
    }
}

void Character::addBomb()
{
    _maxBomb += 1;
}

void Character::addSpeed()
{
    if (_speed < 35)
        _speed += 3;
}

void Character::addRange()
{
    _bombPower += 1;
}

void Character::setPlayers(std::vector<Character *> tabPlayers)
{
    _tabPlayers = tabPlayers;
}

void Character::update()
{
    _now = _device->getTimer()->getTime();
    _frameDeltaTime = (f32)(_now - _then) / 1000.f;
    _then = _now;
    if (!_isDead) {
        if (!move() && _direction != NONE) {
            _model->setMD2Animation(scene::EMAT_STAND);
            _direction = NONE;
        }
        placeBomb();
        checkDeath();
    }
    checkBomb();
    checkExplo();
}

bool Character::move()
{
    vector3df nodePosition = _model->getPosition();

    if (_receiver.IsKeyDown(_keyUp))
    {
        nodePosition.Z += _speed * _frameDeltaTime;
        _model->setPosition(nodePosition);
        if (_direction != UP)
        {
            _model->setRotation(vector3df(0, -90, 0));
            _model->setMD2Animation(scene::EMAT_RUN);
            _direction = UP;
        }
        return (true);
    }
    else if (_receiver.IsKeyDown(_keyDown))
    {
        nodePosition.Z -= _speed * _frameDeltaTime;
        _model->setPosition(nodePosition);
        if (_direction != DOWN)
        {
            _model->setRotation(vector3df(0, 90, 0));
            _model->setMD2Animation(scene::EMAT_RUN);
            _direction = DOWN;
        }
        return (true);
    }
    else if (_receiver.IsKeyDown(_keyLeft))
    {
        nodePosition.X -= _speed * _frameDeltaTime;
        _model->setPosition(nodePosition);
        if (_direction != LEFT)
        {
            _model->setRotation(vector3df(0, -180, 0));
            _model->setMD2Animation(scene::EMAT_RUN);
            _direction = LEFT;
        }
        return (true);
    }
    else if (_receiver.IsKeyDown(_keyRight))
    {
        nodePosition.X += _speed * _frameDeltaTime;
        _model->setPosition(nodePosition);
        if (_direction != RIGHT)
        {
            _model->setRotation(vector3df(0, 0, 0));
            _model->setMD2Animation(scene::EMAT_RUN);
            _direction = RIGHT;
        }
        return (true);
    }
    return (false);
}

void Character::addCollision(IAnimatedMeshSceneNode *model)
{
    ISceneNodeAnimator *anim = _device->getSceneManager()->createCollisionResponseAnimator(_selector, model,
                                                                       vector3df(5, 10, 5),
                                                                       vector3df(0, -10, 0),
                                                                       vector3df(0, 0, 0));
    model->addAnimator(anim);
    _selector->drop();
    anim->drop();
}

IAnimatedMeshSceneNode *Character::getModel()
{
    return (_model);
}

void Character::placeBomb()
{
    vector3df centerPos;
    centerPos.X = (static_cast<int>(_model->getPosition().X + 4) / 7) * 7;
    centerPos.Z = (static_cast<int>(_model->getPosition().Z + 4) / 7) * 7;

    std::for_each(_tabBomb.begin(), _tabBomb.end(), [&](Bomb *bomb) {
        if (!bomb->getCollided() && (bomb->getPos().X != centerPos.X || bomb->getPos().Z != centerPos.Z)) {
            bomb->addCollision(getModel());
            bomb->setCollided(true);
        }
    });

    if (_receiver.IsKeyDown(_keyBomb) && _tabBomb.size() < _maxBomb && !isBombAtPos(centerPos.X, centerPos.Z)) {
        _tabBomb.push_back(new Bomb(_device, _model, _device->getTimer()->getTime()));

        std::for_each(_tabPlayers.begin(), _tabPlayers.end(),
                      [&](Character *player) {
                          if (getModel() != player->getModel())
                              _tabBomb[_tabBomb.size() - 1]->addCollision(player->getModel());
                      });
    }
}

vector3df Character::getCenterPos()
{
    vector3df centerPos;

    centerPos.X = (static_cast<int>(_model->getPosition().X + 4) / 7) * 7;
    centerPos.Z = (static_cast<int>(_model->getPosition().Z + 4) / 7) * 7;
    centerPos.Y = 0;
    return (centerPos);
}

bool Character::isDead()
{
    return (_isDead);
}

void Character::checkDeath()
{    
    for (int i = 0; i < _tabPlayers.size(); i++) {
        for (int j = 0; j < _tabExplo.size(); j++) {
            if (_tabExplo[j]->checkPos(_tabPlayers[i]->getCenterPos()) == true) {
                _tabPlayers[i]->_model->setPosition(vector3df(800, 800, 800));
                _tabPlayers[i]->_isDead = true;
            }
        }
    }
}

void Character::checkBomb()
{
    for (int i = 0; i < _tabBomb.size(); i++) {
        if (_device->getTimer()->getTime() - _tabBomb[i]->getTimePlaced() >= 2500) {
            _tabBomb[i]->explode(_map, _bombPower, _tabPlayers);
            _tabExplo.push_back(new CrossExplo(_device, _map, _tabBomb[i]->getPos(), _bombPower, _device->getTimer()->getTime()));
            _tabBomb.erase(_tabBomb.begin() + i);
        }
    }
}

void Character::checkExplo()
{
    for (int i = 0; i < _tabExplo.size(); i++) {
        if (_device->getTimer()->getTime() - _tabExplo[i]->getTimePlaced() >= 800) {
            _tabExplo[i]->removeExplosion();
            _tabExplo.erase(_tabExplo.begin() + i);            
        }
    };
}

bool Character::isBombAtPos(f32 posX, f32 posZ)
{
    for (int i = 0; i < _tabBomb.size(); i++) {
        if (_tabBomb[i]->getPos().X == posX && _tabBomb[i]->getPos().Z == posZ)
            return (true);
    }
    return (false);
}

