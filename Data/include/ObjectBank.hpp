#ifndef OBJECTBANK_H
#define OBJECTBANK_H

class CellManager;
class Object;
#include <string>
#include <map>

class ObjectBank
{
	public:
		void init(Object * mainObject);
		static ObjectBank & instance(){
        	static ObjectBank INSTANCE;
			return INSTANCE;
        }
		virtual ~ObjectBank();

		Object * getObject(const std::string & objectName, std::string & objFileName, std::string & textureName);
		Object * getCube();
		Object * getSphere();
		Object * getFloor();
		Object * getRobot();
		Object * getBehaviourRobot(CellManager * manager);
		Object * getSkybox();
		Object * getTestObject();
		Object * getWall_01();
		Object * getWall_02();
		Object * getWallCorner();
		Object * getFloortile_01();
		Object * getFloortile_02();
		Object * getTurretFloor();
		Object * getRobot_explosive();
		Object * getRobot_laserTurret();
		Object * getRobot_wireCutter();
		Object * getLasergrid();
		Object * getPowerNode_laser();
		Object * getPowerNode_main();
		Object * getPowerNode_turret();
		Object * getTurret_fast();
		Object * getTurret_medium();
		Object * getTurret_slow();
		Object * getHealthBar();
		Object * getParticle();
		Object * getParticleEmitter();
		Object * getEmptyObject();
		Object * getMainObject(){return mainObject;}

	protected:
	private:
		ObjectBank();
		bool initialized;
		Object * mainObject;
		Object * floorHolder;
		Object * debugCubeHolder;
		Object * robotHolder;
		Object * wallHolder;
		Object * structureHolder;
		Object * particleHolder;
};

#endif // OBJECTBANK_H
