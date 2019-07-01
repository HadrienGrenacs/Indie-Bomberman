/*
** EPITECH PROJECT, 2019
** map
** File description:
** map
*/

#include <iostream>
#include <fstream>
#include "Map.hpp"

Map::Map(IrrlichtDevice *device) : _device(device)
{
	_smgr = device->getSceneManager();
	_driver = device->getVideoDriver();
	_smgr->addCameraSceneNode(0, vector3df(59.5, 90, 57))->bindTargetAndRotation(true);
	_smgr->getActiveCamera()->setRotation(vector3df(89, 0, 0));
	openMap("../media/map.txt");
	generateMap();
	generateGround();
}

Map::~Map()
{
}

IVideoDriver *Map::getDriver()
{
	return (_driver);
}

ISceneManager *Map::getSmgr()
{
	return (_smgr);
}

void Map::openMap(const char *filename)
{
	char c;
	std::ifstream file(filename);
	std::string str;

	if (!file)
		std::cerr << filename << ": No such file or directory" << std::endl;
	while (file.get(c))
	{
		if (c == '\n')
		{
			_mapText.push_back(str);
			str = "";
		}
		else
			str += c;
	}
}

void Map::generateMap()
{
	int x = 0;
	int z = 0;

	while (z < 18)
	{
		while (x < 18)
		{
			if (_mapText[z][x] == '#') {
				if (rand() % 5 == 0 && x > 1 && x < 17 && z > 1 && z < 17)
					_mapWall.push_back(new Wall(_device, vector3df(x * 7, 0, z * 7), "../media/box.png", true));
				else
					_mapWall.push_back(new Wall(_device, vector3df(x * 7, 0, z * 7), "../media/wall.png", false));
			}
			if (_mapText[z][x] == '/')
				_mapWall.push_back(new Wall(_device, vector3df(x * 7, 0, z * 7), "../media/box.png", true));
			x++;
		}
		x = 0;
		z++;
	}
}

void Map::generateGround()
{
	IMeshSceneNode *ground = _smgr->addCubeSceneNode(126, 0, -1, vector3df(59.5, -7, 59.5), vector3df(0, 0, 0), vector3df(1, 0.02, 1));
	ground->setMaterialFlag(EMF_LIGHTING, false);
	ground->setMaterialTexture(0, _driver->getTexture("../media/grass.png"));
	_selector = _smgr->createOctreeTriangleSelector(ground->getMesh(), ground, 128);
	ground->setTriangleSelector(_selector);
}

void Map::addCollision(IAnimatedMeshSceneNode *model)
{

	ISceneNodeAnimator *anim = _smgr->createCollisionResponseAnimator(_selector, model,
														  vector3df(3, 3, 3),
														  vector3df(0.f, 0.f, 0.f),
														  vector3df(0.f, 0.f, 0.f));
	model->addAnimator(anim);
	anim->drop();
	std::for_each(_mapWall.begin(), _mapWall.end(),
				  [model](auto &wall) {
					  wall->addCollision(model);
				  });
}

bool Map::isWall(vector3df const &pos)
{
	int i = 0;

	for (i = 0; i < _mapWall.size(); i++) {
		if (_mapWall[i]->getPos() == pos)
			return (true);
	}
	return (false);
}

bool Map::removeWall(vector3df const &pos)
{
	int i = 0;

	for (i = 0; i < _mapWall.size(); i++) {
		if (_mapWall[i]->getPos() == pos && _mapWall[i]->getIsBreakable()) {
			_mapWall[i]->setPos(vector3df(pos.X, -14, pos.Z));
			return (true);
		}
	}
	return (false);
}
