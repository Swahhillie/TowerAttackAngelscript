#ifndef ROBOTBEHAVIOUR_H
#define ROBOTBEHAVIOUR_H



#include <vector>
class Cell;
class Transform;
class RobotComponent;
class CellManager;
class Destructable;

class RobotBehaviour
{
    public:
		enum RobotBehaviourState{
			MovingDirect,
			MovingAlongMap,
			Attacking,
			Idle
		};
        RobotBehaviour();

        virtual ~RobotBehaviour();
        bool setDestination(Cell * cell);
        void followMap();
        void moveToTarget(RobotComponent & robot, Transform * tr);

        virtual void update(RobotComponent & robot);
        CellManager & manager;
    protected:
    private:
		RobotBehaviour(const RobotBehaviour &);
		RobotBehaviour& operator = (const RobotBehaviour &);

		bool checkForAdjacentEnemies(Transform * tr, RobotComponent & robot);
		void getCurrent(Transform * tr);
		RobotBehaviourState behaviourState;
		void attack(Transform * tr, RobotComponent & robot);
		void onReachTarget();
        Transform * tr;
        std::vector<Cell*> waypoints;
        Cell * target;
        Destructable * attackTarget;
        Cell * destination;
        Cell * current;
};

#endif // ROBOTBEHAVIOUR_H
