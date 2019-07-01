/*
** EPITECH PROJECT, 2019
** speed
** File description:
** speed
*/

#include "Character.hpp"
#include "SpeedUp.hpp"

SpeedUp::SpeedUp(ISceneManager *sceneManager, vector3df const &pos)
    : APowerUp("SpeedUp", "../media/speed.obj", sceneManager, pos)
{
    _model->setRotation(vector3df(-90, 180, 0));
}

SpeedUp::~SpeedUp()
{
}

bool SpeedUp::onCollision(ISceneNodeAnimatorCollisionResponse const &animator)
{
    Character *character = Character::getCharacterFromNode(animator.getTargetNode());
    if (character == NULL)
        return (true);
    character->addSpeed();
    _end = true;
    return (true);
}
