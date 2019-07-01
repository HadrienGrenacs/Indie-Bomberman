/*
** EPITECH PROJECT, 2019
** range
** File description:
** range
*/

#ifndef RANGEUP_HPP_
#define RANGEUP_HPP_

#include <irrlicht.h>
#include "APowerUp.hpp"
#include "Character.hpp"

class RangeUp : public APowerUp
{
public:
    RangeUp(ISceneManager *sceneManager, vector3df const &pos);
    ~RangeUp();
    virtual bool onCollision(const ISceneNodeAnimatorCollisionResponse &animator);
};

#endif /* !RANGEUP_HPP_ */
