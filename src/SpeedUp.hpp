/*
** EPITECH PROJECT, 2019
** speed
** File description:
** speed
*/

#ifndef SPEEDUP_HPP_
#define SPEEDUP_HPP_

#include <irrlicht.h>
#include "APowerUp.hpp"
#include "Character.hpp"

class SpeedUp : public APowerUp
{
public:
    SpeedUp(ISceneManager *sceneManager, vector3df const &pos);
    ~SpeedUp();
    virtual bool onCollision(const ISceneNodeAnimatorCollisionResponse &animator);
};

#endif /* !SPEEDUP_HPP_ */
