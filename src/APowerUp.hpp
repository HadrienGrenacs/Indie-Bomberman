/*
** EPITECH PROJECT, 2019
** powerUp
** File description:
** powerUp
*/

#ifndef POWERUP_HPP_
#define POWERUP_HPP_

#include <irrlicht.h>
#include <string>
#include <memory>
#include <vector>
#include <utility>

using namespace irr;
using namespace core;
using namespace video;
using namespace io;
using namespace gui;
using namespace scene;

class APowerUp : public ICollisionCallback
{
public:
    static void clearAllPowerUp(void);
    static APowerUp *createPowerUp(ISceneManager *sceneManager, vector3df const &pos);
    static void checkPowerUp(void);
    APowerUp(std::string const &name, std::string const &model,
             ISceneManager *sceneManager, vector3df const &pos);
    ~APowerUp();
    IMeshSceneNode *getModel(void);
    virtual bool onCollision(const ISceneNodeAnimatorCollisionResponse &animator) = 0;
    void assignCollision(IAnimatedMeshSceneNode *model);

protected:
    bool _end;
    IMeshSceneNode *_model;

private:
    static std::vector<std::unique_ptr<APowerUp>> _allPowerUps;
    std::string _name;
    ISceneManager *_sceneManager;
    ITriangleSelector *_selector;
    std::vector<std::pair<IAnimatedMeshSceneNode *, ISceneNodeAnimator *>> _tabCollision;
};

#endif /* !POWERUP_HPP_ */
