#include "Lasergrid.hpp"
#include "Object.hpp"
#include "RenderMaterial.hpp"
#include "CellManager.hpp"
#include "Cell.hpp"
#include "Ray.hpp"

Lasergrid::Lasergrid()
{
    //ctor
    attackable = false;
    requirePower = true;
    powered = false;
    initialized = false;
    lastState = powered;
}

Lasergrid::~Lasergrid()
{
    //dtor
}
void Lasergrid::update(){
    if(!initialized){
        onPowerDown();
        initialized = true;
    }
    else{
        if(powered != lastState){
            if(powered){
                onPowerUp();
            }
            else{
                onPowerDown();
            }
            lastState = powered;
        }
    }
    powered = false;
}
void Lasergrid::onPowerUp(){
    object->getRenderMaterial()->visible = true;
    Ray ray(object->getTransform()->getPosition() + glm::vec3(0,1,0), glm::vec3(0,-1,0));
    Cell * cell = CellManager::instance().getCell(ray);
    if(cell){
        cell->setTraversable(false);
    }
}
void Lasergrid::onPowerDown(){
    object->getRenderMaterial()->visible = false;

    Ray ray(object->getTransform()->getPosition() + glm::vec3(0,1,0), glm::vec3(0,-1,0));

    Cell * cell = CellManager::instance().getCell(ray);
    if(cell){
        cell->setTraversable(true);
    }

}
Defender::DefenderType Lasergrid::getDefenderType()const{
    return Defender::Lasergrid;
}
