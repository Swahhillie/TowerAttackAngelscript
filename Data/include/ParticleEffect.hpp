#ifndef PARTICLEEFFECT_H
#define PARTICLEEFFECT_H

#include <vector>
#include "Component.hpp"
#include "ObjectBank.hpp"
#include <string>

class Particle;

class ParticleEffect : public Component
{
    public:
        ParticleEffect(float duration, int amount);
        virtual ~ParticleEffect();

        virtual const std::string getName(){return "ParticleEffect";}
    protected:
    private:

    int amountToSpawn;
    int amountSpawned;
    float startTime;
    float duration;
    float interval;
    float lastSpawn;

    bool running;

    std::vector<Particle*> particles;


    void start();
    void update();
    void cleanUp();
    void spawnParticle();
};

#endif // PARTICLEEFFECT_H
