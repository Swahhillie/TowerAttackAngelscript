#include "ObjectBank.hpp"
#include "Object.hpp"
#include "Texture.hpp"
#include "Body.hpp"
#include "Transform.hpp"
#include "RobotComponent.hpp"
#include "Lasergrid.hpp"
#include "Powernode.hpp"
#include "Turret.hpp"
#include "CellManager.hpp"
#include "Sound.hpp"
#include "Particle.hpp"
#include "ParticleEffect.hpp"
#include "Config.hpp"

ObjectBank::ObjectBank(): initialized(false),mainObject(0), floorHolder(0), debugCubeHolder(0), robotHolder(0), wallHolder(0), structureHolder(0), particleHolder(0)
{
	//ctor

}

ObjectBank::~ObjectBank()
{
	//dtor

}
void ObjectBank::init(Object * mainObject){
    this->mainObject = mainObject;
	floorHolder = new Object();
	floorHolder->name = "floorHolder";
	floorHolder->getTransform()->setParent(mainObject->getTransform());
	debugCubeHolder = new Object();
	debugCubeHolder->name = "debugCubeHolder";
	debugCubeHolder->getTransform()->setParent(mainObject->getTransform());
	robotHolder = new Object();
	robotHolder->name = "robotHolder";
	robotHolder->getTransform()->setParent(mainObject->getTransform());
	wallHolder = new Object();
	wallHolder->name = "wallHolder";
	wallHolder->getTransform()->setParent(mainObject->getTransform());
    structureHolder = new Object();
    structureHolder->name = "structureHolder";
    structureHolder->getTransform()->setParent(mainObject->getTransform());
    particleHolder = new Object();
    particleHolder->name = "particleHolder";
    particleHolder->getTransform()->setParent(mainObject->getTransform());
    initialized = true;
}
Object * ObjectBank::getObject(const std::string & objectName, std::string & objFileName, std::string & textureName){
	std::string assetDir = "assets\\";
	Object * theNewObject = new Object();
	theNewObject->addRenderMaterial();
	theNewObject->name = objectName + "(Clone)";
	Body * theBody = Body::load((assetDir + objFileName).c_str());
	theNewObject->getRenderMaterial()->addTexture(Texture::load((assetDir + textureName).c_str()));
	theNewObject->setBody(theBody);
	theNewObject->getTransform()->setParent(floorHolder->getTransform());

	assert(theNewObject != NULL);
	return theNewObject;
}

