/*
** EPITECH PROJECT, 2019
** bomb
** File description:
** bomb
*/

#ifndef BOMBUP_HPP_
#define BOMBUP_HPP_

#include <irrlicht.h>
#include "APowerUp.hpp"
#include "Character.hpp"

class BombUp : public APowerUp
{
public:
    BombUp(ISceneManager *sceneManager, vector3df const &pos);
    ~BombUp();
    virtual bool onCollision(const ISceneNodeAnimatorCollisionResponse &animator);
};

#endif /* BOMBUP_HPP_ */
