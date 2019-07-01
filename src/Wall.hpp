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

using namespace irr;
using namespace core;
using namespace video;
using namespace io;
using namespace gui;
using namespace scene;

#ifndef WALL_HPP_
#define WALL_HPP_

class Wall {
    public:
        Wall(IrrlichtDevice *device, vector3df const &pos, const path &texture, bool isBreakable);
        ~Wall();
        void addCollision(IAnimatedMeshSceneNode *model);
        IMeshSceneNode* getNode();
        vector3df const &getPos();
        void setPos(vector3df);
        bool getIsBreakable();

    private:
        IrrlichtDevice *_device;
        ISceneManager *_smgr;
        IMeshSceneNode *_wall;
        ITriangleSelector* _selector;
        vector3df _pos;
        ISceneNodeAnimator* _anim;
        bool _isBreakable;
};

#endif /* !WALL_HPP_ */