Object * ObjectBank::getFloor(){
	Object * theFloor = new Object();
	theFloor->addRenderMaterial();

	Body * theBody = Body::load("assets\\plane.obj");
	Texture * theTexture = Texture::load("assets\\floor_tile.jpg");
	theFloor->getRenderMaterial()->addTexture(theTexture);
	theFloor->setBody(theBody);


	Transform * tr = theFloor->getTransform();
	tr->setParent(floorHolder->getTransform()->getParent());
	return theFloor;

}
Object * ObjectBank::getCube(){
    Object * theCube = new Object();
    theCube->addRenderMaterial();
	Body * theBody = Body::load("assets\\dice.obj");
	Texture * theTexture = Texture::load("assets\\floor_tile.jpg");
	theCube->getRenderMaterial()->addTexture(theTexture);
	theCube->setBody(theBody);

	Transform * tr = theCube->getTransform();
	tr->setParent(debugCubeHolder->getTransform()->getParent());
	return theCube;

}
Object * ObjectBank::getSphere(){
    Object * sphere = new Object();
    sphere->addRenderMaterial();
    sphere->getRenderMaterial()->setShader("TimeDistort");
    sphere->addCollider();
    sphere->getCollider()->colliderOffset = glm::vec3(0,1,0);
	Body * theBody = Body::load("assets\\sphere.obj");
	Texture * theTexture = Texture::load("assets\\floor_tile.jpg");
	sphere->getRenderMaterial()->addTexture(theTexture);
	sphere->setBody(theBody);

	Transform * tr = sphere->getTransform();
	tr->setParent(debugCubeHolder->getTransform()->getParent());
	return sphere;
}
Object * ObjectBank::getRobot(){

	Object * robot = getRobot_wireCutter();
	robot->getRenderMaterial()->setShader("Specular");

	return robot;

}
Object * ObjectBank::getBehaviourRobot(CellManager * manager){
	Object * robot = new Object();
	Transform * tr = robot->getTransform();
	robot->layer = Object::SCENERYLAYER;
	robot->name = "behave robot";
	robot->addRenderMaterial();
	robot->addCollider();
	Body * theBody = Body::load("assets\\robotSmaller.obj");
	Texture * theTexture = Texture::load("assets\\white.png");
	robot->addRobotComponent(RobotComponent::WireCutter);

	robot->getRenderMaterial()->addTexture(theTexture);
	robot->setBody(theBody);


	tr->setParent(debugCubeHolder->getTransform()->getParent());
	robot->getRenderMaterial()->setShader("TexCoordDistort");
	return robot;
}
Object * ObjectBank::getSkybox(){
	Object*skybox = new Object();
	skybox->layer = Object::SCENERYLAYER;
	skybox->name = "skybox";
	skybox->addRenderMaterial();
	skybox->getRenderMaterial()->setShader("Skybox");
	skybox->getTransform()->setPosition(glm::vec3(10,0,10));
    //Body * body = Body::load("assets\\models\\environment\\Skybox.obj");
    Body * body = Body::load("assets\\InvertedCube.obj");
    std::string dir ("assets\\models\\skybox\\Sunny1");
    Config::instance().getSetting("skyboxAddress", dir);
    std::cout << "skybox = " << dir << std::endl;
    std::string extension (".png");
    std::vector<std::string> skyboxTextureNames;
    skyboxTextureNames.push_back(dir + "_left" + extension);
    skyboxTextureNames.push_back(dir + "_right"+ extension);
    skyboxTextureNames.push_back(dir + "_up"+ extension);
    skyboxTextureNames.push_back(dir + "_down"+ extension);
    skyboxTextureNames.push_back(dir + "_front"+ extension);
    skyboxTextureNames.push_back(dir + "_back"+ extension);

    Texture * skyboxCubemap = Texture::loadCubemapTexture(skyboxTextureNames);
	assert(skyboxCubemap != NULL);
    skybox->getRenderMaterial()->addTexture(skyboxCubemap);
    skybox->getTransform()->setParent(floorHolder->getTransform());
    //flipping the skybox upside down because it is boring at the bottem :)
    //skybox->getTransform()->rotate(180, glm::vec3(1,0,0));
    skybox->setBody(body);
    return skybox;
}
Object * ObjectBank::getTestObject(){
	Object * theCube = new Object();
	theCube->layer = Object::SCENERYLAYER;
	theCube->name = "theCube";
	theCube->addRenderMaterial();
	Body * theBody = Body::load("assets\\testCube.obj");
	Texture * theTexture = Texture::load("assets\\floor_tile.jpg");
	theCube->getRenderMaterial()->addTexture(theTexture);
	theCube->setBody(theBody);

	Transform * tr = theCube->getTransform();
	tr->setParent(debugCubeHolder->getTransform()->getParent());
	return theCube;
}

