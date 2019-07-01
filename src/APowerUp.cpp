/*
** EPITECH PROJECT, 2019
** powerUp
** File description:
** powerUp
*/

#include <algorithm>
#include <cstdlib>
#include <stdexcept>
#include "APowerUp.hpp"
#include "BombUp.hpp"
#include "SpeedUp.hpp"
#include "RangeUp.hpp"

std::vector<std::unique_ptr<APowerUp>> APowerUp::_allPowerUps;

void APowerUp::clearAllPowerUp(void)
{
    _allPowerUps.clear();
}

APowerUp *APowerUp::createPowerUp(ISceneManager *sceneManager, vector3df const &pos)
{
    if (rand() % 3 != 0)
        return (NULL);

    int bonus = rand() % 3;

    if (bonus == 0)
        _allPowerUps.push_back(std::unique_ptr<APowerUp>(new SpeedUp(sceneManager, pos)));
    else if (bonus == 1)
        _allPowerUps.push_back(std::unique_ptr<APowerUp>(new BombUp(sceneManager, pos)));
    else
        _allPowerUps.push_back(std::unique_ptr<APowerUp>(new RangeUp(sceneManager, pos)));
    return (_allPowerUps[_allPowerUps.size() - 1].get());
}

void APowerUp::checkPowerUp(void)
{
    unsigned int i = 0;

    while (i < _allPowerUps.size()) {
        if (_allPowerUps[i]->_end == true) {
            _allPowerUps.erase(_allPowerUps.begin() + i);
            i = 0;
        }
        else
            ++i;
    }
}

APowerUp::APowerUp(std::string const &name, std::string const &model,
                   ISceneManager *sceneManager,
                   vector3df const &pos)
    : _name(name), _sceneManager(sceneManager), _end(false)
{
    if (!(_model = _sceneManager->addMeshSceneNode(_sceneManager->getMesh(model.c_str()))))
        throw std::runtime_error("Failed to load the powerUp model");
    _model->setScale(vector3df(0.2, 0.2, 0.2));
    _model->setPosition(pos);
    _model->setMaterialFlag(EMF_LIGHTING, false);
    _selector = _sceneManager->createOctreeTriangleSelector(_model->getMesh(),
                                                            _model, 128);
    _model->setTriangleSelector(_selector);
    _model->setName("PowerUp");
}

APowerUp::~APowerUp()
{
    std::for_each(_tabCollision.begin(), _tabCollision.end(),
                  [](auto &col) {
                      col.first->removeAnimator(col.second);
                  });
    _selector->drop();
    _sceneManager->addToDeletionQueue(_model);
}

IMeshSceneNode *APowerUp::getModel(void)
{
    return (_model);
}

void APowerUp::assignCollision(IAnimatedMeshSceneNode *model)
{
    ISceneNodeAnimatorCollisionResponse *anim;

    anim = _sceneManager->createCollisionResponseAnimator(_selector, model,
                                                          vector3df(3, 3, 3),
                                                          vector3df(0.0f, 0.0f, 0.0f),
                                                          vector3df(0.0f, 0.0f, 0.0f));
    model->addAnimator(anim);
    anim->setCollisionCallback(this);
    anim->setTargetNode(model);
    anim->drop();
    _tabCollision.push_back({model, anim});
}
