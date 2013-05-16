#include "ParticleEffect.hpp"
#include "Particle.hpp"
#include "Time.hpp"
#include "Object.hpp"

ParticleEffect::ParticleEffect(float duration_, int amount_)
:amountToSpawn(0),amountSpawned(0),startTime(Time::currentTime),duration(0),interval(0),lastSpawn(0),running(false)
{
    duration = duration_;
    amountToSpawn = amount_;
    start();

//    Object * myFirstParticle = ObjectBank::instance().getParticle();
}

ParticleEffect::~ParticleEffect()
{
    //dtor
}

void ParticleEffect::start()
{
    interval = duration / amountToSpawn;
    running = true;
}

void ParticleEffect::spawnParticle()
{
    Object * particle = ObjectBank::instance().getParticle();
    particle->getTransform()->setPosition(object->getTransform()->getPosition());
    Particle * particleComponent = (Particle*)particle->getComponent("Particle");
    particleComponent->initialize(Time::currentTime,duration,0.5f);
    particles.push_back(particleComponent);
}

void ParticleEffect::update()
{
    if((lastSpawn + interval) < Time::currentTime && running)
    {
        spawnParticle();
        lastSpawn = Time::currentTime;
        amountSpawned ++;
        if(amountSpawned >= amountToSpawn || startTime + duration < Time::currentTime) running = false;
    }

    cleanUp();
}

void ParticleEffect::cleanUp()
{
    for (int i = particles.size()-1; i>-1;i--)
    {
        Particle * p = particles[i];
        if((Time::currentTime - p->startTime) > p->duration)
        {
            p->object->onDestroy();
            particles.erase(particles.begin()+i);
        }
    }
    if(particles.size() == 0 && running == false)
    {
        object->onDestroy();
    }
}
