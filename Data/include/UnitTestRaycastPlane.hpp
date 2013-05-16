#ifndef UNITTESTRAYCASTPLANE_H
#define UNITTESTRAYCASTPLANE_H

#include <sfml/window.hpp>
#include <glm/glm.hpp>


class Camera;
class ObjectBank;
class Plane;
class Object;
class Stage;

class UnitTestRaycastPlane
{
    public:
        UnitTestRaycastPlane(Camera * cam, Plane * plane, ObjectBank * bank, Stage & stage);
        virtual ~UnitTestRaycastPlane();
        void execute();
        void placeCubeOnGrid(glm::vec2 screenPos);
        void intersectMouseWithSphere(glm::vec2 mousePos);
        void detectWalls(glm::vec2 mousePos);

    protected:
    private:
        Camera * cam;
        Plane * plane;
        ObjectBank * bank;
        Object * debugCube;
        Object * debugSphere;
        Stage & stage;
};

#endif // UNITTESTRAYCASTPLANE_H
