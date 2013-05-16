#ifndef PARTICLE_H
#define PARTICLE_H

#include "Component.hpp"
#include <glm/glm.hpp>


class Particle : public Component
{
    public:
        Particle();
        virtual ~Particle();

        virtual const std::string getName(){return "Particle";}

        float startTime;
        float duration;
        float speed;

        void update();
        void initialize(float startTime_,float duration_, float speed_);

    protected:
    private:
};

#endif // PARTICLE_H
