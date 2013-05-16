#ifndef TURRET_HPP
#define TURRET_HPP

#include "Defender.hpp"
class RobotComponent;
class RobotController;
class Object;

class Turret : public Defender
{
	public:
		enum TurretState{
			Attacking,
			Waiting
		};

		enum TurretType{
            Light,
            Heavy,
            Medium
		};

		Turret(TurretType type);
		virtual ~Turret();

		virtual void update();

		virtual const std::string getName(){return "Turret";}
		TurretType getTurretType()const;
		virtual Defender::DefenderType getDefenderType()const;

    protected:
        virtual void onDestroy();

	private: //statistics
		std::string typeString;

		float damagePerShot;
		float shotsPerSecond;
		float range;
		std::string shotSound;

	private://state
		Turret(const Turret& other){/*no*/}
		Turret& operator = (const Turret& other){/*no*/return *this;}

		RobotComponent * target;
		TurretState turretState;
        TurretType turretType;
		float lastShotTime;

		void rotateToDirection(const glm::vec3 & direction);
		void shootAtTarget(const glm::vec3 & dirToTarget);
		void prepareShotAtTarget(const glm::vec3 & dirToTarget);

		RobotController * controller;
};

#endif // TURRET_HPP
