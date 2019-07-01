/*
** EPITECH PROJECT, 2019
** map
** File description:
** map
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <irrlicht.h>
#include <algorithm>
#include <memory>
#include "Wall.hpp"

using namespace irr;
using namespace core;
using namespace video;
using namespace io;
using namespace gui;
using namespace scene;

#ifndef MAP_HPP_
#define MAP_HPP_

class Map {
    public:
        Map(IrrlichtDevice *device);
        ~Map();
        void openMap(const char *filename);
        void generateGround();
        void generateMap();
        void addCollision(IAnimatedMeshSceneNode *model);
        IVideoDriver* getDriver();
        ISceneManager* getSmgr();
        bool isWall(vector3df const &pos);
        bool removeWall(vector3df const &pos);

    private:
        IrrlichtDevice *_device;
        ISceneManager *_smgr;
        IVideoDriver *_driver;
        std::vector<std::string> _mapText;
        std::vector<Wall*> _mapWall;
        ITriangleSelector* _selector;
};

#endif /* !map */
