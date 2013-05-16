#include "Particle.hpp"
#include "Transform.hpp"
#include "Object.hpp"
#include "Time.hpp"

Particle::Particle()
:startTime(0),duration(0),speed(0)
{

}

Particle::~Particle()
{
    //dtor
}

void Particle::initialize(float startTime_,float duration_, float speed_)
{
    startTime = startTime_;
    duration = duration_;
    speed = speed_;
   // object->getTransform()->rotate(angle,rotation_);
    //assert(glm::length(rotation_) > .95 && glm::length(rotation_) < 1.05f);
}

void Particle::update()
{

    Transform * tr = object->getTransform();
    tr->translate(glm::vec3(0,speed*Time::deltaTime,0));

}
