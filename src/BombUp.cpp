/*
** EPITECH PROJECT, 2019
** bomb
** File description:
** bomb
*/

#include "Character.hpp"
#include "BombUp.hpp"

BombUp::BombUp(ISceneManager *sceneManager,
               vector3df const &pos)
    : APowerUp("BombUp", "../media/bomb.3DS", sceneManager, pos)
{
    _model->setScale(vector3df(0.15, 0.15, 0.15));
}

BombUp::~BombUp()
{
}

bool BombUp::onCollision(ISceneNodeAnimatorCollisionResponse const &animator)
{
    Character *character = Character::getCharacterFromNode(animator.getTargetNode());
    if (character == NULL)
        return (true);
    character->addBomb();
    _end = true;
    return (true);
}