Object * ObjectBank::getWall_01(){
    Object * wall1 = new Object();
    wall1->layer = Object::SCENERYLAYER;
    wall1->name = "wall1";
    wall1->addRenderMaterial();
    Body * body = Body::load("assets\\models\\level\\Wall_01.obj");
    Texture * texture = Texture::load("assets\\models\\level\\Wall_01.jpg");
    wall1->getRenderMaterial()->addTexture(texture);
    wall1->setBody(body);
    wall1->getTransform()->setParent(wallHolder->getTransform());
    wall1->addCollider();
    return wall1;
}
Object * ObjectBank::getWall_02(){
    Object * wall2 = new Object();
    wall2->layer = Object::SCENERYLAYER;
    wall2->name = "wall2";
    wall2->addRenderMaterial();
    Body * body = Body::load("assets\\models\\level\\Wall_02.obj");
    Texture * texture = Texture::load("assets\\models\\level\\Wall_02.jpg");
    wall2->getRenderMaterial()->addTexture(texture);
    wall2->setBody(body);
    wall2->addCollider();
    wall2->getTransform()->setParent(wallHolder->getTransform());
    return wall2;
}
Object * ObjectBank::getWallCorner(){
    Object * wallCorner = new Object();
    wallCorner->layer = Object::SCENERYLAYER;
    wallCorner->name = "wall2";
    wallCorner->addRenderMaterial();
    Body * body = Body::load("assets\\models\\level\\Wall_Corner.obj");
    Texture * texture = Texture::load("assets\\models\\level\\Wall_Corner.jpg");
    wallCorner->getRenderMaterial()->addTexture(texture);
    wallCorner->setBody(body);
    wallCorner->addCollider();
    wallCorner->getTransform()->setParent(wallHolder->getTransform());
    return wallCorner;
}
Object * ObjectBank::getFloortile_01(){
    Object * floorTile1 = new Object();
    floorTile1->layer = Object::SCENERYLAYER;
    floorTile1->name = "floorTile1";
    floorTile1->addRenderMaterial();
    //floorTile1->getRenderMaterial()->setShader("ProgressBar");
    Body * body = Body::load("assets\\models\\level\\FloorTile_01.obj");
    Texture * texture = Texture::load("assets\\models\\level\\FloorTile_01.jpg");
    floorTile1->getRenderMaterial()->addTexture(texture);
    texture = Texture::load("assets\\models\\level\\FloorTile_02.jpg");
    floorTile1->getRenderMaterial()->addTexture(texture);
    floorTile1->getRenderMaterial()->setShader("ProgressBar");
    floorTile1->setBody(body);
    floorTile1->getTransform()->setParent(floorHolder->getTransform());
    return floorTile1;
}
Object * ObjectBank::getFloortile_02(){
    Object * floorTile2 = new Object();
    floorTile2->layer = Object::SCENERYLAYER;
    floorTile2->name = "floorTile2";
    floorTile2->addRenderMaterial();
    Body * body = Body::load("assets\\models\\level\\FloorTile_02.obj");
    Texture * texture = Texture::load("assets\\models\\level\\FloorTile_02.jpg");
    floorTile2->getRenderMaterial()->addTexture(texture);
    floorTile2->setBody(body);
    floorTile2->getTransform()->setParent(floorHolder->getTransform());
    return floorTile2;
}
Object * ObjectBank::getTurretFloor(){
    Object * theFloor = new Object();
    theFloor->layer = Object::SCENERYLAYER;
	theFloor->addRenderMaterial();

	Body * theBody = Body::load("assets\\models\\level\\Floortile_turret.obj");
	Texture * theTexture = Texture::load("assets\\models\\level\\Floortile_turret.jpg");
	theFloor->getRenderMaterial()->addTexture(theTexture);
	theFloor->setBody(theBody);


	Transform * tr = theFloor->getTransform();
	tr->setParent(floorHolder->getTransform()->getParent());
	return theFloor;

}
Object * ObjectBank::getLasergrid(){
	Object * lasergrid = new Object();
	lasergrid->name = "lasergrid";
    lasergrid->addRenderMaterial();
	lasergrid->getRenderMaterial()->setShader("LaserShader");
    lasergrid->addComponent(new Lasergrid());// ======= lasergrid added;
    lasergrid->addCollider();

    Body * body = Body::load("assets\\models\\level\\Lasergrid.obj");
    Texture * texture = Texture::load("assets\\models\\level\\Lasergrid.jpg");
    lasergrid->getRenderMaterial()->addTexture(texture);
    lasergrid->setBody(body);
    lasergrid->getTransform()->setParent(robotHolder->getTransform());
    return lasergrid;
}
Object * ObjectBank::getRobot_wireCutter(){
    Object * robotWireCutter = new Object();
    robotWireCutter->layer = Object::ROBOTLAYER;
    robotWireCutter->addSound(new Sound());
    robotWireCutter->name = "robotWireCutter";
    robotWireCutter->addRenderMaterial();
    Body * body = Body::load("assets\\models\\robot\\Robot_wirecutter.obj");
    Texture * texture = Texture::load("assets\\models\\robot\\Robot_wirecutter.jpg");

    robotWireCutter->addCollider();
    robotWireCutter->addRobotComponent(RobotComponent::WireCutter);
    Transform * tr = robotWireCutter->getTransform();




    robotWireCutter->getRenderMaterial()->addTexture(texture);
    robotWireCutter->setBody(body);
    tr->setParent(robotHolder->getTransform());
    return robotWireCutter;
}
Object * ObjectBank::getRobot_laserTurret(){
    Object * robotLaserTurret = new Object();
    robotLaserTurret->layer = Object::ROBOTLAYER;
    robotLaserTurret->addSound(new Sound());
    robotLaserTurret->name = "robotLaserTurret";
    robotLaserTurret->addRenderMaterial();

    Body * body = Body::load("assets\\models\\robot\\Robot_laserturret.obj");
    Texture * texture = Texture::load("assets\\models\\robot\\Robot_laserturret.jpg");

	robotLaserTurret->addCollider();
	robotLaserTurret->addRobotComponent(RobotComponent::LaserTurret);

    Transform * tr = robotLaserTurret->getTransform();


    robotLaserTurret->getRenderMaterial()->addTexture(texture);
    robotLaserTurret->setBody(body);
    tr->setParent(robotHolder->getTransform());
    return robotLaserTurret;
}
Object * ObjectBank::getRobot_explosive(){
    Object * robotExplosive = new Object();
    robotExplosive->layer = Object::ROBOTLAYER;
    robotExplosive->addSound(new Sound());
    robotExplosive->name = "robotExplosive";
    robotExplosive->addRenderMaterial();
    Body * body = Body::load("assets\\models\\robot\\Robot_explosive.obj");
    Texture * texture = Texture::load("assets\\models\\robot\\Robot_explosive.jpg");

	robotExplosive->addCollider();
	robotExplosive->addRobotComponent(RobotComponent::Explosive);

    Transform * tr = robotExplosive->getTransform();

    robotExplosive->getRenderMaterial()->addTexture(texture);
    robotExplosive->setBody(body);
    tr->setParent(robotHolder->getTransform());
    return robotExplosive;
}
Object * ObjectBank::getPowerNode_main(){
    Object * powerNodeMain = new Object();
    //powerNodeMain->getTransform()->scale(glm::vec3(1.5f, 1.5f, 1.5f));
    powerNodeMain->layer = Object::DEFENDERLAYER;
    powerNodeMain->name = "powerNodeMain";
    powerNodeMain->addRenderMaterial();
    powerNodeMain->addCollider();
    Powernode * pn = new Powernode(Powernode::Main);

    powerNodeMain->addComponent(pn);
    Body * body = Body::load("assets\\models\\level\\PowerNode_main.obj");
    Texture * texture = Texture::load("assets\\models\\level\\PowerNode_main.jpg");
    powerNodeMain->getRenderMaterial()->addTexture(texture);
    powerNodeMain->setBody(body);
    powerNodeMain->getTransform()->setParent(robotHolder->getTransform());


    return powerNodeMain;
}
Object * ObjectBank::getPowerNode_turret(){
    Object * powerNodeTurret = new Object();
    powerNodeTurret->layer = Object::DEFENDERLAYER;
    powerNodeTurret->name = "powerNodeTurret";
    powerNodeTurret->addRenderMaterial();
    powerNodeTurret->addCollider();
    Powernode * pn = new Powernode(Powernode::Turret);

    powerNodeTurret->addComponent(pn);
    Body * body = Body::load("assets\\models\\level\\PowerNode_turret.obj");
    Texture * texture = Texture::load("assets\\models\\level\\PowerNode_turret.jpg");
    powerNodeTurret->getRenderMaterial()->addTexture(texture);
    powerNodeTurret->setBody(body);
    powerNodeTurret->getTransform()->setParent(structureHolder->getTransform());

    return powerNodeTurret;
}
Object * ObjectBank::getPowerNode_laser(){
    Object * powerNodeLaser = new Object();
    powerNodeLaser->layer = Object::DEFENDERLAYER;
    powerNodeLaser->name = "powerNodeLaser";
    powerNodeLaser->addRenderMaterial();
    powerNodeLaser->addCollider();
    Powernode * pn = new Powernode(Powernode::Laser);

    powerNodeLaser->addComponent(pn);

    Body * body = Body::load("assets\\models\\level\\PowerNode_laser.obj");
    Texture * texture = Texture::load("assets\\models\\level\\PowerNode_laser.jpg");
    powerNodeLaser->getRenderMaterial()->addTexture(texture);
    powerNodeLaser->setBody(body);
    powerNodeLaser->getTransform()->setParent(structureHolder->getTransform());

    return powerNodeLaser;
}
Object * ObjectBank::getTurret_slow(){
    Object * turretSlow = new Object();
    turretSlow->layer = Object::DEFENDERLAYER;
    turretSlow->name = "turretSlow";
    turretSlow->addRenderMaterial();
    turretSlow->addCollider();
    Turret * turret = new Turret(Turret::Heavy);


    turretSlow->addComponent(turret);
    Sound * soundComp = new Sound();
    turretSlow->addSound(soundComp);
    Body * body = Body::load("assets\\models\\level\\Turret_slow.obj");
    Texture * texture = Texture::load("assets\\models\\level\\Turret_slow.jpg");

    Transform * tr = turretSlow->getTransform();

    turretSlow->getRenderMaterial()->addTexture(texture);
    turretSlow->setBody(body);
    tr->setParent(structureHolder->getTransform());

    //Object * turretFloor = getTurretFloor();
    //turretFloor->getTransform()->setParent(tr);

    return turretSlow;
}
Object * ObjectBank::getTurret_medium(){
    Object * turretMedium = new Object();
    turretMedium->layer = Object::DEFENDERLAYER;
    turretMedium->name = "turretMedium";
    turretMedium->addRenderMaterial();
    turretMedium->addCollider();
    Turret * turret = new Turret(Turret::Medium);

    turretMedium->addComponent(turret);
    Sound * soundComp = new Sound();
    turretMedium->addSound(soundComp);
    Body * body = Body::load("assets\\models\\level\\Turret_medium.obj");
    Texture * texture = Texture::load("assets\\models\\level\\Turret_medium.jpg");
    turretMedium->getRenderMaterial()->addTexture(texture);
    turretMedium->setBody(body);
    Transform * tr = turretMedium->getTransform();
    tr->setParent(structureHolder->getTransform());

    //Object * turretFloor = getTurretFloor();
    //turretFloor->getTransform()->setParent(tr);
    return turretMedium;
}
Object * ObjectBank::getTurret_fast(){
    Object * turretFast = new Object();
    turretFast->layer = Object::DEFENDERLAYER;
    turretFast->name = "turretFast";
    turretFast->addRenderMaterial();
    turretFast->addCollider();
    Turret * turret = new Turret(Turret::Light);

    turretFast->addComponent(turret);
    Sound * soundComp = new Sound();
    turretFast->addSound(soundComp);
    Body * body = Body::load("assets\\models\\level\\Turret_fast.obj");
    Texture * texture = Texture::load("assets\\models\\level\\Turret_fast.jpg");
    turretFast->getRenderMaterial()->addTexture(texture);
    turretFast->setBody(body);

    turretFast->getTransform()->setParent(structureHolder->getTransform());

   //Object * turretFloor = getTurretFloor();
    //turretFloor->getTransform()->setParent(tr);
    return turretFast;
}
Object * ObjectBank::getHealthBar(){
	Object * hb = new Object();
	hb->layer = Object::SCENERYLAYER;
	hb->name = "healthbar";
	hb->addRenderMaterial();
	hb->getRenderMaterial()->setShader("ProgressBar");
	Texture * texture = Texture::load("assets\\models\\ui\\healthbar_full.png");
	hb->getRenderMaterial()->addTexture(texture);
	Texture * texture2 = Texture::load("assets\\models\\ui\\healthbar_empty.png");
	hb->getRenderMaterial()->addTexture(texture2);
	Body * body = Body::load("assets\\models\\ui\\healthbar.obj");
	hb->setBody(body);
	hb->getTransform()->setParent(robotHolder->getTransform());
	return hb;
}

Object * ObjectBank::getParticle(){
    Object * prt = new Object();
    prt->addRenderMaterial();
    //Texture * tex = Texture::load("assets\\models\\objects\\ExplosiveParticle.png");
    Texture * tex = Texture::load("assets\\white.png");
    prt->getRenderMaterial()->addTexture(tex);
    //Body * body = Body::load("assets\\models\\objects\\ExplosiveParticle.obj");
     Body * body = Body::load("assets\\models\\misc\\explosion.obj");
    prt->setBody(body);
    Particle * p = new Particle();
    prt->addComponent(p);
    prt->getTransform()->setParent(particleHolder->getTransform());
    return prt;
}

Object * ObjectBank::getParticleEmitter(){
    Object * prt = new Object();
    ParticleEffect * pe = new ParticleEffect(10.0f,10);
    prt->addComponent(pe);
    prt->getTransform()->setParent(particleHolder->getTransform());
    return prt;
}
Object * ObjectBank::getEmptyObject(){
	Object * empty = new Object();
	empty->name = "empty object";
	empty->getTransform()->setParent(structureHolder->getTransform());
	return empty;
}
