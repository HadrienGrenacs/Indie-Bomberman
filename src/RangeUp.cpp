/*
** EPITECH PROJECT, 2019
** range
** File description:
** range
*/

#include "Character.hpp"
#include "RangeUp.hpp"

RangeUp::RangeUp(ISceneManager *sceneManager,
               vector3df const &pos)
    : APowerUp("RangeUp", "../media/explo.obj", sceneManager, pos)
{
    _model->setScale(vector3df(2, 2, 2));
}

RangeUp::~RangeUp()
{
}

bool RangeUp::onCollision(ISceneNodeAnimatorCollisionResponse const &animator)
{
    Character *character = Character::getCharacterFromNode(animator.getTargetNode());
    if (character == NULL)
        return (true);
    character->addRange();
    _end = true;
    return (true);
}