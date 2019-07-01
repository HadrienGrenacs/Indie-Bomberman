/*
** EPITECH PROJECT, 2019
** map
** File description:
** map
*/

#include <iostream>
#include <fstream>
#include "Wall.hpp"

Wall::Wall(IrrlichtDevice *device, vector3df const &pos, const path &texture, bool isBreakable) : _device(device), _pos(pos), _isBreakable(isBreakable)
{
	IVideoDriver *driver = device->getVideoDriver();

	_smgr = device->getSceneManager();
	_wall = _smgr->addCubeSceneNode(7, 0, -1, pos);
	_wall->setMaterialFlag(EMF_LIGHTING, false);
	_wall->setMaterialTexture(0, driver->getTexture(texture));
	_selector = _smgr->createOctreeTriangleSelector(_wall->getMesh(), _wall, 128);
	_wall->setTriangleSelector(_selector);
}

Wall::~Wall()
{
}

IMeshSceneNode* Wall::getNode()
{
	return (_wall);
}

vector3df const &Wall::getPos()
{
	return (_pos);
}

void Wall::setPos(vector3df pos)
{
	_pos = pos;
	_wall->setPosition(vector3df(pos.X, -14, pos.Z));
}

bool Wall::getIsBreakable()
{
	return (_isBreakable);
}

void Wall::addCollision(IAnimatedMeshSceneNode *model)
{
	ISceneNodeAnimator *anim = _smgr->createCollisionResponseAnimator(_selector, model,
														  vector3df(3, 3, 3),
														  vector3df(0.f, 0.f, 0.f),
														  vector3df(0.f, 0.f, 0.f));
	model->addAnimator(anim);
	anim->drop();
}